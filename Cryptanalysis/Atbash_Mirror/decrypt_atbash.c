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

int main(int argc, char **argv, char **env){
  welcome();
  if (argc!=3)
    error("Args: ./decrypt_atbash [encrypted_file] [decrypted_file]");
  FILE *encrypted=NULL;
  if ((encrypted=fopen(argv[1],"r"))==NULL)
    error(argv[1]);
  FILE *decrypted=NULL;
  if ((decrypted=fopen(argv[2],"w"))==NULL)
    error(argv[2]);
  char *buffer=NULL;
  size_t size=length(encrypted);
  if ((buffer=(char *)calloc(size,sizeof(char)))==NULL)
    error("Buffer");
  fill_buffer(buffer,encrypted);
  decrypt(buffer,size);
  write_file(buffer,decrypted);
  printf("\tYou can find the decrypted message in the file %s\n\n",argv[2]);
  free(buffer);
  return 0;
} 
