# Makefile

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I/usr/local/include

# Linker settings
LDFLAGS = -L/usr/local/lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Target executable name
TARGET = game_of_life

# Directories
SRCDIR = src
OBJDIR = obj

# Source and object files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

# Default rule to build the target
$(TARGET): $(OBJECTS)
	@echo "Linking $@..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to create the object directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Rule to clean up generated files
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Specify targets that are not files
.PHONY: clean
