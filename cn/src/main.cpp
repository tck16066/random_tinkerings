#include <iostream>
#include <stdint.h>
#include <iomanip>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#include "CNNeighbor.h"
#include "CNRawIPTransport.h"
#include "CNID.h"
#include "CNProtocol.h"
#include "CNError.h"
#include "utility.h"

#define UPDATE_MS 15000

int main(int argc, char *argv[])
{
  CNContext ctx;
  CNErrorCode ret = CN_SUCCESS;
  CNRawIPTransport raw;
  CNNeighborStateManager manager;
  CNNeighborStateManager::CNNeighborList neighbors;
  uint64_t lastTime = 0;
  uint64_t currTime = 0;
  uint8_t protocol = RAW_PROTO_NUM;
  int arg;

  if (argc > 1) {
    while ((arg = getopt (argc, argv, "hp:")) != -1) {
      switch (arg) {
      case 'p':
	arg = atoi(optarg);
        if (arg < 143 || arg > 252) {
          std::cerr << "Specify port in IANA IP protocol unassigned range: 143 - 252" << std::endl;
          ret = CN_BUILD_ERROR(CN_MAIN, CN_BAD_ARG, 1);
          goto error;
        }
        protocol = (uint8_t)arg;
        break;
      case 'h':   //drop-through
      default:
        std::cout << "usage:  " << argv[0] << "-p protocol_number" << std::endl;
        goto error;
      }
    }
  }

  if ((ret = ctx.id.generate()) != CN_SUCCESS)
    goto error;
  if ((ret = raw.init(protocol)) != CN_SUCCESS)
    goto error;

  raw.setCtx(&ctx);
  manager.init(&ctx, &raw);

  ret = monoMSecs(&currTime);
  if (ret)
    goto error;
  lastTime = currTime - UPDATE_MS;

  ret = manager.advertise();
  if (ret)
    goto error;

  while (1) {
    ret = monoMSecs(&currTime);
    if (ret)
      goto error;

    if (currTime > lastTime) {
      neighbors.clear();
      ret = manager.knownNeighbors(&neighbors);
      if (ret)
        goto error;

      std::cout << "\n************* NEIGHBORS ************\n";
      for (CNNeighborStateManager::CNNeighborList::iterator iter = neighbors.begin();
        iter != neighbors.end(); ++iter) {
          CNNeighborState *state = NULL;
          ret = manager.neighborState(&(*iter), &state);
          if (ret)
            goto error;

         std::cout << iter->strVal() << " :  ";
         if (state->pingArrived)
           std::cout << state->pingArrived - state->pingSent << " ms" << std::endl;
         else
           std::cout << "UNKNOWN ms" << std::endl;
      }
      std::cout << "\n***********************************\n\n\n";

      ret = manager.advertise();
      if (ret)
        goto error;

      ret = manager.pingNeighbors();
      if (ret)
        goto error;

      lastTime = currTime + UPDATE_MS;
    }

    ret = manager.listenNeighbors(lastTime - currTime);
    if (ret)
      goto error;
  }

error:
  raw.shutdown();
  std::cerr << "Exiting with code: sys(" << CN_SYS_DECODE(ret) << ") " <<
    "code(" << CN_CODE_DECODE(ret) << ")  sub(" << CN_SUB_DECODE(ret) << ")" << std::endl;
  std::cerr.flush();
  return ret;
}

