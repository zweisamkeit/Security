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

/************************/
/**** Pre-treatement ****/
/************************/

const char alphabet_min[ALPHABET_SIZE]="abcdefghijklmnopqrstuvwxyz";
const char alphabet_maj[ALPHABET_SIZE]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char all_signs[]="\"\',.:-!?\n";

int count_signs(char *buffer, size_t size){
  int i=0,number=0;
  for (i=0;i<size;i++){
    if ((strchr(all_signs,buffer[i])!=NULL) || buffer[i]==' ')
      number++;
  }
  return (number);
}

void left_shift(char *buffer, size_t *size, int *i){
 int j=0;
 for (j=*i+1;j<*size;j++)
   buffer[j-1]=buffer[j];
 (*size)--;
 (*i)--;
}

void is_lower(char *buffer, size_t size, int *lower){
  int i=0;
  for (i=0;i<size;i++){
    if (strchr(alphabet_min,buffer[i])!=NULL)
      lower[i]=1;
    else
      lower[i]=0;
  }
}

void upper(char *buffer, int i){
  int j=0;
  while((buffer[i])!=alphabet_min[j] && j<ALPHABET_SIZE)
      j++;
  if (j!=26)
    buffer[i]=alphabet_maj[j];
}

void pre_treatment(char *buffer, size_t *size, index_sign *signs, int *lower){
  int i=0,k=0;
  is_lower(buffer,*size,lower);
  while(i<(*size)){
    if ((strchr(all_signs,buffer[i])!=NULL) || buffer[i]==' '){
      (signs+k)->index=i+k;
      (signs+k)->sign=buffer[i];
      k++;
      left_shift(buffer,size,&i);
    }
    upper(buffer,i);
    i++;
  }
}

/************************/
/**** Post-treatment ****/
/************************/

void right_shift(char *buffer, size_t *size, int i){
  int j=0;
  (*size)++;
  for (j=(*size);j>i;j--)
    buffer[j]=buffer[j-1];
}

void to_lower(char *buffer, int i){
  int j=0;
  while (alphabet_maj[j]!=buffer[i])
   j++;
  buffer[i]=alphabet_min[j];
}

void post_treatment(char *buffer, size_t size, index_sign *signs, size_t number_signs, int *lower){
  int i=0;
  for (i=0;i<number_signs;i++){
    right_shift(buffer,&size,(signs+i)->index);
    buffer[(signs+i)->index]=(signs+i)->sign;
  }
  for (i=0;i<size;i++){
   if (lower[i])
     to_lower(buffer,i);
  }
}
