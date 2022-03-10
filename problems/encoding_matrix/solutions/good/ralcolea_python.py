#!/usr/bin/env python3

# ICPC Qualifier 2021
# Problem Encoding Matrix
# Ad Hoc 1
import sys,os,string

n=int(input())
zeros = 0
ones = 0
star_ones = ""
star_zeros = ""
first = 'a'
for i in range(n):
    s = input()
    if (first == 'a'):
        first = s[0]
    for j in range(n):
        if (s[j] == '0'):
            zeros += 1
            star_ones  += 'o'
            star_zeros += '*'
        elif (s[j] == '1'):
            ones += 1
            star_ones  += '*'
            star_zeros += 'o'

if (zeros > ones or (zeros == ones and first == '0')):
    star_ones = star_zeros

for i in range(n):
    s = ""
    for j in range(n):
        s += star_ones[n * i + j]
    print(s)