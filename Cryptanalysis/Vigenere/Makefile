CC=gcc
CFLAGS=-Wall -g
LDFLAGS=
EXEC=decrypt_vigenere
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

decrypt_vigenere: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
