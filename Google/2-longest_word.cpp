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
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class Problem {
private:
    string S_;
    map<char, vector<int>> data_;

public:
    Problem(string S) {
        S_ = S;
        for (int it= 0; it < S.size(); ++it)
            if (data_.find(S[it]) == data_.end())
                data_[S[it]] = vector<int> {it};
            else
                data_[S[it]].push_back(it);
    }

    string find_longest_word(vector<string> words) {
        int max_length = 0;
        string max_string = "";
        for(auto word : words) {
            if(is_substr(word) && (word.size() > max_length)) {
                max_length = word.size();
                max_string = word;
            }
        }
        return max_string;
    }

    bool is_substr(string word) {
        int pos = -1;
        for (char ch : word) {
            if(data_.find(ch) == data_.end())
                return false;
            else {
                vector<int> vec = data_[ch];
                auto newpos = std::upper_bound(vec.begin(), vec.end(), pos);
                if(newpos == vec.end())
                    return false;
                else
                    pos = *newpos;
            }
        }
        return true;
    }
};

int main()
{
    Problem pro("abppplee");
    vector<string> D = {"able", "ale", "apple", "bale", "kangaroo"};
    cout << pro.find_longest_word(D) << endl;
    return 0;
}

