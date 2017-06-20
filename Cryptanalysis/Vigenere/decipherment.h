/* Title : Cryptanalysis of Chiffre de Vigenère
 * Author : Zweisamkeit
 * Created : 24 juin 2016
 * Last modification : 29 juin 2016
 * Contact : contact@zweisamkeit.fr
 * License : GNU/GPL */

#ifndef __DECIPHERMENT__
#define __DECIPHERMENT__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "decrypt_vigenere.h"
#include "treatment.h"
#include "key_length.h"
#include "key.h"
#include "decipherment.h"
#include "other.h"
#include "constants.h"

extern const char alphabet_maj[ALPHABET_SIZE];

/************************/
/***** Decipherment *****/
/************************/

int letter_number(char letter);
int modulo_abs(int a, int b, int p);
void decrypt(char *buffer, size_t size, char *key, size_t key_length, char *buffer2);

#endif
