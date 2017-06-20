/* Title : Cryptanalysis of Atbash Mirror
 * Author : Zweisamkeit
 * Created : 2 juillet 2016
 * Last modification : 2 juillet 2016
 * Contact : contact@zweisamkeit.fr
 * License : GNU/GPL */

#ifndef __OTHER__
#define __OTHER__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decrypt_atbash.h"
#include "other.h"
#include "constants.h"
#include "decryption.h"

extern const char alphabet_maj[ALPHABET_SIZE];
extern const char alphabet_min[ALPHABET_SIZE];

void error(char *error);
size_t length(FILE *file);
void fill_buffer(char *buffer, FILE *file);
void write_file(char *buffer, FILE *file);
void welcome(void);

#endif