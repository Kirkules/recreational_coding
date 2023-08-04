// Author: Kirk Boyer
//
// My c++ solution to https://leetcode.com/problems/longest-substring-without-repeating-characters/
//
// Description
// ----------------------------------------------------------------------------------------------
//  Given a string s, find the length of the longest substring without repeating characters.
//  Example 1:
//
//  Input: s = "abcabcbb"
//  Output: 3
//  Explanation: The answer is "abc", with the length of 3.
//
//  Example 2:
//
//  Input: s = "bbbbb"
//  Output: 1
//  Explanation: The answer is "b", with the length of 1.
//
//  Example 3:
//
//  Input: s = "pwwkew"
//  Output: 3
//  Explanation: The answer is "wke", with the length of 3.
//  Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
//
// ----------------------------------------------------------------------------------------------
//
// Discussion:
//
//  "repeating" here means "duplicated". Usually when I say "repeating" characters I mean subsequent, so
//  that the string "abababababab" has no repeating characters but many duplicated ones.
//
//  A first approach to this problem would be to iterate through the list and greedily take more characters
//  into a recorded longest substring until reaching a character which is a duplicate of one in the current
//  longest substring, then discard the part of the substring up to the first occurrence of that duplicated character
//  and continue extending from the end until the next duplicate is found, and continue in this way, replacing the
//  longest substring found so far once a new/longer one is found.
//
//  Some quick optimizations to a very naive implementation of this approach would be:
//      - record substring bounds instead of a copy of the substring itself
//      - we'd use a hashmap to record duplicates. But don't record something like # of occurrences of a character
//        or a bool whether it was seen or not, just record the index of the most recent occurrence of that char
//        in the string
//      - just for LeetCode stuff, made a bunch of variables static because I know it's going to run the
//        method a bunch of times and get an average time
//

#include <string>
#include <unordered_map>

class Solution {
public:
    int lengthOfLongestSubstring(const std::string& s)
    {
        std::unordered_map<char, int> last_index_map;
        // In real (not LeetCode) code, don't need/want to make these static, this is for
        // beating average runtimes.
        static int longest_length, length, end, start;
        static std::unordered_map<char, int>::iterator last_index;

        longest_length = 0, end = 0, start = 0;

        for (end = 0; end < s.size() + 1; ++end) {
            if (length = end - start; length > longest_length) {
                longest_length = length;
            }
            // Short-cut the rest of the computation if the longest substring found so
            // far is longer than the # of remaining characters to search through
            if (longest_length > s.size() - start - 1) {
                break;
            }
            if (end == s.size() + 1) {
                break;
            }
            if (last_index = last_index_map.find(s[end]);
                last_index != last_index_map.end()) {
                if (last_index->second >= start) {
                    start = last_index->second + 1;
                }
            }
            last_index_map.insert_or_assign(s[end], end);
        }

        return longest_length;
    }
};
