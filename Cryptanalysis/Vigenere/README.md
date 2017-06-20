# Cryptanalysis of the Chiffre de Vigenère

 * This program can decrypt a message written in french or in english crypted according to the Chiffre de Vigenère.
 
 * First, it performs a pre-treatment of the text, then calculates the probable length of the key by using the index of coincidence and the Friedman test.
 * Then, it determines the encryption key, using a frequency analysis on the ciphertext.
 * Finally, it offers a decrypted version of the message.
 
 * To compile this program, simply run the make command.
 * To execute it, it must pass back a text file containing the encrypted message, the name of a file that will be written the decrypted message, and the two first letters of the original language of the text: ./decrypt_vigenere [encrypted_file] [decrypted_file] [en/fr].

*********************************************************************************************************************************
# Cryptanalyse du Chiffre de Vigenère

 * Ce programme permet de déchiffrer un message rédigé en français ou en anglais codé selon l'algorithme du Chiffre de Vigenère.
 
 * Dans un premier temps, il effectue un prétraitement du texte, puis calcule la longueur probable de la clé en utilisant l'indice de coïncidence et le test de Friedman.
 * Ensuite, il détermine la clé de chiffrement, à l'aide d'une analyse fréquentielle sur le texte chiffré.
 * Enfin, il propose une version déchiffrée du message.
 
 * Pour le compiler, il suffit de lancer la commande make.
 * Pour l'éxecuter, il faut passer en argument un fichier texte contenant le message chiffré, le nom d'un fichier sur lequel sera écrit le message déchiffré, et les deux premières lettres de la langue d'origine du texte : ./decrypt_vigenere [encrypted_file] [decrypted_file] [fr/en].
