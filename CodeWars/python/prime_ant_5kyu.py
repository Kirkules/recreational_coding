# Author: Kirk Boyer
#
# My solution to codewars.com/kata/5a2e96f1c5e2849eef00014a/python authored by kodejuice.
#
# Description:
# -----------------------------------------------------------------------------------------
# The "prime ant" is an obstinate animal that navigates the integers and divides them until there
# are only primes left!
#
# Initially, we have an infinite array A containing all the integers >= 2 : [2, 3, 4, 5, 6, ... ]
#
# Let p be the position of the ant on the array. Initially, p = 0 (the array is 0-indexed)
#
# Each turn, the ant will move as follows:
#
#     if A[p] is prime, the ant moves to the next position : p += 1
#     else, if A[p] is a composite number, let q be its smallest divisor > 1. We divide A[p] by q,
#       and we add q to A[p-1]. The ant moves to the previous position: p -= 1
#
# Here are the first moves for the ant:
#
# 2  3  4  5  6  7  8  9  ...    # 2 is prime: go on
# ^
# 2  3  4  5  6  7  8  9  ...    # 3 is prime: go on
#    ^
# 2  3  4  5  6  7  8  9  ...    # 4 is composite: go back and update
#       ^
# 2  5  2  5  6  7  8  9  ...    # 5 is prime: go on
#    ^
# 2  5  2  5  6  7  8  9  ...    # 2 is prime: go on
#       ^
# 2  5  2  5  6  7  8  9  ...    # 5 is prime: go on
#          ^
# etc.
#
# Your task
#
# Your function should return the full list of integers up to (and including) the ant's position
# after n moves (that is A[0 .. p+1])
#
#
# -----------------------------------------------------------------------------------------
#
# Discussion:
#
# Most of the concepts here are self explanatory. You need a prime number checker and a smallest divisor finder.
#
# I implemented is_prime with a lazy sieve of eratosthenes, and cached the results with a dict so that instead of just
# recording whether a number is prime, I record its minimum divisor, for use elsewhere, since in building the sieve
# you check primality by checking for a prime divisor starting with 2 and going to larger primes
#
# Doing more caching and minimizing repeated computation for the "performance" version. Also stopping at sqrt(n) when
# looking for divisors
#

from itertools import count, islice
from math import sqrt


class AntList():
    def __init__(self, initial_length=0):
        self.A_generator = count(2)
        self.A = list(islice(self.A_generator, initial_length))

    def _fill_up_to_n(self, val):
        if isinstance(val, int):
            if val >= len(self.A):
                # Fill in the entries of A up to `n`
                self.A.extend(islice(self.A_generator, val+1 - len(self.A)))
        elif isinstance(val, slice):
            self._fill_up_to_n(val.stop)

    def __getitem__(self, index):
        self._fill_up_to_n(index)
        return self.A[index]

    def __setitem__(self, index, value):
        self._fill_up_to_n(index)
        self.A[index] = value


class LazySieve():
    """
    Sort of like the Sieve of Eratosthenes, but lazy and mildly optimized.
    """

    def __init__(self):
        self.primes = dict()
        self.composites = dict()

        self.primes[2] = 2
        self.highest_checked = 2

    def is_prime(self, n):
        if n < self.highest_checked:
            return n in self.primes

        for k in range(self.highest_checked+1, n+1):
            for divisor in islice(self.primes.keys(), int(sqrt(k))):
                if k % divisor == 0:
                    self.composites[k] = divisor
                    break

            if k in self.composites:
                continue

            self.primes[k] = None

        self.highest_checked = n

        return n in self.primes

    def min_divisor(self, n):
        if self.is_prime(n):
            return n

        return self.composites[n]


class NaiveAnt():
    def __init__(self):
        self.sieve = LazySieve()
        self.A = AntList()
        self.ending_position = dict()

    def crawl(self, n):
        # We won't have to recompute if A[n] is prime, because the ant will never go left(/down) in this case.
        if n < len(self.ending_position) and self.sieve.is_prime(self.A[n]):
            return self.A[:(self.ending_position[n])]
        else:
            self.A = AntList()

        last_n = len(self.ending_position) - 1

        p = self.ending_position[last_n] if self.ending_position else 0
        for i in range(len(self.ending_position), n+1):
            if self.sieve.is_prime(self.A[p]):
                p += 1
            else:
                q = self.sieve.min_divisor(self.A[p])
                self.A[p] = self.A[p]//q
                self.A[p-1] += q
                p -= 1

            self.ending_position[i] = p

        return self.A[:(p+1)]


def prime_ant(n):
    if "ant" not in prime_ant.__dict__:
        prime_ant.ant = NaiveAnt()

    return prime_ant.ant.crawl(n)


if __name__ == "__main__":
    tests = [[10000, 72],
             [100000, 932],
             [1000000, 7161],
             ]
    for test, expected in tests:
        print(
                f"prime_ant({test})[-1]: {prime_ant(test)[-1]} \t(expected {expected})\n")

    longtests = [
            [19948, 909, -10, [2, 5, 3, 7, 3, 3, 2, 2, 7, 3]],
            [44499, 1810, -10, [3, 5, 2, 2, 3, 2, 5, 2, 3, 2]],
            [10000000, 233369, -10, [2, 2, 2, 7, 2, 3, 2, 7, 2, 4]],
            ]

    for test, expected_length, last_n, expected_last_n in longtests:
        result = prime_ant(test)
        print(
                f"prime_ant({test}): length= {len(result)}(exp:{expected_length}) \tprime_ant({test})[{last_n}:] = {result[last_n:]}(exp: {expected_last_n}) \n")
