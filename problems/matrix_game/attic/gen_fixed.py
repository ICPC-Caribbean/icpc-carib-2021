#!/usr/bin/env python3

# Sample test generator

import sys
import os
import string
from random import seed, randint, sample

# first argument must be seed
seed(sys.argv[1])
MIN = int(sys.argv[2])
MAX = int(sys.argv[3])

n = randint(MIN, MAX)
m = randint(MIN, MAX)
c = randint(MIN, MAX)
q = randint(MIN, MAX)

print(n, m, c, q)

x = randint(1, n)
for i in range(c):
    y = min(i + 1, m)
    print(x, y)

for i in range(q):
    print(m)
