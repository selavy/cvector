CC=gcc
CFLAGS=-g -pedantic -Wall -Werror
OBJS=main.o cvector_int.o cvector_char.o cvector_long.o
TARGET=driver

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
%.o: %.c %.h
	$(CC) -o $@ $(CFLAGS) -c $<
.PHONY: clean
clean:
	rm -rf $(TARGET) $(OBJS) *~
