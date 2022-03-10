#!/usr/bin/env python3
# encoding: utf-8
import sys

line_count = 0

polygon = []
queries = []
MAX = 10**9

for line in sys.stdin.readlines():
    line_count += 1
    line = line.strip('\n')

    if line_count == 1:
        n = int(line)
        assert 1 <= n <= 10**5

    elif line_count <= n + 1:
        x, y = map(int, line.split())
        assert 0 <= x <= MAX and 0 <= y <= MAX, "Coordinates in range"
        # Convert to complex number
        polygon.append(x + 1j * y)
    
    elif line_count == n + 2:
        q = int(line)
        assert 0 <= q <= 10**4

    else:
        x, y = map(int, line.split())
        assert 0 <= x <= MAX and 0 <= y <= MAX, "Coordinates in range"
        queries.append(x + 1j * y)
        
assert line_count == n + q + 2