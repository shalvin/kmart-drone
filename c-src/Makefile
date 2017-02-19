CC=gcc
CFLAGS=-Wall -std=c11
LDFLAGS=-lwiringPi
SRCFILES=main.c shellinput.c commands.c
OBJECTS=$(SRCFILES:.c=.o)
EXECUTABLE=motorcontrol

all: $(SRCFILES) $(EXECUTABLE)

.c.o:
	$(CC) $(CFLAGS) $< -c -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	rm -f *.o $(EXECUTABLE)
