CC= gcc
CFLAGS= -c -g -Wall -I include/
SOURCES= $(shell find * -type f -name '*.c')
OBJECTS= $(SOURCES:.c=.o)
OUTPUT= main

LIBS=

# Are we compiling on a mac?

UNAME= $(shell uname)

ifeq ($(UNAME), "Darwin")
LIBS=
endif


all: $(SOURCES) $(OUTPUT)
	@echo "Done."

$(OUTPUT): $(OBJECTS)
	@$(CC) $(OBJECTS) -o $@ $(LIBS)
	@echo "LD $@"

.c.o:
	@$(CC) $(CFLAGS) $< -o $@
	@echo "CC $<"
	

clean:
	@-rm -rf $(OBJECTS) $(OUTPUT)

love:
	@echo "Not war?"
