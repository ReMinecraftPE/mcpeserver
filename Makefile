# MCPE Server (C) 2023 iProgramInCpp
# Makefile

# Source code paths
SRC_DIR=source
BUILD_DIR=build
THIRDPARTY_DIR=thirdparty

# Binary target
BINARY_TARGET=mcpeserver

INCLUDES = \
-I.                          \
-Ithirdparty                 \
-Iplatforms/windows          \
-Iplatforms/windows          \
-Ithirdparty/raknet          \
-Isource                     \
-Isource/Network             \
-Isource/Sound               \
-Isource/GameMode            \
-Isource/App                 \
-Isource/Base                \
-Isource/GUI                 \
-Isource/GUI/Screen          \
-Isource/Renderer            \
-Isource/UserInput           \
-Isource/World               \
-Isource/World/Generator     \
-Isource/World/Item          \
-Isource/World/Tile          \
-Isource/World/Renderer      \
-Isource/World/Entity        \
-Isource/World/Entity/Models \
-Isource/World/Particle      \
-Isource/World/Storage

CXXFLAGS = $(INCLUDES)

CPP_FILES = $(shell find $(SRC_DIR) $(THIRDPARTY_DIR) -type f -name '*.cpp')
OBJ_FILES = $(patsubst %, $(BUILD_DIR)/%, $(CPP_FILES:.cpp=.o))
DEP_FILES = $(patsubst %, $(BUILD_DIR)/%, $(CPP_FILES:.cpp=.d))

all: binary

clean:
	@echo "Cleaning..."
	@rm -rf $(OBJ_FILES) $(DEP_FILES) $(BINARY_TARGET)

binary: $(BINARY_TARGET)

$(BINARY_TARGET): $(OBJ_FILES)
	@echo "Linking $@"
	@$(CXX) -o $@ $^

-include $(DEP_FILES)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@ -MMD
