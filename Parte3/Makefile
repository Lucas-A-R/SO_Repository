CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = esteganografia

all: $(TARGET)

$(TARGET): main.o esteganografia.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

esteganografia.o: esteganografia.c
	$(CC) $(CFLAGS) -c esteganografia.c

clean:
	rm -f *.o $(TARGET)