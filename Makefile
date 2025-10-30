CC = gcc
CFLAGS = -Wall -Iinclude
SRC = src/main.c src/parking.c src/queue.c src/linkedlist.c src/bst.c src/priority_queue.c src/billing.c src/fileio.c src/utils.c
OBJ = $(SRC:.c=.o)
TARGET = smart_parking

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
