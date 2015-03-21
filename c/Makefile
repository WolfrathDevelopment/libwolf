CC= g++
CFLAGS= -c -g -Wall -I include/
SOURCES= $(shell find * -type f -name '*.c[p]*' -not -path "tests/*")
COBJECTS= $(SOURCES:.c=.o)
OBJECTS= $(COBJECTS:.cpp=.o)
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
	@echo "LD $@"
	@$(CC) $(OBJECTS) -o $@ $(LIBS)

.c.o:
	@echo "CC $<"
	@$(CC) $(CFLAGS) $< -o $@
	
.cpp.o:
	@echo "CC $<"
	@$(CC) $(CFLAGS) $< -o $@

clean:
	@-rm -rf $(OBJECTS) $(OUTPUT)

love:
	@echo "Not war?"
