#!/usr/bin/env python

import threading
import time

"""
This demonstrates a simple example of how to do threading. The program
defines a class called "Counter." Counter subclasses Thread, and it
represents a distinct execution context, i.e. a distinct thread of
execution.

When Counter's start() (a function in the base class---Thread) is
called, it creates a new thread and runs whatever is in the subclass
(in this case, the subclass is Counter) run() function. Counter's
run() function loops forever until it is told to stop. While it
is running, it will update a counter if both of the following are true:
the counter has been told to count and it has been at least half a
second since the last time it incremented the counter.

Counter can have its increment value set, so you don't need to only
increment by 1 (or even positive numbers). Counter also a function
that will return the current value of the counter.

Counter represents a secondary thread. The primary thread instantiates
a Counter object, starts the Counter thread, and then blocks forever
to await user input. All commands are processed on the primary thread.
The secondary thread _only_ counts.

When it is time to quit (q), the primary thread tells the secondary
thread to quit. The primary thread sets the Counter's "running" member
to "False," which tells the thread to stop running because "self.running"
is no longer true for the loop condition inside of Counter.run(). The
primary thread then attempts to join the threads, which means the caller
(the primary thread) waits until the other thread (the secondary thread)
exits (in this case, meaning run() has returned).

Note to observers, this is _not_ production-worthy code. There are
numerous edge cases, style incongruities, unforgiving input parsing, etc. I wouldn't even recommend subclassing from Thread in most cases.

It is only meant as a very simplistic example of how to achieve 2
execution contexts and do something mildly interesting.
"""

class Counter(threading.Thread):
    # This class emulates a long-running process.
    def __init__(self):
        # Set counter to 0, prepare to run.
        self.counting = False
        self.count = 0
        self.increment = 1
        self.running = False
        self.last_update_time = time.time()
        threading.Thread.__init__(self)

    def startCounting(self):
        self.counting = True

    def stopCounting(self):
        self.counting = False

    def setIncAmount(self, inc):
        self.increment = inc

    def getCount(self):
        return self.count

    def incCount(self):
        self.count = self.count + self.increment

    def stopRunning(self):
        self.running = False
        # Here, the caller waits until the thread termiates.
        # Note, DO NOT call this from the thread you want to terminate.
        self.join()

    def run(self):
        self.running = True
        while self.running:
            now = time.time()
            delta = now - self.last_update_time
            if self.counting and delta > 0.5:
                self.incCount()
                self.last_update_time = now

counter = Counter()
counter.start()

running = True

def quit(x):
    print "Quitting program."
    global running
    global counter
    running = False
    counter.stopRunning()

def get_count(x):
    global counter
    print "Current value is: %s" % counter.getCount()

def set_inc(x):
    # We are a little unforiving with input; we expect exactly
    # one space and an int, like this: i 10
    global counter
    x = int(x.split()[1])
    print "Setting increment to %s" % x
    counter.setIncAmount(x)

def do_counting(x):
    global counter
    counter.startCounting()

def stop_counting(x):
    global counter
    counter.stopCounting()    

cmds = {}
cmds['q'] = quit
cmds['g'] = get_count
cmds['i'] = set_inc
cmds['d'] = do_counting
cmds['n'] = stop_counting

while running:
    inp = str(raw_input())

    if inp[0] not in cmds:
        print "Unknown Command."
    else:
        cmds[inp[0]](inp)
