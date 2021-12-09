#!/usr/bin/python3

import sys

l = [[hex(32) for i in range (16)] for i in range(256)]

for i in range (0,256):
	l[i][5] = hex(i)

print(l)
