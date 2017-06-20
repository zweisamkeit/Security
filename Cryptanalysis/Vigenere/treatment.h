/* Title : Cryptanalysis of Chiffre de Vigenère
 * Author : Zweisamkeit
 * Created : 24 juin 2016
 * Last modification : 29 juin 2016
 * Contact : contact@zweisamkeit.fr
 * License : GNU/GPL */

#ifndef __FORMAT__
#define __FORMAT__

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

 typedef struct index_sign{
  int index;
  char sign;
} index_sign;

/*********************/
/**** Format text ****/
/*********************/

extern const char alphabet_min[ALPHABET_SIZE];
extern const char alphabet_maj[ALPHABET_SIZE];
extern const char all_signs[];

int count_signs(char *buffer, size_t size);
void left_shift(char *buffer, size_t *size, int *i);
void is_lower(char *buffer, size_t size, int *lower);
void upper(char *buffer, int i);
void pre_treatment(char *buffer, size_t *size, index_sign *signs, int *lower);

/************************/
/**** Post-treatment ****/
/************************/

void right_shift(char *buffer, size_t *size, int i);
void to_lower(char *buffer, int i);
void post_treatment(char *buffer, size_t size, index_sign *signs, size_t number_signs,int *lower);

#endif
