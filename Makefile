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
EXE := test

# Compile all the object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

# Link the object files to create the executable
$(EXE): test.c $(OBJS) 
	$(CC) $(CFLAGS) $^ -o $@

# Clean up the directory
.PHONY: clean
clean:
	rm -f $(OBJ_DIR)/*.o $(EXE)