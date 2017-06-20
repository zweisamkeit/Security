#!/usr/bin/env python

# Title : Cryptanalysis of Caesar Cipher
# Author : Zweisamkeit
# Created : 07/28/2016
# Last modification : 07/28/2016
# Contact : contact@zweisamkeit.fr
# License : GNU/GPL

import sys

if (len(sys.argv)!=4):
  # print("Args error : ./dceasar.py ciphertext deciphertext shift_value")
  exit(1)

try:
  cipherfile=open(sys.argv[1],"r")
  decipherfile=open(sys.argv[2],"w")
except:
  # print("Error: No such file directory")
  exit(2)

ciphertext=cipherfile.read()

alphabet="abcdefghijklmnopqrstuvwxyz"

for i in range (0,len(ciphertext)):
  if (ciphertext[i].isupper()):
    upper=1
  else:
    upper=0
  index=alphabet.find(ciphertext[i].lower())
  if (index!=-1):
    if (upper):
      decipherfile.write(alphabet[(index-int(sys.argv[3]))%26].upper())
    else:
      decipherfile.write(alphabet[(index-int(sys.argv[3]))%26])
  else:
    decipherfile.write(ciphertext[i])

cipherfile.close()
decipherfile.close()
