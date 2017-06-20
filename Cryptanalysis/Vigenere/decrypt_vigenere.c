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

char lang[2];

int main(int argc, char **argv, char **env){

  /* Home */

  welcome();

  /* Files */

  if (argc!=4)
    error("Args : ./decrypt_vigenere [encrypted_file] [decrypted_file] [fr/en]"); 
  FILE *encrypted=NULL;
  if ((encrypted=fopen(argv[1],"r"))==NULL)
    error(argv[1]);
  FILE *decrypted=NULL;
  if ((decrypted=fopen(argv[2],"w+"))==NULL)
    error(argv[2]);
 
  /* Langage of the initial message */ 
 
  strcpy(lang,argv[3]);
  if ((strcmp((const char *)lang,"fr")!=0) && (strcmp((const char *)lang,"en")!=0))
    error("Invalid language");

  /* Creation of buffer which contains the message  */

  size_t size=length(encrypted);
  char *buffer;
  if ((buffer=(char *)calloc(size,sizeof(char)))==NULL)
    error("Buffer");
  fill_buffer(buffer,encrypted);

  /* To manage upper/lowercase */

  int *lower=NULL;
  if ((lower=(int *)calloc(size,sizeof(int)))==NULL)
    error("Lower");

  /* Count ponctuation signs and spaces in the buffer, keep all of them associated indexes on a structure, and delete all of them  */

  size_t size_copy=size;
  index_sign *signs;
  int number_signs=count_signs(buffer, size_copy);
  if ((signs=(index_sign *)calloc(number_signs,sizeof(index_sign)))==NULL)
      error("Index_sign");
  pre_treatment(buffer,&size_copy,signs,lower);

  /* Copy the part of buffer which contain message without signs  */  

  char *buffer_treated=NULL;
  if ((buffer_treated=(char *)calloc(size_copy,sizeof(char)))==NULL)
    error("Buffer_treated");
  memcpy(buffer_treated,buffer,size_copy);
  
  /* Key */

  size_t key_length=probable_length_key(buffer_treated, size_copy);
  printf("Probable length of the key : %li\n\n",key_length);
  char *key;
  if ((key=(char *)calloc(key_length,sizeof(char)))==NULL)
    error("Key");
  key_construction(buffer_treated,size_copy,key_length,key);
  printf("Probable key  : %s\n\n",key);

  /* Create buffer which will contain the decrypted message */

  char *buffer2;
  if ((buffer2=(char *)calloc(size_copy,sizeof(char)))==NULL)
    error("Buffer2");
  decrypt(buffer_treated,size_copy,key,key_length,buffer2);

  /* Rewrite on buffer all the content of buffer2, with the place to put the spaces */
  
  memcpy(buffer,buffer2,size_copy); // realloc doesn't work...
  post_treatment(buffer,size_copy,signs,number_signs,lower);
  write_file(buffer,decrypted);

  /* Cleaning */

  free(signs);
  free(buffer);
  free(lower);
  free(buffer_treated);
  free(buffer2);
  free(key);
  fclose(encrypted);
  fclose(decrypted);
  return 0;
}
