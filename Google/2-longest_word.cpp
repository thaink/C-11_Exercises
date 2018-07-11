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
 *      The complexity is O(N + L * logN). log N to find occurence > pos in the list.
 *      Advanced data structure:
 *
 * Small alphabet:
 *      O(N + L)
 *      for each character. store vector which is next character equal c with index > pos
 *
 * An optimal O(N + L)
 *      Process all word simontanously.
 *      First, for each word w in D, create a 2-tuple containing w and the number 0 (i.e. (w, 0)).
 *      The number refers to the number of characters in w that have already been found in S.
 *      group word by next processing character.
 *      for each character in S. increase this list. The problem is how to group tuple effectively?
 *      We could construct replacement for the list and process it simontaneously.
 *
 */

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Problem {
    using map_type = multimap<char,pair<string, int>>;
public:
    string solve(const string& S, const vector<string>& D) {
        map_type dmap = gen_map(D);
        string maxstring;
        for (char c : S) {
            auto fl = dmap.equal_range(c);
            for(map_type::iterator it = fl.first, it_next = fl.first; it != fl.second; it = it_next) {
                pair<string, int>& value = it->second;
                value.second++;
                it_next++;
                if(value.second == value.first.size()) {
                    if(value.first.size() > maxstring.size()) maxstring = value.first;
                    dmap.erase(it);
                    continue;
                }
                if(value.first[value.second] != c) {
                    dmap.emplace(value.first[value.second], std::move(value));
                    dmap.erase(it);
                }
            }
        }
    return maxstring;
    }

private:
    map_type gen_map(const vector<string>& D) {
        map_type mmap;
        for (string s : D) {// s is a new copy of the original string
            if(s.empty()) continue;
            mmap.emplace(s[0], make_pair(s, 0));
        }
        return mmap;
    }
};


int main()
{
    Problem pb;
    cout << pb.solve("abppplee", {"able", "ale", "apple", "bale", "kangaroo"}) << endl;
    return 0;
}
