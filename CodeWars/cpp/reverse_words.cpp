#include <algorithm>

std::string reverse_words(std::string str)
{
    int word_end = 0;
    for (int begin = 0; begin < str.size(); ++begin) {
        while (std::isspace(str[begin]) && begin < str.size()) {
            ++begin;
        }
        word_end = begin;
        while (!std::isspace(str[word_end]) && word_end < str.size()) {
            ++word_end;
        }
        std::reverse(str.begin() + begin, str.begin() + word_end);
        begin = word_end;
    }

    return str;
}
