#!/usr/bin/env python3

matrix = []

z = 0
o = 0
for _ in range(int(input())):
    row = input()
    z += row.count('0')
    o += row.count('1')
    matrix.append(row)

zc = '*'
oc = 'o'
if o > z:
    zc, oc = oc, zc

for row in matrix:
    row = row.replace('0', zc)
    row = row.replace('1', oc)
    print(row)
