/** Longest word:
 * Given a string S and a set of words D, find the longest word in D that is a subsequence of S.
 * Word W is a subsequence of S if some number of characters, possibly zero,
 * can be deleted from S to form W, without reordering the remaining characters.
 *
 * Solution:
 * greedy algorithm:
 *      for each word W in D, search sequentially if the character W[i] is in S.
 *      if all found then check the length of W.
 *      Complexity of this algorithm is N*L. mostly optimal.
 *      However if s is a very long it take much time.
 *
 * Improved greedy algorithm:
 *      Build a map of each character in S and its position.
 *      For each word W in D, check sequentially if if position of character W[i] is
 *      larger than character of its previous.
 *      The complexity is O(N + L * log N)
 *
 * An optimal O(N + L)
 *      Process all word simontanously
 *
 */

#include <iostream>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}

