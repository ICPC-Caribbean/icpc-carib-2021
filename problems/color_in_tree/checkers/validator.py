#!/usr/bin/env python3
# encoding: utf-8
import sys

MAX = 10**5
MAX_COLORS = 64

line_count = 0

p = {}
size = {}

def create_disjointSet(n):
    for i in range(n):
        p[i] = i
        size[i] = 1

def find(v):
    if v == p[v]:
        return v
    p[v] = find(p[v])
    return p[v]

def union(a, b):
    a = find(a)
    b = find(b)

    if a != b:
        if size[a] != size[b]:
            a, b = b, a
            p[b] = a
            size[a] += size[b]

for line in sys.stdin.readlines():
    line_count += 1
    line = line.strip('\n')

    if line_count == 1:
        n, q = map(int, line.split())
        assert 1 <= n <= MAX and 1 <= q <= MAX, "n and q in range"
        create_disjointSet(n)

    elif line_count == 2:
        colors = map(int, line.split(' '))
        for c in colors:
            assert 0 <= c < MAX_COLORS, "Color in range"
    
    elif line_count >= 3 and line_count <= n + 1:
        a, b = map(int, line.split())
        assert 1 <= a <= n and 1 <= b <= n, "edge vertices in range"
        assert find(a - 1) != find(b - 1), "graph must be a tree"
        union(a - 1, b - 1)

    else:
        queries = map(int, line.split(' '))
        curr_pos = 0
        for value in queries:
            if (curr_pos == 0):
                assert 1 <= value <= 2, "query type in range"
            elif (curr_pos == 1):
                assert 1 <= value <= n, "query vertex in range"
            elif (curr_pos == 2):
                assert 0 <= value < MAX_COLORS, "query color in range"
            curr_pos += 1
        
assert line_count == n + q + 1