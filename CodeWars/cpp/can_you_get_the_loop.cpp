// Author: Kirk Boyer
//
// My solution to www.codewars.com/kata/52a89c2ea8ddc5547a000863/cpp authored by Devouring.
//
// Description:
// -----------------------------------------------------------------------------------------
// You are given a node that is the beginning of a linked list. This list contains a dangling piece
// and a loop. Your objective is to determine the length of the loop.
// Use the `getNext()` method to get the following node.
// nodePtr->getNext()
//
//  Notes :
//
//  do NOT mutate the nodes !in some cases there may be only a loop,
//  with no dangling piece
//
// -----------------------------------------------------------------------------------------
//
// Discussion:
//
// There's no way to avoid recording something about all the nodes in the linked list to see when you've
// returned to one you saw before (closing the loop). The instructions don't give you anything about the
// Node class except that they have a getNext() method, so all you have access to to record anyway is the
// pointer to the Node.
//
// If we only record the node pointers seen, then we'll know when the loop is closed, but not how long it is.
// In that case, we'd have to traverse the loop again and count how many steps we take. Since we're already
// recording pointers, I figured recording another int/long per Node is probably something we can afford,
// so I just recorded how many nodes we saw by the time we reached each Node pointer. Then, once the loop is
// closed, you just have to subtract from the total node count the count at the Node you just returned to for
// the loop size.
//
#include <unordered_map>

int getLoopSize(Node* startNode)
{
    std::unordered_map<Node*, long> nodes_seen;
    long node_count = 1;
    while (true) {
        if (const auto& pair = nodes_seen.try_emplace(startNode, node_count); pair.second) {
            startNode = startNode->getNext();
            ++node_count;
        } else {
            break;
        }
    }
    return node_count - nodes_seen[startNode];
}
