/* Title : Cryptanalysis of Chiffre de Vigenère
 * Author : Zweisamkeit
 * Created : 24 juin 2016
 * Last modification : 29 juin 2016
 * Contact : contact@zweisamkeit.fr
 * License : GNU/GPL */

#ifndef __OTHER__
#define __OTHER__

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

/**************************************/
/***** Processing files / buffers *****/
/**************************************/

size_t length(FILE *file);
void fill_buffer(char *buffer, FILE *file);
void write_file(char *buffer, FILE *file);

/****************/
/***** Home *****/
/****************/

void welcome(void);

/******************/
/***** Errors *****/
/******************/

void error(char *error);

#endif
