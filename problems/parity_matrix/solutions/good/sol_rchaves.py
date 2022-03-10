#!/usr/bin/env python3
def main():
    r, c = map(int, input().split())
    mat = [[int(x) for x in input().split()] for _ in range(r)]
    rows = []
    cols = []
    for i in range(r):
        if sum(mat[i]) % 2:
            rows.append(i)
    for j in range(c):
        if sum(mat[i][j] for i in range(r)) % 2:
            cols.append(j)
    while rows or cols:
        if rows and cols:
            row = rows[-1]
            col = cols[-1]
            rows.pop()
            cols.pop()
        elif rows:
            row = rows[-1]
            col = 0
            rows.pop()
            cols.append(0)
        else:
            row = 0
            col = cols[-1]
            rows.append(0)
            cols.pop()
        mat[row][col] += 1
    for i in range(r):
        print(' '.join(map(str, mat[i])))


main()
