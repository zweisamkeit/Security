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

/******************************/
/**** Frequential analysis ****/
/******************************/

const float theorical_frequencies_fr[ALPHABET_SIZE]={9.42,1.02,2.64,3.39,15.87,0.95,1.04,0.77,8.41,0.89,0.00,5.34,3.24,7.15,5.14,2.86,1.06,6.46,7.90,7.26,6.24,2.15,0.00,0.30,0.24,0.32};
const float theorical_frequencies_en[ALPHABET_SIZE]={8.08,1.67,3.18,3.99,12.56,2.17,1.80,5.27,7.24,0.14,0.63,4.04,2.60,7.38,7.47,1.91,0.09,6.42,6.59,9.15,2.79,1.00,1.89,0.21,1.65,0.07};

/* Calcul the frequency of occurence of each letter in the message */

void calcul_frequences(float experimental_frequencies[ALPHABET_SIZE], char *buffer, size_t size){
  int repetitions[ALPHABET_SIZE];
  repetition_array(repetitions, buffer, size);
  int i=0;
  for (i=0;i<ALPHABET_SIZE;i++)
    experimental_frequencies[i]=repetitions[i]/(float)size*100;
}

/* Calcul accumulated distances between theorical frequences (depending on the language parameter) and experimental frequences for each shift */

void calcul_distances(float accumulated_differences[ALPHABET_SIZE], char *buffer, size_t size){
  float experimental_frequencies[ALPHABET_SIZE],theorical_frequencies[ALPHABET_SIZE];
  int i=0;
  if ((strcmp((const char *)lang,"fr"))==0)
    for (i=0;i<ALPHABET_SIZE;i++)
     theorical_frequencies[i]=theorical_frequencies_fr[i]; 
  else
    for (i=0;i<ALPHABET_SIZE;i++)
     theorical_frequencies[i]=theorical_frequencies_en[i];
  calcul_frequences(experimental_frequencies, buffer, size);
  int j=0;
  for (i=0;i<ALPHABET_SIZE;i++){
    accumulated_differences[i]=0;
    for (j=0;j<ALPHABET_SIZE;j++)
      accumulated_differences[i]+=modulus(theorical_frequencies[j],experimental_frequencies[(i+j)%ALPHABET_SIZE]);
  }
}

/****************************/
/***** Key construction *****/
/****************************/

int minimum(char *buffer, size_t size){
  int i=0,position=0;
  float accumulated_differences[ALPHABET_SIZE];
  calcul_distances(accumulated_differences,buffer, size);
  float min=accumulated_differences[i];
  for (i=1;i<ALPHABET_SIZE;i++){
    if (min>accumulated_differences[i]){
      min=accumulated_differences[i];
      position=i;
    }
  }
  return position;
}

/* Construct the key */

void key_construction(char *buffer, size_t size, size_t key_length, char *key){
  int i=0,j=0,position=0,overflow=0,aux=1;
  overflow=size%key_length;
  for (i=0;i<key_length;i++){
    if (overflow<=0)
      aux=0;
    char *buffer_sub_message;
    if ((buffer_sub_message=(char *)calloc((size/key_length+aux),sizeof(char)))==NULL)
      error("Buffer_sub_message");
    for (j=0;j<(size/key_length+aux);j++)
       buffer_sub_message[j]=buffer[j*key_length+i];
    position=minimum(buffer_sub_message,size/key_length+aux);
    free(buffer_sub_message);
    key[i]=alphabet_maj[position];
    overflow--;
  }
}
