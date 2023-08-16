// Author: Kirk Boyer
//
// My c++ solution to https://leetcode.com/problems/longest-palindromic-substring/
//
// Description
// ----------------------------------------------------------------------------------------------
// Given a string s, return the longest
// palindromic
// substring
// in s.
//
//
//
// Example 1:
//
// Input: s = "babad"
// Output: "bab"
// Explanation: "aba" is also a valid answer.
//
// Example 2:
//
// Input: s = "cbbd"
// Output: "bb"
//
//
// ----------------------------------------------------------------------------------------------
//
// Discussion:
//
// Seems like a good candidate for dynamic programming, since palindromes can be defined recursively (i.e.
// string S is a palindrome if S is a singleton or doubled character, or if the outer characters are the same and
// the inner substring is a palindrome).
//
// Lemmas and observations
//  L1. If a string S = \{S_0, S_1, ..., S_{n-1}\} is a palindrome, then
//      so is S\setminus{S_0, S_{n-1}}.
//  O2. A single character is a palindrome, and a pair of identical adjacent characters
//      is a palindrome.
//  L3. A solution to P = "What is the longest palindromic substring of S?" is the maximum over i \in {0, 1, ..., j}
//      and j \in {0, 1, ..., n-1} of:
//      P_i,j = "What is the longest palindromic substring of S[i:j] beginning with S_i?"
//  O4. P_i,j has optimal substructure, as its solution is the maximum of solutions to subproblems P_i',j' for i'<i, j'<j
//  05.
//
//
// ----------------------------------------------------------------------------------------------

class Solution {
public:
    string longestPalindrome(string s)
    {
    }
}
