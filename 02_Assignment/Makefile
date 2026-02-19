# Makefile for Lexical Analyzer

# Compiler and tools
CC = gcc
FLEX = flex
RM = rm -f

# Output executable name
TARGET = lexer
LEX_OUTPUT = lex.yy.c
LEX_SOURCE = lexer.l
TEST_FILE = test_program.c
TEST_FILE2 = test_program2.c
TEST_FILE3 = test_program3.c

# Flags
CFLAGS = -Wall
LDFLAGS = -lfl

# Default target
all: $(TARGET)

# Generate lexer C code from lex file
$(LEX_OUTPUT): $(LEX_SOURCE)
	$(FLEX) $(LEX_SOURCE)

# Compile the lexer
$(TARGET): $(LEX_OUTPUT)
	$(CC) $(CFLAGS) $(LEX_OUTPUT) -o $(TARGET) $(LDFLAGS)

# Run the lexer with test file
test: $(TARGET)
	./$(TARGET) $(TEST_FILE)

# Run the lexer with test file 2
test2: $(TARGET)
	./$(TARGET) $(TEST_FILE2)

# Run the lexer with test file 3
test3: $(TARGET)
	./$(TARGET) $(TEST_FILE3)

# Run all tests
test-all: $(TARGET)
	@echo "=== Running test_program.c ==="
	@./$(TARGET) $(TEST_FILE)
	@echo ""
	@echo "=== Running test_program2.c ==="
	@./$(TARGET) $(TEST_FILE2)
	@echo ""
	@echo "=== Running test_program3.c ==="
	@./$(TARGET) $(TEST_FILE3)

# Run the lexer interactively
run: $(TARGET)
	./$(TARGET)

# Clean generated files
clean:
	$(RM) $(LEX_OUTPUT) $(TARGET) $(TARGET).exe lex.yy.c

# Windows-specific targets
windows: 
	flex $(LEX_SOURCE)
	gcc lex.yy.c -o $(TARGET).exe

windows-test: windows
	$(TARGET).exe $(TEST_FILE)

# Help
help:
	@echo "Available targets:"
	@echo "  all         - Build the lexer (default)"
	@echo "  test        - Build and run with test_program.c"
	@echo "  test2       - Build and run with test_program2.c (loops and arrays)"
	@echo "  test3       - Build and run with test_program3.c (functions and pointers)"
	@echo "  test-all    - Build and run all test programs"
	@echo "  run         - Build and run interactively"
	@echo "  clean       - Remove generated files"
	@echo "  windows     - Build on Windows"
	@echo "  windows-test - Build and test on Windows"
	@echo "  help        - Show this help message"

.PHONY: all test test2 test3 test-all run clean windows windows-test help
