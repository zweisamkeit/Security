/* Title : Cryptanalysis of Chiffre de Vigenère
 * Author : Zweisamkeit
 * Created : 24 juin 2016
 * Last modification : 29 juin 2016
 * Contact : contact@zweisamkeit.fr
 * License : GNU/GPL */

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

/**************************************/
/***** Processing files / buffers *****/
/**************************************/

size_t length(FILE *file){
  size_t size;
  fseek(file,0L,SEEK_END);
  size=ftell(file);
  return (size-1);
}

void fill_buffer(char *buffer, FILE *file){
  size_t size=length(file);
  int err;
  fseek(file,0,SEEK_SET);
  if ((err=fread(buffer,sizeof(char),size,file))==0)
    error("Read file");
}

void write_file(char *buffer, FILE *file){
  size_t size=strlen(buffer)-1;
  fwrite(buffer,sizeof(char),size,file);
  fwrite("\n",sizeof(char),1,file);
}

void welcome(void){
  printf("\n\n\t\t%s","~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  printf("\n\n\t\t%s","Cryptanalysis of the Chiffre de Vigenère");
  printf("\n\n\t\t%s","        Zweisamkeit -- 2016");
  printf("\n\n\t\t%s","             License GNU/GPL");
  printf("\n\n\t\t%s","~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  printf("\n\n");
}

/******************/
/***** Errors *****/
/******************/

void error(char *error){
  perror(error);
  printf("\n\n");
  exit(EXIT_FAILURE);
}
