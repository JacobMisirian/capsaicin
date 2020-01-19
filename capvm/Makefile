TARGET   = bin/capvm

CC       = gcc
# compiling flags here
CFLAGS   = -c -std=c99 -I inc

LINKER   = gcc
# linking flags here
LFLAGS   = -Wall -I. -lm

OBJECTS += src/main.o
OBJECTS += src/inst.o
OBJECTS += src/vm.o

rm       = rm -f

$(TARGET): $(OBJECTS)
	$(LINKER) -o $@ $(LFLAGS) $^ -lgcc
%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"

.PHONY: run
run:
	@bin/capvm
