TARGET = main
SOURCES = main.c util.c
HEADERS = util.h
CFLAGS = -Wall -g
CC = gcc
LDFLAGS =

$(TARGET): $(SOURCES) $(HEADERS)
	@$(CC) $(CFLAGS) -o $@ $(SOURCES) $(LDFLAGS)

clean:
	rm -f $(TARGET) *.o