CC=gcc
CFLAGS=-g -Wall
LDFLAGS=
EXECUTABLE=motorcontrol
SRCFILES=main.c shellinput.c
OBJECTS=$(SRCFILES:.c=.o)

all: $(SRCFILES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
    $(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
    $(CC) $(CFLAGS) $< -o $@

clean:
    rm *.o $(EXECUTABLE)
