#!/usr/bin/env python3
import sys

eps = 1e-7

class Point:
    def __init__(self, x, y, id=0) -> None:
        self.id = id
        self.x = x
        self.y = y

    def __add__(self, p):
        return Point(self.x + p.x, self.y + p.y)
    
    def __sub__(self, p):
        return Point(self.x - p.x, self.y - p.y)

    def __mul__(self, t):
        return Point(self.x * t, self.y * t)

def cross(p, q):
    return p.x * q.y - p.y * q.x

def dot(p, q):
    return p.x * q.x + p.y * q.y

def norm(p):
    return dot(p, p)

def vect_abs(p):
    return norm(p) ** 0.5

def ccw(a, b, c):
    b = b - a
    c = c - a
    if cross(b, c) > 0:
        return +1 # couter clockwise
    if cross(b, c) < 0:
        return -1 # clockwise
    if dot(b, c) < 0:
        return +2 # c--a--b on line
    if norm(b) < norm(c):
        return -2 # a--b--c on line
    return 0

def intersectSP(s, p):
    if abs(cross(s[1] - s[0], p - s[0])) > eps:
        return False
    return vect_abs(s[0] - p) + vect_abs(s[1] - p) - vect_abs(s[1] - s[0]) < eps
    

def crosspoint(l, m):
    A = cross(l[1] - l[0], m[1] - m[0])
    B = cross(l[1] - l[0], l[1] - m[0])
    if abs(A) < eps and abs(B) < eps:
        return m[0]; # same line
    if abs(A) < eps:
        assert(False) # PRECONDITION NOT SATISFIED
    return m[0] + (m[1] - m[0]) * (B / A)

def convex_hull(ps):
    n = len(ps)
    ps.sort(key = lambda pi: [pi.x, pi.y])
    ch = [0] * 2 * n
    k = 0

    for i in range(n):
        while k >= 2 and ccw(ch[k - 2], ch[k - 1], ps[i]) <= 0:
            k -= 1
        ch[k] = ps[i]
        k += 1

    t = k + 1
    for i in range(n-2, -1, -1):
        while k >= t and ccw(ch[k - 2], ch[k - 1], ps[i]) <= 0:
            k -= 1
        ch[k] = ps[i]
        k += 1
        
    return ch[:k - (k > 1)]

def main():
    Input = sys.stdin.readlines()
    Output = []

    cur_line = 0
    def get_line():
        nonlocal cur_line
        cur_line += 1
        return Input[cur_line - 1].strip()

    n = int(get_line())
    p = []
    for i in range(n):
        x, y = map(int, get_line().split())
        p.append(Point(x, y, i+1))

    p = convex_hull(p)
    n = len(p)

    def out(line):
        nonlocal Output
        Output.append(line)

    def check_on_point(a, pi):
        if norm(a - pi) < eps:
            out('1')
            out('{} 1'.format(a.id))
            return True
        return False

    def check_on_segment(a, b, pi):
        if intersectSP([a, b], pi):
            t = vect_abs(pi - a) / vect_abs(b - a)
            out('2')
            out('{id} {val:.20f}'.format(id=a.id, val=(1 - t)))
            out('{id} {val:.20f}'.format(id=b.id, val=t))
            return True
        return False
        
    q = int(get_line())
    for _ in range(q):
        x, y = map(int, get_line().split())
        pi = Point(x, y)
        if n == 1:
            if not check_on_point(p[0], pi):
                out('impossible')
        elif n == 2:
            a, b = p[0], p[1]
            if check_on_point(a, pi) or check_on_point(b, pi):
                continue
            if not check_on_segment(a, b, pi):
                out('impossible')
        else:
            if cross(p[1] - p[0], pi - p[0]) < -eps:
                out('impossible')
                continue
            if cross(p[n-1] - p[0], pi - p[0]) > eps:
                out('impossible')
                continue
            
            lo, hi = 1, n-2
            while lo < hi:
                m = (lo + hi + 1) >> 1
                if cross(p[m] - p[0], pi - p[0]) >= 0:
                    lo = m
                else:
                    hi = m - 1
            
            a, b, c = p[0], p[lo], p[lo+1]
            
            if cross(c - b, pi - b) < -eps:
                out('impossible')
                continue

            if check_on_point(a, pi) or check_on_point(b, pi) or check_on_point(c, pi):
                continue

            if check_on_segment(a, b, pi) or check_on_segment(b, c, pi) or check_on_segment(a, c, pi):
                continue

            d = crosspoint([b, pi], [a, c])
            t = vect_abs(pi - b) / vect_abs(d - b)
            k = vect_abs(d - a) / vect_abs(c - a)

            out('3')
            out('{id} {val:.20f}'.format(id=a.id, val=(t * (1-k))))
            out('{id} {val:.20f}'.format(id=b.id, val=(1 - t)))
            out('{id} {val:.20f}'.format(id=c.id, val=(t * k)))

    print('\n'.join(Output))

if __name__ == '__main__':
    main()
