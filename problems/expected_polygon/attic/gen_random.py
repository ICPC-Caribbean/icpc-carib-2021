#!/usr/bin/env python3

# Sample test generator


from random import seed, randint, shuffle
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


def main(cin):
    mode = cin.next()

    points = []

    if mode == 'random':
        n = number_from(cin.next())
        M = number_from(cin.next())
        _points = set()
        for _ in range(n):
            while True:
                x, y = randint(-M, M), randint(-M, M)
                if not (x, y) in _points:
                    _points.add((x, y))
                    break
        points = list(_points)

    elif mode == 'grid':
        # Creates the triangles, and add points in the interior of this triangles
        n = number_from(cin.next())
        for i in range(n):
            for j in range(n):
                points.append((i, j))
        shuffle(points)

    elif mode == 'circle':
        n = number_from(cin.next())
        r = number_from(cin.next())

        _points = set()
        for _ in range(n):
            x, y = randint(-r, r), randint(-r, r)
            if x * x + y * y < r * r and not (x, y) in _points:
                _points.add((x, y))
        points = list(_points)

    else:
        raise ValueError(f'Invalid mode {mode}')

    assert len(points) != 0
    print(len(points))
    for x, y in points:
        print(x, y)


if __name__ == '__main__':
    main(Input())
