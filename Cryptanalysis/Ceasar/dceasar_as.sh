# Title : Cryptanalysis of Caesar Cipher
# Author : Zweisamkeit
# Created : 07/28/2016
# Last modification : 08/02/2016
# Contact : contact@zweisamkeit.fr
# License : GNU/GPL

#!/bin/bash

if [ $# -ne 1 ]
then
  echo -e "\n  Arg error: ./dceasar_as.sh ciphertext\n"
  exit
fi

if [ ! -e $1 ]
then
  echo -e "\n  Error: No such file directory\n"
  exit
fi

clear

echo -e "\n"
echo -e "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
echo -e "\tCryptanalysis of the Ceasar Cipher"
echo -e "\t        Zweisamkeit -- 2016       "
echo -e "\t          License GNU/GPL"
echo -e "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
echo -e "\n"

chmod u+x dceasar.py
rm -r Results/* 2>/dev/null
mkdir -p Results

echo -e "\n Launching the brutforce attack..."

for i in `seq 0 25`
do
  echo -e "\tDecryption with the offset `expr $i + 1 `..."
  touch Results/deciphertext_${i}
  ./dceasar.py $1 Results/deciphertext_${i} $i
  echo -e "\n  Shift value = $i:\n `head -n 1 Results/deciphertext_${i}`" >> Results/Overview
done

echo -e "\n Brutforce attack endend"

chmod u+x freq_an.py

echo -e "\n Launching the frequential analysis"

probable_shift=`./freq_an.py $1`

echo -e "\n Frequential analysis ended"

echo -e "\n Attack ended"

case $? in

3)
  echo -e "\n  Conf error: No line unsharped. Please edit dceaser.conf -> see Readme.md\n"
  exit
  ;;
4)
  echo -e "\n  Conf error: Bad format. Please edit dceaser.conf -> see Readme.md\n"
  exit
  ;;
esac

echo -e "\n  The probable shift is ${probable_shift}\n\n  Overview for the probable shift:\n\n\t`head -n 1 Results/deciphertext_${probable_shift}`\n\n"

echo -ne "  Do you want to see all the text for this shift (1),\n\n  or an overiew of the other results (2)? [1/2/exit] "

read response

case $response in

"1")
  echo -e "\n\n"
  cat Results/deciphertext_${probable_shift} | sed -e 's/^/  /g'
  echo -e "\n\n"
  ;;
"2")
  echo -e "\n\n"
  cat Results/Overview | sed -e 's/^/  /g' | more
  echo -e "\n\n"
  ;;
esac
