# AES
Implémentation de l'AES:
-aes.c

# SquareAttackAES 4 tour
Cette attaque à clairs choisis permet de déterminer la clé utilisée lors d'un chiffrement AES sur 4 tours.
Afin de mener à bien cette attaque, il est nécessaire de posséder 2 lambdaSets chiffrés avec une même clé. 

Implémentaion de l'attaque:
-attaque4.c
//Ne prends rien en entrée et affiche en sortie la clé initiale utilisée lors du chiffrement des 2 lambdaSets forunis, ainsi que la clé de tour 4 de celle ci.

Les 2 lambdaSets chiffrés fournis sont :
-AES4_ciphered_set_1_key_B.txt
-AES4_ciphered_set_2_key_B.txt



# SquareAttackAES 5 tour
Cette attaque à clairs choisis permet de déterminer la clé utilisé lors d'un chiffrement AES sur 5 tours.
Afin de mener à bien cette attaque, il est nécessaire de posséder 6 lambdaSets chiffrés avec une même clé. 

Implémentation de l'attaque:
-attaque5.c
//Ne prends rien en entrée et affiche en sortie la clé initiale utilisée lors du chiffrement des 6 lambdaSets forunis, ainsi que la clé de tour 5 de celle ci.

Les 6 lambdaSets chiffrés fournis sont :
-AES5_ciphered_set_1_key_C.txt
-AES5_ciphered_set_2_key_C.txt
-AES5_ciphered_set_3_key_C.txt
-AES5_ciphered_set_4_key_C.txt
-AES5_ciphered_set_5_key_C.txt
-AES5_ciphered_set_6_key_C.txt

