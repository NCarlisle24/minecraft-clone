# compiler and flags
CC := gcc
CXX := g++
CFLAGS := -Wall -Wextra -O2
CXXFLAGS := -Wall -Wextra -O2

SRC_DIR := src
OBJ_DIR := obj

INC := -Iinclude
LIB := -Llib -lglfw3dll

TARGET := cutable.exe

# source files
SOURCE_FILES := $(shell find $(SRC_DIR) -name "*.cpp" -or -name "*.c")
OBJECT_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(filter %.c,$(SOURCE_FILES)))
OBJECT_FILES += $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(filter %.cpp,$(SOURCE_FILES)))

# compile object files into executable
$(TARGET): $(OBJECT_FILES)
	$(CXX) $(CXXFLAGS) $(INC) $^ $(LIB) -o $@

# compile c files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< $(LIB) -o $@

# compile cpp files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INC) -c $< $(LIB) -o $@