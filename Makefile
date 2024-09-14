CC := gcc
CFLAGS := -Wall -Werror -g
LDFLAGS :=


OBJECTS := main.o mush.o

all: mush


mush: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f mush *.o

.PHONY: clean
