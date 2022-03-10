#!/usr/bin/env python3
t = int(input())
for _ in range(t):
    p, k, m = map(int, input().split())
    val = (m - k + p - 1)//p
    if val <= -1:
        print(1)
    elif val <= 0:
        print(2)
    else:
        print(val + val % 2)
