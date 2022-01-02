#!/usr/bin/python3

import sys

l = [['{:x}'.format(103) for i in range (16)] for i in range(256)]

for i in range (0,256):
	l[i][5] = '{:x}'.format(i)




for i in range (0,256):
	ligne = ""
	for j in range (0,16):
		ligne += l[i][j] 
	sys.stdout=open("lambda_set6.txt","a")
	print(ligne)
	sys.stdout.close()
