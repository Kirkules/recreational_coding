# Author: Kirk Boyer
#
# My solution to codewars.com/kata/5a2c084ab6cfd7f0840000e4/python authored by kodejuice.
#
# Description:
# -----------------------------------------------------------------------------------------
# The Prime ant (A293689) is an obstinate animal that navigates the integers and divides them until
# there are only primes left, according to the following procedure:
#
#   An infinite array/list A is initialized to contain all the integers greater than 1: [2, 3, 4, 5, 6, …]
#   Let p be the position of the ant on the array/list. Initially p = 0, so the ant is at A[0] = 2
#   At each turn, the ant moves as follows:
#       - If A[p] is prime, move the ant one position forward, so p ← p + 1
#       - Otherwise (if A[p] is composite):
#           - Let q be its smallest divisor greater than 1
#           - Replace A[p] with A[p] / q
#           - Replace A[p−1] with A[p−1] + q
#           - Move the ant one position backward, so p ← p − 1
#
# Your task is to comlete the function that computes the position of the prime ant after n turns.
# Examples
#
# prime_ant(2)   # => 2
# prime_ant(11)  # => 5
# prime_ant(47)  # => 9
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

from itertools import count, islice


class AntList():
    def __init__(self, initial_length=0):
        self.A_generator = count(2)
        self.A = list(islice(self.A_generator, initial_length))

    def _fill_up_to_n(self, n):
        assert isinstance(n, int)
        if n >= len(self.A):
            # Fill in the entries of A up to `n`
            self.A.extend(islice(self.A_generator, n+1 - len(self.A)))

    def __getitem__(self, index):
        self._fill_up_to_n(index)
        return self.A[index]

    def __setitem__(self, index, value):
        self._fill_up_to_n(index)
        self.A[index] = value


def prime_sieve(n):
    """
    Use sieve of eratosthenes to return True if `n` is prime and False otherwise.

    Side effect: prime_sieve.sieve[n] = smallest divisor of n

    Should really be a class but I'm not super invested in this right now.
    """

    assert isinstance(n, int)
    assert n > 0

    if "sieve" not in prime_sieve.__dict__:
        # The sieve itself, a dict() because iterating over keys is in insertion order, and because this allows
        # storing the smallest divisor we found along the way in checking primality
        prime_sieve.sieve = dict()
        prime_sieve.sieve[2] = 2

    if "highest" not in prime_sieve.__dict__:
        # The highest number that has been a parameter to this function. prime_sieve.sieve is complete up to
        # prime_sieve.highest, i.e. if n < prime_sieve.highest, then prime_sieve(n) is True <==> k is prime
        prime_sieve.highest = 2

    if n < prime_sieve.highest:
        return n == prime_sieve.sieve[n]

    composite = False
    for k in range(prime_sieve.highest+1, n+1):
        for divisor in prime_sieve.sieve:
            if k % divisor == 0:
                prime_sieve.sieve[k] = divisor
                composite = True
                break

        if composite:
            composite = False
            continue

        prime_sieve.sieve[k] = k

    prime_sieve.highest = n

    return n == prime_sieve.sieve[n]


def min_divisor(n):
    # Smallest divisor of any number is always prime; otherwise if k is min s.t. k | n and k = a*b for a, b > 1,
    # then a<k and b<k contradicts minimality of k.
    prime_sieve(n)
    return prime_sieve.sieve[n]


def is_prime(n):
    # If I write a better prime finder than the sieve above, I'll use it here.
    return prime_sieve(n)


def naive_ant(n):
    """
    Just follows the problem description as pseudocode and spits out p
    """
    A = AntList()
    p = 0
    for _ in range(n):
        if is_prime(A[p]):
            p += 1
        else:
            q = min_divisor(A[p])
            A[p] = A[p]//q
            A[p-1] += q
            p -= 1

    return p


def print_highlighted_entry(values, i):
    print("[", end="")
    if i > 0:
        print(*values[:i], sep=", ", end=", ")
    if i < len(values)-1:
        print(*("*", values[i], "*"), sep="", end=", ")
        print(*values[i+1:], sep=", ", end="]\n")
    else:
        print(*("*", values[i], "*"), sep="", end="]\n")


def prime_ant(n):
    # If I write a better prime ant function than the naive one above, I'll use it here.
    return naive_ant(n)


if __name__ == "__main__":
    # tests = [[28, 10],
    #         [11, 5],
    #         [19, 5],
    #         [2, 2],
    #         [12, 4],
    #         [29, 9],
    #         [46, 8],
    #         [463, 229],
    #         ]
    tests = [[51, 11],
             [58, 12],
             [66, 12],
             ]
    for test, expected in tests:
        print(
            f"prime_ant({test}): {prime_ant(test)} \t(expected {expected})\n")

    print(f'Checking again: 14 is {"" if is_prime(14) else "not"} prime')
    print(f'Checking again: 14 is {"" if is_prime(14) else "not"} prime')
    print(f'Checking again: 14 is {"" if is_prime(14) else "not"} prime')
    print(f'Checking again: 14 is {"" if is_prime(14) else "not"} prime')
    print(f'sieve: {prime_sieve.sieve}')
    print(f'highest: {prime_sieve.highest}')
