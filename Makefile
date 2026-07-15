

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

# Directories
SRC_DIR   = src
BUILD_DIR = build
BIN_DIR   = bin

# Executable
TARGET = $(BIN_DIR)/assembler

# Source files
SRC = $(shell find $(SRC_DIR) -name "*.c")

# Object files
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

# Default target
all: $(TARGET)

# Link executable
$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJ) -o $(TARGET)

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Run the assembler
run: $(TARGET)
	./$(TARGET) tests/program.asm

# Remove build artifacts
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Rebuild everything
re: clean all

.PHONY: all clean re run

