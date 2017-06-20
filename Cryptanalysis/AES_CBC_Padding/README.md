# AES128 - CBC Padding Oracle Attack

* This program allows to carry out an AES128 - CBC Padding Oracle Attack on a vulnerable server
* It works only with servers which are using the AES128 encryption (but it's pretty easy to modify it to work with other algorithms: you just have to change the size of the blocks)
* To use it, you just have to start the following command: ./acpadora [Hostname] [Port] [Ciphertext] [Initialization Vector] [Pad Error Message]

* If you don't know anything about this attack, you should read this very good paper: https://blog.skullsecurity.org/2013/padding-oracle-attacks-in-depth, and the exemple which is in the same blog.
