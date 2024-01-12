CFLAGS = -std=c11 -Wall -Wextra -pthreads

all:
	$(CC) $(CCFLAGS) -g -o main src/main.c -lGL -lglut
