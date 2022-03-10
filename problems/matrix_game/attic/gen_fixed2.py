#!/usr/bin/env python3

# Sample test generator

import sys
import os
import string
from random import seed, shuffle

# first argument must be seed
seed(sys.argv[1])

n = int(sys.argv[2])
m = int(sys.argv[3])
c = int(sys.argv[4])
q = m

SHUFFLED = len(sys.argv) > 5 and int(sys.argv[5]) != 0

coins = [(n, min(i + 1, m)) for i in range(c)]
queries = list(range(1, m+1))

if SHUFFLED:
   shuffle(coins)
   shuffle(queries)

print(n, m, c, q)
print('\n'.join( ("%d %d" % (x, y) for (x, y) in coins) ) )
print('\n'.join(map(str, queries)))

