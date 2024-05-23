CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = main
SRCDIR = src
BUILDDIR = build

# Source files
SRC = $(wildcard $(SRCDIR)/*.cpp $(SRCDIR)/*/*.cpp)
# Object files
OBJ = $(SRC:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

# Default target
all: $(TARGET)

# Link the target
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files to object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean up
clean:
	rm -rf $(BUILDDIR) $(TARGET)

# Phony targets
.PHONY: all clean
