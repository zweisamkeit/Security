CC=gcc
CFLAGS=-Wall -g
LDFLAGS=
EXEC=decrypt_atbash
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

decrypt_atbash: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
