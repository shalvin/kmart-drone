CC=gcc
CFLAGS=-Wall
LDFLAGS=
SRCFILES=main.c shellinput.c
OBJECTS=$(SRCFILES:.c=.o)
EXECUTABLE=motorcontrol

all: $(SRCFILES) $(EXECUTABLE)

.c.o:
	$(CC) $(CFLAGS) $< -c -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	rm -f *.o $(EXECUTABLE)
