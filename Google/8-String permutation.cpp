#include <iostream>

using namespace std;

void permutation_impl(string& s, int r, int n) {
    if(r == n)
        cout << s << endl;
    else {
        for(int i = r; i < n; ++i) {
            swap(s[i], s[r]);
            permutation_impl(s, r+1, n);
            swap(s[i], s[r]);
        }
    }
}

void permutation(string s) {
    permutation_impl(s, 0, s.size());
}


int main()
{
    permutation("abcd");
    return 0;
}

