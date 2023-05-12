CC := gcc
AR := ar
ARFLAGS := rcs

OBJ_DIR := obj
SRC_DIR := src
INC_DIR := includes

# Compiler flags
CFLAGS := -Wall -g

# List of source files
SRCS := $(wildcard $(SRC_DIR)/*.c)

# List of object files
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# List of library files
LIB_DIR := lib
LIBS := $(patsubst $(OBJ_DIR)/%.o, $(LIB_DIR)/%.a, $(OBJS))
LIBS += $(patsubst $(OBJ_DIR)/%.o, $(LIB_DIR)/%.lib, $(OBJS))

TEST_DIR=tests
TESTS=$(wildcard $(TEST_DIR)/*.c)
TEST_BINS=$(patsubst $(TEST_DIR)/%.c, $(TEST_DIR)/bin/%.out, $(TESTS))

# Compile all the object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

#Create a lib folder to store the .lib and .a files
$(LIB_DIR)/%.a: $(OBJ_DIR)/%.o
	@mkdir -p $(@D)
	$(AR) $(ARFLAGS) $@ $<

$(LIB_DIR)/%.lib: $(OBJ_DIR)/%.o
	@mkdir -p $(@D)
	$(AR) $(ARFLAGS) $@ $<

# Create Tests
$(TEST_DIR)/bin/%.out: $(TEST_DIR)/%.c $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< $(OBJS) -o $@ -lcriterion -lm

run_tests: $(TEST_BINS)
	for test in $(TEST_BINS); do \
		./$$test; \
	done

# Run tests with Valgrind
valgrind_tests: $(TEST_BINS)
	for test in $(TEST_BINS); do \
		valgrind --leak-check=full --show-leak-kinds=all ./$$test; \
	done

# Clean up the directory
.PHONY: clean
clean:
	rm -f $(OBJ_DIR)/*.o $(TEST_DIR)/bin/* $(LIB_DIR)/*

# Build targets
lib: $(LIBS)
all: $(LIBS) $(TEST_BINS)
