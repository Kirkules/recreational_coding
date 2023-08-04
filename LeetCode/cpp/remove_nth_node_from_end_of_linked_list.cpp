// Author: Kirk Boyer
//
// My c++ solution to https://leetcode.com/problems/remove-nth-node-from-end-of-list/
//
// Description
// ----------------------------------------------------------------------------------------------
// Given the head of a linked list, remove the nth node from the end of the list and return its head.
//
// Example 1:
//
// Input: head = [1,2,3,4,5], n = 2
// Output: [1,2,3,5]
//
// ----------------------------------------------------------------------------------------------
//
// Discussion:
//
// Just follow the list pointers with two pointers, one trailing the other by n+1 links.
//
// The nth node from the end is pointed to by the n+1th node from the end, so this latter node is
// the one we need to find.
//
// Edge cases include: the list has n elements (in which case there is no n+1th element from the end),
// and the list has n elements (in which case the trailing element will not move and will be 1 ahead of
// where it needs to be), or the list has 1 element (in which
// ----------------------------------------------------------------------------------------------

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, const int& n)
    {
        static int countdown;
        static ListNode* current = head;
        static ListNode* trailing = head;
        countdown = n;
        while (nullptr != current->next) {
            current = current->next;
            if (countdown == 0) {
                trailing = trailing->next;
            } else {
                countdown -= 1;
            }
        }
        if (nullptr == trailing->next) {
            if (current == head) {
                head = nullptr;
            }
            return head;
        }
        if (countdown == 1) {
            head = head->next;
            return head;
        }
        trailing->next = trailing->next->next;
        return head;
    }
};
