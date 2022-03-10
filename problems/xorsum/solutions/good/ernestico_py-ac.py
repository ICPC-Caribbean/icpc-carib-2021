#!/usr/bin/env python3
# encoding: utf-8
import sys

def get_best_with_2(a, b):
    ret = 0
    for i in range(30):
        if (a&(1<<i)) == (b&(1<<i)):
            ret += 2 * (1<<i)
        else: 
            ret += 3 * (1<<i)
    return ret

def get_best_with_1(a, b):
    ret = 0
    for i in range(30):
        if (a&(1<<i)) == (b&(1<<i)):
            ret += 2 * (1<<i)
        else: 
            ret += 1 * (1<<i)
    return ret


if __name__ == '__main__':
    Input = sys.stdin.readlines()
    n = int(Input[0].strip())
    a = list(map(int, Input[1].strip().split()))

    v = (1<<30) - 1

    if n == 2:
        print(v)
        exit(0)
    if n == 3:
        print(2*v)
        exit(0)
    
    pref, suff = [0] * n, [0] * n
    for i in range(1, n):
        pref[i] = pref[i-1] + (a[i-1] ^ a[i])
    for i in range(n-2, -1, -1):
        suff[i] = suff[i+1] + (a[i] ^ a[i+1])
    
    ans = pref[n-1]
    
    ans = max(ans, suff[2], pref[n-3]) + 2*v;
    for i in range(1, n-2):
        ans = max(ans, pref[i-1] + suff[i+2] + get_best_with_2(a[i-1], a[i+2]))
    
    dp = [0] * n
    dp[0] = v
    ans = max(ans, suff[1] + v)
    for i in range(1, n):
        dp[i] = pref[i-1]
        if i < n-1:
            dp[i] += get_best_with_1(a[i-1], a[i+1])
        else:
            dp[i] += v

        ans = max(ans, dp[i] + (0 if i == n-1 else suff[i+1]))

        if i > 1:
            ans = max(ans, dp[i-2] + (v if i == n-1 else get_best_with_1(a[i-1], a[i+1]) + suff[i+1]))

        if i < n-1:
            dp[i] = max(dp[i], dp[i-1] + (0 if i == n-1 else a[i] ^ a[i+1]))

    print(ans)
