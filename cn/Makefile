# Well aware that this Makefile causes an entire rebuild each time any header file changes.
# Not tracking each and every dependency for interest of time.

CXX=g++

SRC_DIR:=$(realpath ./src)
INC_DIR:=$(realpath ./include)
BUILD_DIR=cn_build
OUT_BINARY=cn
DOCS_DIR=$(BUILD_DIR)/docs

SRC=$(shell ls 2>/dev/null $(SRC_DIR)/*.cpp)
INC=$(shell ls 2>/dev/null $(INC_DIR)/*.h)
OBJ=$(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))

DEFS= -DRAW_PROTO_NUM=144

CXX_FLAGS=	\
	-I $(INC_DIR) $(DEFS) -Wall -Werror -std=c++11 -g

LD_FLAGS= -L$(BUILD_DIR) -luuid

all: exec docs

.PHONY: exec
exec: $(BUILD_DIR)/$(OUT_BINARY)

.PHONY: docs
docs: $(DOCS_DIR)

$(BUILD_DIR)/$(OUT_BINARY): $(BUILD_DIR) $(OBJ)
	$(CXX) $(CXX_FLAGS) $(OBJ) -o $(BUILD_DIR)/$(OUT_BINARY) $(LD_FLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC)
	$(CXX) $(CXX_FLAGS) $< -c -o $@

$(DOCS_DIR): $(INC)
	rm -rf $(DOCS_DIR)
	mkdir -p $(DOCS_DIR)
	doxygen

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
