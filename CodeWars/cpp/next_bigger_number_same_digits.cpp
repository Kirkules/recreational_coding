// Author: Kirk Boyer
//
// My solution to www.codewars.com/kata/55983863da40caa2c900004e/cpp authored by GiacomoSorbi.
//
// Description:
// -----------------------------------------------------------------------------------------
// Create a function that takes a positive integer and returns the next bigger number that can be
// formed by rearranging its digits. For example:
//
//   12 ==> 21
//  513 ==> 531
// 2017 ==> 2071
//
// If the digits can't be rearranged to form a bigger number, return -1 (or nil in Swift, None in Rust):
//
//   9 ==> -1
// 111 ==> -1
// 531 ==> -1
//
// -----------------------------------------------------------------------------------------
//
// Discussion:
//
// Let i and j be indices of digits, where the i^th digit is the coefficient of 10^i in the decimal expansion
// of the given number.
//
// If a number has an inverted pair of digits d_i > d_j with i < j, then swapping d_i and d_j yields a larger
// number, since d_i*10^i + d_j*10^j = (d_i*10^(j-i) + d_j)*10^i < (d_j*10^(j-i) + d_i)*10^i.
//
// The smallest increase available from a single swap is when max(i, j) above is smallest.
//
// But after that single swap, we need to decrease the value as much as possible while remaining larger than the
// original input value, and we can do this by swapping at indices i', j' < max(i, j). We make the largest such
// increase, then search again
//
// Knowing this, we find the first swap to make by iterating over i, j pairs such that max(i, j) is
// nondecreasing and doesn't skip any pairs.

#include <iostream>
#include <string>

// Returns the leftmost index of the swap made within digits[left:] to increase the value of digits.
std::optional<int> swapLarger(std::string& digits, int left)
{
    std::optional<int> minimal;
    for (int j = digits.size() - 1; j >= left; --j) {
        for (int i = j + 1; i < digits.size(); ++i) {
            if (digits[j] < digits[i]) {
                if (minimal.has_value()) {
                    minimal = digits[i] < digits[*minimal] ? i : minimal;
                } else {
                    minimal = i;
                }
            }
        }
        if (minimal.has_value()) {
            std::cout << "swapLarger, left=" << left << ":in\t" << digits << ", " << digits[*minimal] << " <-> " << digits[j] << std::endl;
            std::swap(digits[*minimal], digits[j]);
            std::cout << "yielding\t\t" << digits << std::endl;
            return j;
        }
    }
    return std::nullopt;
}

// Returns the leftmost index of the swap made within digits[left:] to maximally decrease the value of digits.
std::optional<int> swapSmaller(std::string& digits, int left)
{
    std::optional<int> maximal;
    for (int j = left; j < digits.size(); ++j) {
        for (int i = digits.size() - 1; i > j; --i) {
            if (digits[j] > digits[i]) {
                if (maximal.has_value()) {
                    maximal = digits[i] < digits[*maximal] ? i : maximal;
                } else {
                    maximal = i;
                }
            }
        }
        if (maximal.has_value()) {
            std::swap(digits[*maximal], digits[j]);
            return j;
        }
    }
    return std::nullopt;
}

long nextBigger(long n)
{
    std::string digits = std::to_string(n);

    std::optional<int> swap_found_at = swapLarger(digits, 0);
    if (!swap_found_at.has_value()) {
        return -1;
    }

    int left = *swap_found_at + 1;
    while (-1 < left && left < digits.size()) {
        swap_found_at = swapSmaller(digits, left);

        if (!swap_found_at.has_value()) {
            // No swap found for some subsequent iteration, so try again smaller
            left += 1;

        } else {
            // Look for the next swap to the right of the one we just found.
            left = *swap_found_at + 1;
        }
    }

    return std::stol(digits);
}
