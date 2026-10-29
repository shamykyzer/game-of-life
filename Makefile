# Makefile

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I$(RAYLIB_SRC)

# raylib is vendored in ./raylib and built in place (no system install needed)
RAYLIB_SRC = raylib/src
RAYLIB_LIB = $(RAYLIB_SRC)/libraylib.a

# Linker settings
LDFLAGS = -L$(RAYLIB_SRC) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Target executable name
TARGET = game_of_life

# Directories
SRCDIR = app
OBJDIR = obj

# Source and object files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

# Default rule to build the target
$(TARGET): $(OBJECTS) $(RAYLIB_LIB)
	@echo "Linking $@..."
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

# Rule to compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to create the object directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Build the vendored raylib static library (requires libxinerama-dev etc, see scripts/)
$(RAYLIB_LIB):
	$(MAKE) -C $(RAYLIB_SRC) PLATFORM=PLATFORM_DESKTOP

# Rule to clean up generated files
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Also clean the raylib build
clean-all: clean
	$(MAKE) -C $(RAYLIB_SRC) clean

# Specify targets that are not files
.PHONY: clean clean-all
