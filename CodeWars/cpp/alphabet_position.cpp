// Author: Kirk Boyer
//
// My solution to www.codewars.com/kata/546f922b54af40e1e90001da/cpp authored by MysteriousMagenta.
//
// Description:
// -----------------------------------------------------------------------------------------
//
// In this kata you are required to, given a string, replace every letter with its position in the alphabet.
//
// If anything in the text isn't a letter, ignore it and don't return it.
//
// "a" = 1, "b" = 2, etc.
//
// Example:
//
// alphabet_position("The sunset sets at twelve o' clock.")
//
// Should return "20 8 5 19 21 14 19 5 20 19 5 20 19 1 20 20 23 5 12 22 5 15 3 12 15 3 11" ( as a string )
//
// -----------------------------------------------------------------------------------------
//
// Discussion:
//
// Not much to discuss here; I chose to make a const hash map for fast lookups and made the value type
// a std::string instead of an int so that I wasn't repeatedly converting int to string for output.
//
// I also used the iterator returned by unordered_map.find instead of doing a second lookup for each character.

#include <sstream>
#include <string>
#include <unordered_map>

const std::unordered_map<char, std::string> POSITION = {
    { 'a', "1" }, { 'A', "1" },
    { 'b', "2" }, { 'B', "2" },
    { 'c', "3" }, { 'C', "3" },
    { 'd', "4" }, { 'D', "4" },
    { 'e', "5" }, { 'E', "5" },
    { 'f', "6" }, { 'F', "6" },
    { 'g', "7" }, { 'G', "7" },
    { 'h', "8" }, { 'H', "8" },
    { 'i', "9" }, { 'I', "9" },
    { 'j', "10" }, { 'J', "10" },
    { 'k', "11" }, { 'K', "11" },
    { 'l', "12" }, { 'L', "12" },
    { 'm', "13" }, { 'M', "13" },
    { 'n', "14" }, { 'N', "14" },
    { 'o', "15" }, { 'O', "15" },
    { 'p', "16" }, { 'P', "16" },
    { 'q', "17" }, { 'Q', "17" },
    { 'r', "18" }, { 'R', "18" },
    { 's', "19" }, { 'S', "19" },
    { 't', "20" }, { 'T', "20" },
    { 'u', "21" }, { 'U', "21" },
    { 'v', "22" }, { 'V', "22" },
    { 'w', "23" }, { 'W', "23" },
    { 'x', "24" }, { 'X', "24" },
    { 'y', "25" }, { 'Y', "25" },
    { 'z', "26" }, { 'Z', "26" }
};

std::string alphabet_position(const std::string& text)
{
    std::stringstream output;
    for (int i = 0; i < text.size(); ++i) {
        if (auto it = POSITION.find(text[i]); it != POSITION.end()) {
            output << it->second << ' ';
        }
    }
    if (output.size()) {
        output.pop_back();
    }
    return output.str();
}

// The below solution is not mine, but I thought it was interesting. I spread it out over more lines
// and added my own comments to clarify what it is doing.
//
// CodeWars attributes this solution to its users FArekkusu, GoodSoul, Shchuka, Allen17, and Belorabola
std::string alphabet_position(const std::string& s)
{
    std::stringstream ss;
    for (auto& x : s) { // auto reference to the chars in s; should be const auto& but whatever
        if (std::isalpha(x)) {
            // Doing bitwise or with 32 just adds 32 in case the 2^5 bit is not set in the char.
            // This is equivalent to adding 32 in case the bit is not set, and it happens to be that in ascii
            // all uppercase roman letters have a value 32 below their corresponding lowercase letters, and happen
            // to not have the 2^5 bit set.
            //
            // So, for a char x representing an upper or lower case letter, (x | 32) is the value in the
            // range [97, 122] corresponding to the lowercase representation of the letter in x.
            //
            // Then, subtracting 96 just shifts this range to [1, 26].
            ss << (x | 32) - 96 << ' ';
        }
    }
    std::string r = ss.str();
    // remove the last character added, which is a space character.
    if (r.size())
        r.pop_back();
    return r;
}
