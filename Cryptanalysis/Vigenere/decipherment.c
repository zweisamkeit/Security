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

 #include "constants.h"

/************************/
/***** Decipherment *****/
/************************/

int letter_number(char letter){
  int num=0;
  while (alphabet_maj[num]!=letter)
    num++;
  return num;
}

int modulo_abs(int a, int b, int p){
  if (a>=b)
    return ((a-b)%p);
  else
    return (p+(a-b));
}

void decrypt(char *buffer, size_t size, char *key, size_t key_length, char *buffer2){
  int i=0,num1=0,num2=0,position=0;
  for (i=0;i<size;i++){
    num1=letter_number(buffer[i]);
    num2=letter_number(key[i%key_length]);
    position=modulo_abs(num1,num2,ALPHABET_SIZE);
    buffer2[i]=alphabet_maj[position];
  }
}
