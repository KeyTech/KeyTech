PROGRAM_NAME = simulator

# Executables
TEST_EXECUTABLE = test-execution
DEBUG_EXECUTABLE = $(PROGRAM_NAME)-debug
RELEASE_EXECUTABLE = $(PROGRAM_NAME)

# Directories
SRC_DIR := src
TEST_DIR := test

BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj/main
TEST_OBJ_DIR := $(BUILD_DIR)/obj/test
DEBUG_OBJ_DIR := $(BUILD_DIR)/obj/debug

# Files
CPP_FILES := $(notdir $(wildcard $(SRC_DIR)/*.cpp))
TEST_CPP_FILES := $(notdir $(wildcard $(TEST_DIR)/*.cpp))

OBJ_FILES = $(CPP_FILES:%.cpp=$(OBJ_DIR)/%.o)
TEST_OBJ_FILES = $(TEST_CPP_FILES:%.cpp=$(TEST_OBJ_DIR)/%.o)
DEBUG_OBJ_FILES = $(CPP_FILES:%.cpp=$(DEBUG_OBJ_DIR)/%.o)

GTEST_CPP_FILES := contrib/googletest/gmock-gtest-all.cc
MAIN_DEBUG_OBJ := $(DEBUG_OBJ_DIR)/main.o

# Includes:
INCLUDES := -I include
TEST_INCLUDES := $(INCLUDES) -I contrib
OPTIONS := -Wall
DEBUG_OPTIONS := $(OPTIONS) -ggdb
TEST_OPTIONS := $(DEBUG_OPTIONS) -pthread
