# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# SFML library settings
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files and executable
SRCS = $(wildcard src/*.cpp)
EXEC = FormulaFrenzy

# Default target
all: $(EXEC)

# Compile and link
$(EXEC): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(SFML_LIBS)

# Clean
clean:
	rm -f $(EXEC)

# Run
run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run