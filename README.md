# SquareAttackAES

#AES

matrice 4x4

Fonction initialisation qui prend un message de 128 bits et le met dans une matrice de taille 4x4

Fonction AddRoundKey prend en entrée une matrice et un sous-clef K_i de 128 bits et renvoie le XOR des deux

Fonction KeySchedule prend en entrée une clef et renvoie les sous-clefs K_i   

Fonction SubBytes prend en entrée une matrice et renvoie la matrice passée dans une Sbox

Fonction ShiftRows prend une matrice et renvoie la matrice shiftée vers la gauche sur les lignes

Fonction MixColumns prend une matrice et renvoie la matrice multipliée par une matrice définie 

Fonction Tour qui appelle les fonctions SubBytes, ShiftRows, MixColumns et AddRoundKey dans cet ordre

#Attaque

Fonction SubBytesInv qui prend en entrée un tableau de 256 chiffrés et renvoie ces messages passés par la SboxInv

Fonction TestCell qui prend en entrée une liste de 256 matrices et renvoie true si elles sont équilibrées

deuxième test
