#!/usr/bin/env python3
def main():
    n, k = map(int, input().split())

    res = 0
    for i in range(1, n + 1):
        s = 0
        u = i
        j = 2
        while j * j <= u:
            while u % j == 0:
                s += j
                u //= j
            j += 1
        if u > 1:
            s += u
        res += int(s <= k)
    print(res)


if __name__ == '__main__':
    main()
