// Author: Kirk Boyer
//
// My solution to www.codewars.com/kata/530e15517bc88ac656000716/cpp authored by Rubikan.
//
// Description:
// -----------------------------------------------------------------------------------------
// How can you tell an extrovert from an introvert at NSA?
// Va gur ryringbef, gur rkgebireg ybbxf ng gur BGURE thl'f fubrf.
//
// I found this joke on USENET, but the punchline is scrambled. Maybe you can decipher it?
// According to Wikipedia, ROT13 is frequently used to obfuscate jokes on USENET.
//
// For this task you're only supposed to substitute characters. Not spaces, punctuation, numbers, etc.
//
// Test examples:
//
// "EBG13 rknzcyr." -> "ROT13 example."
//
// "This is my first ROT13 excercise!" -> "Guvf vf zl svefg EBG13 rkprepvfr!"
//
//
// -----------------------------------------------------------------------------------------

#include <algorithm>
#include <iostream>
#include <unordered_map>

constexpr char lower[] = "abcdefghijklmnopqrstuvwxyz";
constexpr char upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

const std::unordered_map<char, char>& GetRot13Map()
{
    static const std::unordered_map<char, char>* map = []() {
        std::unordered_map<char, char>* theMap = new std::unordered_map<char, char>;
        for (int i = 0; i < 26; ++i) {
            theMap->emplace(lower[i], lower[(i + 13) % 26]);
            theMap->emplace(upper[i], upper[(i + 13) % 26]);
        }
        return theMap;
    }();
    return *map;
}

std::string rot13(std::string str)
{
    std::for_each(str.begin(), str.end(),
        [](char& c) {
            if (std::isalpha(c)) {
                c = GetRot13Map().at(c);
            }
        });
    return str;
}

int main()
{
    std::cout << rot13("EBG13 rknzcyr.") << std::endl;
    std::cout << rot13("This is my first ROT13 excercise!") << std::endl;
}
