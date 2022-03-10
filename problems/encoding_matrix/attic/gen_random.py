#!/usr/bin/env python2.7

# Sample test generator

import sys,os,string
from random import seed, randint, sample

# first argument must be seed
seed(sys.argv[1])
N=int(sys.argv[2])

n = N
print n
for i in range(n):
    s = ""
    for j in range(n):
        s += str(randint(1,n) % 2)
    print s
