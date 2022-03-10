#!/usr/bin/env python3

# Sample test generator


from random import seed, randint, sample, random, choice
import string
import os
from pathlib import Path
import sys


def number_from(desc):
    """
    "{number}": Return the same number
    "{lo}:{hi}": Return a random number in the closed interval [lo, hi]
    "~{number}": Return a random number in the interval [number // 2, number]
    """

    if '=' in desc:
        _, desc = desc.split('=')

    if ':' in desc:
        lo, hi = map(int, desc.split(':'))
        return randint(lo, hi)

    elif desc.startswith('~'):
        number = int(desc[1:])
        return randint(number // 2, number)

    else:
        return int(desc)


class Input:
    def __init__(self):
        self.cur_arg = 1
        seed(self.next())

    def next(self):
        ix = self.cur_arg
        self.cur_arg += 1
        return sys.argv[ix]


def sub(A, B):
    return A[0] - B[0], A[1] - B[1]


def cross(A, B):
    return A[0] * B[1] - B[0] * A[1]


def rotate(A, B, C):
    """
    return the first point to be the intersection of the two legs
    return the points sorted counter clockwise
    """

    # Find the corner
    P = [A, B, C]
    for i in range(3):
        eq = [0, 0]
        for j in range(3):
            for k in range(2):
                eq[k] += int(P[i][k] == P[j][k])
        if eq == [2, 2]:
            P[0], P[i] = P[i], P[0]
            break

    # Rotate them counter clockwise
    if cross(sub(P[1], P[0]), sub(P[2], P[0])) < 0:
        P[1], P[2] = P[2], P[1]

    return P


def sign(v):
    if v > 0:
        return +1
    elif v < 0:
        return -1
    else:
        return 0


def sample_in_triangle(A, B, C):
    A, B, C = rotate(A, B, C)
    s = max(abs(A[0] - B[0]), abs(A[1] - B[1]))

    x, y = A
    dx = randint(0, s)
    dy = randint(0, s)

    if dx + dy > s:
        dx = s - dx
        dy = s - dy

    nx = x + (sign(B[0] - A[0]) + sign(C[0] - A[0])) * dx
    ny = y + (sign(B[1] - A[1]) + sign(C[1] - A[1])) * dy
    return nx, ny


def main(cin):
    mode = cin.next()

    points = []
    triangles = []

    if mode == 'random':
        # Random set of points and triangles
        n = number_from(cin.next())
        m = number_from(cin.next())
        M = number_from(cin.next())

        for _ in range(n):
            x = randint(-M, M)
            y = randint(-M, M)
            points.append((x, y))

        for _ in range(m):
            x = randint(-M, M)
            y = randint(-M, M)
            s = randint(1, M)
            dx = choice([-1, 1])
            dy = choice([-1, 1])

            if x + dx * s > M or x + dx * s < -M:
                dx *= -1

            if y + dy * s > M or y + dy * s < -M:
                dy *= -1

            triangles.append([
                (x, y),
                (x + dx * s, y),
                (x, y + dy * s),
            ])

    elif mode == 'triangle_first':
        # Creates the triangles, and add points in the interior of this triangles
        n = number_from(cin.next())
        m = number_from(cin.next())
        M = number_from(cin.next())

        for _ in range(m):
            x = randint(-M, M)
            y = randint(-M, M)
            s = randint(1, M)
            dx = choice([-1, 1])
            dy = choice([-1, 1])
            if x + dx * s > M or x + dx * s < -M:
                dx *= -1
            if y + dy * s > M or y + dy * s < -M:
                dy *= -1
            triangles.append([
                (x, y),
                (x + dx * s, y),
                (x, y + dy * s),
            ])

        for _ in range(n):
            tri = choice(triangles)
            points.append(sample_in_triangle(*tri))
    else:
        raise ValueError(f'Invalid mode {mode}')

    print(n, m)
    for x, y in points:
        print(x, y)
    for tri in triangles:
        tri = rotate(*tri)
        print(' '.join('{} {}'.format(x, y) for x, y in tri))


if __name__ == '__main__':
    main(Input())
