#!/usr/bin/env python3
# encoding: utf-8
import sys

MAX = 10**5

line_count = 0


for line in sys.stdin.readlines():
    line_count += 1
    line = line.strip('\n')

    if line_count == 1:
        n, m, c, q = map(int, line.split())
        assert 1 <= n <= MAX and 1 <= m <= MAX and 1 <= c <= MAX and 1 <= q <= MAX, "n, m, c and q in range"

    elif 2 <= line_count <= c + 1:
        x, y = map(int, line.split(' '))
        assert 1 <= x <= n and 1 <= y <= m, "Cell coordinates in range"

    elif c + 2 <= line_count <= c + q + 1:
        r = int(line)
        assert 1 <= r <= m, "Game column in range"

assert line_count == c + q + 1
