SHELL := /bin/zsh
CC := gcc
CFLAGS := -g -Wall -Wextra -Iinclude -MMD -MP

TARGET_EXEC := game
BUILD_DIR := ./build
SRC_DIR := ./src
TEST_DIR := ./tests

# 1. Source Finding
SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# 2. Engine Logic (Everything EXCEPT main.c)
# IMPORTANT: Adjust 'src/main.c.o' if your file path is different!
ENGINE_OBJS := $(filter-out $(BUILD_DIR)/src/main.c.o, $(OBJS))

# 3. Standard Game Build
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	@echo "Linking Game..."
	@mkdir -p $(BUILD_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Built: $@"

# 4. Standard Compilation
$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean run

run: $(BUILD_DIR)/$(TARGET_EXEC)
	./$(BUILD_DIR)/$(TARGET_EXEC)

clean:
	rm -rf $(BUILD_DIR)

# Usage: make test_bfs
# Logic: Matches "test_%" (e.g., test_bfs). 
#        Prerequisite 1: tests/test_%.c (tests/test_bfs.c)
#        Prerequisite 2: $(ENGINE_OBJS) (All your map, player, queue logic)
test_%: $(TEST_DIR)/test_%.c $(ENGINE_OBJS)
	@echo "Building Test: $*"
	@mkdir -p $(BUILD_DIR)/tests
	
	# Compile the specific test file + Link with Engine Objects
	$(CC) $(CFLAGS) $< $(ENGINE_OBJS) -o $(BUILD_DIR)/tests/$@
	
	@echo "Running Test: $*..."
	@echo "-----------------------------------"
	@./$(BUILD_DIR)/tests/$@

-include $(OBJS:.o=.d)
