CFLAGS = -Wall -std=c99

TARGET = program

all: $(TARGET)

$(TARGET): update_dataset.c student.c student.h
	$(CC) $(CFLAGS) update_dataset.c student.c -o $(TARGET)

clean:
	rm -f $(TARGET)
