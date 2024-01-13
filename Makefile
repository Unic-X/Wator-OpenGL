CFLAGS = -std=c11 -Wall -Wextra 

all:
	$(CC) $(CCFLAGS) -g -o main src/main.c -lGL -lglut -lpthread
