CC := gcc

OBJ_DIR := obj
SRC_DIR := src
INC_DIR := includes

# Compiler flags
CFLAGS := -Wall -g

# List of source files
SRCS := $(wildcard $(SRC_DIR)/*.c)

# List of object files
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Name of the executable
EXE := test.out

TEST_DIR=tests
TESTS=$(wildcard $(TEST_DIR)/*.c)
TEST_BINS=$(patsubst $(TEST_DIR)/%.c, $(TEST_DIR)/bin/%, $(TESTS))

# Compile all the object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

# Link the object files to create the executable
$(EXE): test.c $(OBJS) 
	$(CC) $(CFLAGS) $^ -o $@ -lm

# Create Tests
$(TEST_DIR)/bin/%: $(TEST_DIR)/%.c $(OBJS)
	$(CC) $(CFLAGS) $< $(OBJS) -o $@ -lcriterion -lm

# Clean up the directory
.PHONY: clean
clean:
	rm -f $(OBJ_DIR)/*.o $(EXE) $(TEST_DIR)/bin/*

# Build targets
all: $(EXE) $(TEST_BINS)
