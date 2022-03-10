#!/usr/bin/env python3
import sys
input = sys.stdin.readline


def main():
    t = int(input())

    for _ in range(t):
        n, a, b = map(int, input().split())

        if a + b > n:
            print('No')
            continue

        mk = {}
        men_partners = [[] for _ in range(n)]
        in_deg = [0] * n

        j = 0
        for i in range(n):
            for _ in range(a):
                men_partners[i].append(j + 1)
                mk[(i, j)] = 1
                in_deg[j] += 1
                j = (j + 1) % n

        women_partners = [[] for _ in range(n)]

        for j in range(n):
            for i in range(n):
                if (i, j) not in mk:
                    women_partners[j].append(i + 1)

                    if len(women_partners[j]) == b:
                        break

        print('Yes')
        for i in range(n):
            print(' '.join(map(str, men_partners[i])))

        for i in range(n):
            print(' '.join(map(str, women_partners[i])))


main()
