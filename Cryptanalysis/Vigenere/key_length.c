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
 
/********************/
/**** Key length ****/
/********************/

/* Repetitions number of each letter in the message */

int letter_repetition(char letter, char *buffer, size_t size){
  int freq=0;
  int i=0;
  for (i=0;i<size;i++){
    if (buffer[i]==letter)
      freq++;
  }
  return freq;
}

void repetition_array(int repetitions[ALPHABET_SIZE], char *buffer, size_t size){
  int i=0;
  for (i=0;i<ALPHABET_SIZE;i++)
    repetitions[i]=letter_repetition(alphabet_maj[i], buffer, size);
}

/* Calcul of the index of coincidence */

float index_coincidence(int repetitions[ALPHABET_SIZE], size_t size){
  float somme=0;
  int i=0;
  for (i=0;i<ALPHABET_SIZE;i++)
    somme+=((repetitions[i]*(repetitions[i]-1))/(float)(size*(size-1)));
  return somme;
}

float average(float *tableau, size_t size){
  int i=0;
  float somme=0;
  for (i=0;i<size;i++)
    somme+=tableau[i];
  return (somme/i);
}

/* Calcul the index of coincidences of each sub-message, and the average of all indexes -> Firedman Test */

void calcul_indexes(char *buffer, float indices[CUTTING], size_t size){
  int repetitions[ALPHABET_SIZE];
  int i=0,j=0,k=0,overflow=0;
  for (i=1;i<CUTTING+1;i++){
    int *buffer_sizes=NULL;
    if ((buffer_sizes=(int *)calloc(i,sizeof(int)))==NULL)
      error("Buffer_sizes");
    if ((size % i)==0){
      for (j=0;j<i;j++)
        buffer_sizes[j]=size/i;
    }
    else{
      overflow=size%i;
      for (j=0;j<overflow;j++)
        buffer_sizes[j]=size/i+1;
      for (j=overflow;j<i;j++)
        buffer_sizes[j]=size/i;
    }
    float *buffer_indices=NULL;
    if ((buffer_indices=(float *)calloc(i,sizeof(float)))==NULL)
      error("Buffer_indices");
    for (j=0;j<i;j++){
      char *buffer_sub_message=NULL;
      if ((buffer_sub_message=(char *)calloc(buffer_sizes[j],sizeof(char)))==NULL)
        error("Buffer_sub_message");
       for (k=0;k<buffer_sizes[j];k++)
         buffer_sub_message[k]=buffer[k*i+j];
       repetition_array(repetitions,buffer_sub_message,buffer_sizes[j]);
       free(buffer_sub_message); 
       buffer_indices[j]=index_coincidence(repetitions,buffer_sizes[j]);
       }
    free(buffer_sizes);
    indices[i-1]=average(buffer_indices,i);
    free(buffer_indices);
  }
}

/* Probable length of the key */

float modulus(float a, float b){
  if (a-b>=0)
    return (a-b);
  else
    return (b-a);
}

size_t probable_length_key(char *buffer, size_t size){
  float indices[CUTTING];
  calcul_indexes(buffer,indices, size);
  float indice_theorique_fr=0.074;
  int length=0,i=0;
  for (i=0;i<CUTTING;i++){
    if (modulus(indices[length],indice_theorique_fr)>modulus(indices[i],indice_theorique_fr))
      length=i;
  }
  return (length+1);
}
