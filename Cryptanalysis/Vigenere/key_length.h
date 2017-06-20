/* Title : Cryptanalysis of Chiffre de Vigenère
 * Author : Zweisamkeit
 * Created : 24 juin 2016
 * Last modification : 29 juin 2016
 * Contact : contact@zweisamkeit.fr
 * License : GNU/GPL */

#ifndef __KEY__LENGTH__
#define __KEY__LENGTH__

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

/********************/
/**** Key length ****/
/********************/

int letter_repetition(char letter, char *buffer, size_t size);
void repetition_array(int repetitions[ALPHABET_SIZE], char *buffer, size_t size);
float index_coincidence(int repetitions[ALPHABET_SIZE], size_t size);
float average(float *tableau, size_t size);
void calcul_indexes(char *buffer, float indices[CUTTING], size_t size);
float modulus(float a, float b);
size_t probable_length_key(char *buffer, size_t size);

#endif