#!/usr/bin/env python2.7

# Sample test generator

import sys,os,string
from random import seed, randint, sample

# first argument must be seed
seed(sys.argv[1])
N=int(sys.argv[2])

n = N
print n
zeros = (n * n) / 2
ones  = zeros
for i in range(n):
    s = ""
    for j in range(n):
        bit = randint(1,n) % 2
        if bit == 1:
            if ones > 0:
                ones -= 1
                s += '1'                
            else:
                zeros -= 1
                s += '0'
        elif bit == 0:
            if zeros > 0:
                zeros -= 1
                s += '0'                
            else:
                ones -= 1
                s += '1'
    print s
