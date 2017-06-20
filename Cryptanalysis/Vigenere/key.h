/* Title : Cryptanalysis of Chiffre de Vigenère
 * Author : Zweisamkeit
 * Created : 24 juin 2016
 * Last modification : 29 juin 2016
 * Contact : contact@zweisamkeit.fr
 * License : GNU/GPL */

#ifndef __KEY__
#define __KEY__

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

extern char lang[2];
extern const char alphabet_maj[ALPHABET_SIZE];
extern const float theorical_frequencies_fr[ALPHABET_SIZE];
extern const float theorical_frequencies_en[ALPHABET_SIZE];

/******************************/
/**** Frequential analysis ****/
/******************************/

void calcul_frequences(float experimental_frequencies[ALPHABET_SIZE], char *buffer, size_t size);
void calcul_distances(float accumulated_differences[ALPHABET_SIZE], char *buffer, size_t size);

/****************************/
/***** Key construction *****/
/****************************/

int minimum(char *buffer, size_t size);
void key_construction(char *buffer, size_t size, size_t key_length, char *key);

#endif
