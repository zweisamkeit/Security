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

void decrypt(char *buffer, size_t size_message){
  int i=0,j=0;
  for (i=0;i<size_message;i++){
    if (strchr(alphabet_maj,buffer[i])!=NULL){
      j=0;
      while (buffer[i]!=alphabet_maj[j] && j<ALPHABET_SIZE)
        j++;
      if (j!=26)
        buffer[i]=alphabet_maj[ALPHABET_SIZE-j-1];
    }
    else if (strchr(alphabet_min,buffer[i])!=NULL){
      j=0;
      while (buffer[i]!=alphabet_min[j] && j<ALPHABET_SIZE)
        j++;
      if (j!=26)
        buffer[i]=alphabet_min[ALPHABET_SIZE-j-1];
    }
  }
}
