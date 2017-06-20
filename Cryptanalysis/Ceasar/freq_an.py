#!/usr/bin/env python

# Title : Cryptanalysis of Caesar Cipher
# Author : Zweisamkeit
# Created : 07/28/2016
# Last modification : 08/01/2016
# Contact : contact@zweisamkeit.fr
# License : GNU/GPL

# Frequential Analysis
# Errors are managed by the bash wrapper
# To use this program alone, please uncomment the commented line which correspond to error messages
import sys

if (len(sys.argv)!=2):
# print("Arg error: ./freq_an.py [cipherfile]")
  exit(1)

try:
  cipherfile=open(sys.argv[1],"r")
except:
# print("Error: No such file directory")
  exit(2)

ciphertext=cipherfile.read()

frequencies=[]

length=len(ciphertext)

alphabet="abcdefghijklmnopqrstuvwxyz"

# Experimental frequencies

for i in alphabet:
  frequencies.append([i,0])

for i in range (0,len(frequencies)):
  frequencies[i][1]=ciphertext.lower().count(frequencies[i][0])/float(length)*100

#frequencies.sort(key=lambda frequencies:frequencies[1],reverse=True)

# Theorical frequencies
try:
  conf_file=open("dceasar.conf","r")
except:
# print("Error: No such file directory")
  exit(2)
conf_lines=conf_file.readlines()

aux=0

for line in conf_lines: # manage error: no config
  if (line[0] != "#"):
    aux=1
    break

if (aux==0): # Error: No line unsharped
# print("Conf error: No unsharped line")
  exit(3)
elif (line.find("=")==-1): # Bad format
# print("Conf error: Bad format")
  exit(4)
else:
  theorical_frequencies=eval(line.split("=")[1])

# Error: Bad format

if (not (isinstance(theorical_frequencies, list)) or (len(theorical_frequencies)!=26)):
# print("Conf error: Bad format")
  exit(4)
else:
  for i in range (0,26):
    if not ((isinstance(theorical_frequencies[i],float))):
#     print("Conf error: Bad format")
      exit(4)

# Differencies between theorical frequencies and experimental frequencies for each possible shift

averadges_diff=[]

for i in range (0,26):
  tmp_differencies=[]
  for j in range (0,26):
    tmp_differencies.append(abs(theorical_frequencies[j]-(frequencies[(j+i)%26][1])))
  averadges_diff.append(sum(tmp_differencies)/len(tmp_differencies))

# Lower difference = Most probable shift

min=0

for i in range (1,26):
  if (averadges_diff[i]<averadges_diff[min]):
    min=i

probable_shift=min

cipherfile.close()
conf_file.close()

print(probable_shift)
exit(0)
