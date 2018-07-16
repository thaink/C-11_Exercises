#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

unordered_multimap<string, int> gen_word_map(const vector<string>& vec, int k);
vector<vector<string>> word_squares_recursive(const vector<string>& vec, const int k, vector<string>& candidate, int cl, const unordered_multimap<string, int>& smap);

vector<vector<string>> word_squares(const vector<string>& vec, const int k) {
    unordered_multimap<string, int> smap = gen_word_map(vec,k);

    vector<vector<string>> result;
    if(k==0) return result;
    //find all possible word squares
    vector<string> candidate;
    for (uint i = 0; i < vec.size(); ++i) {
        candidate.push_back(vec[i]);
        vector<vector<string>> r = word_squares_recursive(vec, k, candidate, 1, smap);
        candidate.pop_back();
        result.insert(result.end(), r.begin(), r.end());
    }
    return result;
}

vector<vector<string>> word_squares_recursive(const vector<string>& vec, const int k, vector<string>& candidate, int cl, const unordered_multimap<string, int>& smap) {
    vector<vector<string>> result;
    if(cl >= k) {result.push_back(candidate); return result;}
    //find all possible word squares
    string search_string;
    for(uint i = 0; i < candidate.size(); ++i)
        search_string += candidate[i][cl];
    auto rm = smap.equal_range(search_string);
    for (auto it = rm.first; it != rm.second; ++it) {
        candidate.push_back(vec[it->second]);
        vector<vector<string>> nresult = word_squares_recursive(vec, k, candidate, cl+1, smap);
        candidate.pop_back();
        result.insert(result.end(), nresult.begin(), nresult.end());
    }
    return result;
}

unordered_multimap<string, int> gen_word_map(const vector<string>& vec, int k) {
    //generate lookup map
    unordered_multimap<string, int> smap;
    if(k==0) return smap;
    for (uint i = 0; i < vec.size(); ++i)
        for(int j=1; j < k; ++j)
            smap.emplace(vec[i].substr(0,j), i);
    return smap;
}


int main()
{
    vector<string> vec{"AREA", "BALL", "DEAR", "LADY", "LEAD", "YARD"};
    auto result = word_squares(vec, 4);
    for (auto vec_string : result) {
        for (string s : vec_string)
            cout << s << " ";
        cout << "\n";
    }
    cout << "Hello World!" << endl;
    return 0;
}

