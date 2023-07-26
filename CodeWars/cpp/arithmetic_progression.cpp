// Author: Kirk Boyer
//
// My solution to www.codewars.com/kata/52de553ebb55d1fca3000371/cpp authored by Coldberg.
//
// Description:
// -----------------------------------------------------------------------------------------
//
// An Arithmetic Progression is defined as one in which there is a constant difference between
// the consecutive terms of a given series of numbers. You are provided with consecutive elements
// of an Arithmetic Progression. There is however one hitch: exactly one term from the original
// series is missing from the set of numbers which have been given to you. The rest of the given
// series is the same as the original AP. Find the missing term.
//
// You have to write a function that receives a list, list size will always be at least 3 numbers.
// The missing term will never be the first or last one.
//
// -----------------------------------------------------------------------------------------
//
// Discussion:
//
// There can only be two consecutive-term differences that appear in the given list, one which is wrong for the AP
// and another which is correct (which is also possibly repeated).
//
// If a, b (in that order) are the consecurive numbers with difference b-a that is not the AP's difference D,
// then since only one term in the AP is missing between a and b, b-a = 2D, because if c is the missing term between
// a and b, then c-a = D and b-c = D, and b-a = c-a + b-c.
//
// This means that we can iterate over the list, tracking differences between consecutive terms, until we see two
// distinct differences. The larger (in absolute value) difference will be the incorrect one, so we
// add the other difference to the first list item leading to the incorret difference to get the missing term.
//
// At that point we have the answer and can stop looking.
//
//
// Meta-Discussion:
//
// This feels like a project euler question because the correct solution isn't an algorithm implementation
// so much as a sort of recognition of a deeper understanding of the problem.

#include <cstdlib>

// Since this is CodeWars, skip validation like checking the list size is at least 3 as promised.
static long findMissing(std::vector<long> list)
{
    long d = list[1] - list[0];
    long d2 = d;
    for (int i = 1; i < list.size(); ++i) {
        d2 = list[i] - list[i - 1];
        // If we just found the second distinct difference d2,
        if (d2 != d) {
            // and it (d2) is larger,
            if (std::abs(d2) > std::abs(d)) {
                // then the missing term is in the gap we just examined,
                // and is d larger than the lower term.
                return list[i - 1] + d;
            }
            // and it(d2) is smaller,
            else {
                // then the missing term is in the gap leading to difference d, which
                // is from the first pair of items in the list.
                return list[0] + d2;
            }
        }
    }
}
