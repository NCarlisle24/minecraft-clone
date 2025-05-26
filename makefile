# recursive file searching for a given directory and wildcard pattern
rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

# compiler and flags
CC := gcc
CXX := g++
CFLAGS := -g -Wall -Wextra -O2
CXXFLAGS := -g -Wall -Wextra -O2

SRC_DIR := src
OBJ_DIR := obj

INC := -Iinclude
LIB := -Llib -lglfw3dll

TARGET := cutable.exe

# source files

# use this version if using UNIX terminal:
SOURCE_FILES := $(shell find $(SRC_DIR) -name "*.cpp" -or -name "*.c")

# use for windows cmd (ended up being too lazy to implement other things; compile in git bash for now)
# SOURCE_FILES := $(strip $(call rwildcard,$(SRC_DIR)/,*.cpp) $(call rwildcard,$(SRC_DIR)/,*.c))

OBJECT_FILES := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SOURCE_FILES))
OBJECT_FILES := $(OBJECT_FILES:.c=.o)
OBJECT_FILES := $(OBJECT_FILES:.cpp=.o)

# compile object files into executable
$(TARGET): $(OBJECT_FILES)
	$(CXX) $(CXXFLAGS) $(INC) $^ $(LIB) -o $@

# compile c files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# compile cpp files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)