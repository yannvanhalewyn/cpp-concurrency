# Compiler
CC = g++

# Flags
CFLAGS = -c -Wall -std=c++1y
LDLFLAGS = -lpthread

# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Executables
EXEC = main
EXEC := $(addprefix $(BINDIR)/, $(EXEC))

# Sources
SOURCES := $(shell find $(SRCDIR) -name '*.cpp')
HEADERS := $(shell find $(SRCDIR) -name '*.h')
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(EXEC): $(OBJECTS)
	@[ -d $(BINDIR) ] || (mkdir $(BINDIR) && echo "made $(BINDIR) dir")
	$(CC) $^ -o $@ $(LDLFLAGS)

$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	@[ -d $(dir $@) ] || (mkdir -p $(dir $@) && echo "made dir $(dir $@)")
	$(CC) $(CFLAGS) $< -o $@

# Helpers
clean:
	rm -f $(EXEC) $(OBJECTS)

print_vars:
	@echo SOURCES = $(SOURCES)
	@echo OBJECTS = $(OBJECTS)
	@echo HEADERS = $(HEADERS)
	@echo EXEC = $(EXEC)

run: $(EXEC)
	@./$(EXEC)

.PHONY: clean test run print_vars
