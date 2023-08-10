// Author: Kirk Boyer
//
// My solution to www.codewars.com/kata/5511b2f550906349a70004e1/cpp authored by dburgoyne.
//
// Description:
// -----------------------------------------------------------------------------------------
// Define a function that takes in two non-negative integers a and b and returns the last decimal
// digit of a^b. Note that aaa and bbb may be very large!
//
// For example, the last decimal digit of 9^7 is 9, since 9^7 = 4782969.
// The last decimal digit of (2^200)^(2^300), which has over 109210^{92}1092
// decimal digits, is 666. Also, please take 0^0 to be 1
//
// You may assume that the input will always be valid.
// Examples
//
// last_digit("4", "1")            // returns 4
// last_digit("4", "2")            // returns 6
// last_digit("9", "7")            // returns 9
// last_digit("10","10000000000")  // returns 0
//
// -----------------------------------------------------------------------------------------
//
// Discussion:
//
// The last digit of x is y = x (mod 10), and the last digit of x^20 is x^20 (mod 10) = y^20 (mod 10).
//
// Repeatedly multiplying a number 1-10 by itself (mod 10) just iterates through a cycle of last digits. The cycles:
// 1: (1)
// 2: (2, 4, 8, 6)
// 3: (3, 9, 7, 1)
// 4: (4, 6)
// 5: (5)
// 6: (6)
// 7: (7, 9, 3, 1)
// 8: (8, 4, 2, 6)
// 9: (9, 1)
// 0: (0)
//
//
// Raising these numbers to a power n thus yields the (n-1 (mod k)) element of the cycle.
//
// Applying to the examples above, 9^7 and (2^200)^(2^300):
//
// 9 (mod 10) is 9, and the cycle for 9 is (9, 1) which has length 2. 7-1 (mod 2) = 0, so the last digit of 9^7
// the 0th element of (9, 1), or 9.
//
// The last decimal digit of 2^300 is the 300-1 (mod 4) = 3rd element of (2, 4, 8, 6), or 8. The last decimal digit of
// 2^200 is similarly 8. So the last decimial digit of (2^200)^(2^300) is the same as the last digit of 8^8, which is 6.
//
//
// Since the c++ input values are strings, instead of doing modular arithmetic to get the last digits of the inputs,
// we just convert the last parts of the strings to numbers directly.
//
// For (mod 10), just convert the last character to an int by subtracting the '0' character's value
// (since ascii characters for numbers are contiguous and in order).
//
// For (mod 4), the last digit isn't enough to see the whole number's value (mod 4); e.g. 12 (mod 4) = 0, but 2 (mod 4) = 2.
// On the other hand, the last two digits are enough, because every higher power is a multiple of 100 which itself
// is a multiple of 4. In other words, the decimal representation of any number is 1*d_1 + 10*d_2 + 100*d_3 + ..., where
// d_i is the i^th digit, so all the terms for i>2 are equivalent to 0 (mod 4), and we only need to look at the smallest 2
// digits.
//

#include <string>
#include <unordered_map>
#include <vector>

const std::unordered_map<int, std::vector<int>> CYCLES = {
    { 0, std::vector<int> { 0 } },
    { 1, std::vector<int> { 1 } },
    { 2, std::vector<int> { 2, 4, 8, 6 } },
    { 3, std::vector<int> { 3, 9, 7, 1 } },
    { 4, std::vector<int> { 4, 6 } },
    { 5, std::vector<int> { 5 } },
    { 6, std::vector<int> { 6 } },
    { 7, std::vector<int> { 7, 9, 3, 1 } },
    { 8, std::vector<int> { 8, 4, 2, 6 } },
    { 9, std::vector<int> { 9, 1 } }
};

int last_digit(const std::string& str1, const std::string& str2)
{
    if (str2 == "0") {
        return 1;
    }

    // Use the last digits of the input.
    int base = str1.back() - '0';
    int pow = str2.back() - '0';
    if (str2.size() > 1) {
        pow = std::stoi(str2.substr(str2.size() - 2, 2), nullptr);
    }
    auto cycle = CYCLES.at(base);
    return cycle[(pow - 1) % cycle.size()];
}
