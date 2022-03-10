#!/usr/bin/env python3

def cross(x1, y1, x2, y2):
    return x1 * y2 - y1 * x2


def inside(x, y, x1, y1, x2, y2, x3, y3):
    return \
        cross(x2 - x1, y2 - y1, x - x1, y - y1) >= 0 and \
        cross(x3 - x2, y3 - y2, x - x2, y - y2) >= 0 and \
        cross(x1 - x3, y1 - y3, x - x3, y - y3) >= 0


def main():
    n, q = map(int, input().split())

    points = [
        tuple(map(int, input().split())) for _ in range(n)
    ]

    for _ in range(q):
        vertex = list(map(int, input().split()))
        answer = 0
        for x, y in points:
            answer += int(inside(x, y, *vertex))
        print(answer)


if __name__ == '__main__':
    main()
