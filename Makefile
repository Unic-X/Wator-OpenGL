CFLAGS = -std=c99 -Wall -Wextra

all:
				$(CC) $(CCFLAGS) -g -o main src/main.c -lGL -lglut
