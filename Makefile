CC = gcc
TARGET = square 

all: main.cpp squaresolver.cpp
	$(CC) main.cpp squaresolver.cpp -Wall -Wextra -o $(TARGET)
clean:
	rm *.o $(TARGET)