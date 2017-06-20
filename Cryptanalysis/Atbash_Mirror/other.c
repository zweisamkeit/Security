/* Title : Cryptanalysis of Atbash Mirror
 * Author : Zweisamkeit
 * Created : 2 juillet 2016
 * Last modification : 2 juillet 2016
 * Contact : contact@zweisamkeit.fr
 * License : GNU/GPL */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decrypt_atbash.h"
#include "other.h"
#include "constants.h"
#include "decryption.h"

const char alphabet_maj[ALPHABET_SIZE]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char alphabet_min[ALPHABET_SIZE]="abcdefghijklmnopqrstuvwxyz";

void error(char *error){
  perror(error);
  printf("\n\n");
  exit(EXIT_FAILURE);
}

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
  size_t size=strlen(buffer);
  fwrite(buffer,sizeof(char),size,file);
  fwrite("\n",sizeof(char),1,file);
}

void welcome(void){
  printf("\n\n\t\t%s","~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  printf("\n\n\t\t%s","Cryptanalysis of the Atbash Mirror");
  printf("\n\n\t\t%s","    Zweisamkeit -- 2016"); 
  printf("\n\n\t\t%s","         License GNU/GPL");
  printf("\n\n\t\t%s","~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  printf("\n\n");
}
