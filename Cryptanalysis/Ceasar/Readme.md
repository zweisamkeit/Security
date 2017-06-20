#Cryptanalysis of Ceasar Cipher

* This program allows to decrypt a text encrypted according to the Ceaser Cipher;
* The program dceaser.py can decrypt a message in a given shift, the program freq_an.py calcule the probable shift, and the bash wrapper allows to try all the possible shifts;
* To decrypt a cipher text encrypted according to the Ceaser Cipher without knowing the shift value, you have to:
  * Remove the sharp from the beginning of the line corresponding to the language in which the text was written (default: french);
  * Start the following commands: chmod u+x dceaser_wrapper.sh && ./dceaser_ac.sh [cipherfile].
