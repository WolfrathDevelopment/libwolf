CC= gcc
CFLAGS= -c -g -Wall -I include/

CSOURCES= $(shell find * -type f -name '*.c' -not -path "tests/*")
CPPSOURCES= $(shell find * -type f -name '*.cpp' -not -path "tests/*")
SOURCES= $(CSOURCES) $(CPPSOURCES)

COBJECTS= $(CSOURCES:.c=.o)
CPPOBJECTS= $(CPPSOURCES:.cpp=.o)
OBJECTS= $(COBJECTS) $(CPPOBJECTS)

OUTPUT= main

LIBS=

# Are we compiling on a mac?

UNAME= $(shell uname)

ifeq ($(UNAME), "Darwin")
LIBS=
endif

all: $(CSOURCES) $(CPPSOURCES) $(OUTPUT)
	@echo "Done."

$(OUTPUT): $(OBJECTS)
	@echo "LD $@"
	@$(CC) $(OBJECTS) -o $@ $(LIBS)

.c.o:
	@echo "CC $<"
	@gcc $(CFLAGS) $< -o $@
	
.cpp.o:
	@echo "CC $<"
	@$(CC) $(CFLAGS) $< -o $@

clean:
	@-rm -rf $(OBJECTS) $(OUTPUT)

love:
	@echo "Not war?"
