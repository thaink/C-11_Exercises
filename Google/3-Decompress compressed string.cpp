#include <iostream>
#include <vector>
#include <string>
using namespace std;

string decompress(const string& input, int& index) {
    string output;
    while((index < input.size()) && (input[index] != ']')) {
        if(isalpha(input[index]))
            output += input[index];
        else if(isdigit(input[index])) {
            string num;
            while(isdigit(input[index]))
            num += input[index++];
            index++;//bypass the '['
            string inner =  decompress(input, index);
            for (int idx = 0; idx < stoi(num); ++idx)
            output += inner;
        }
        index++;
    }
    return output;
}

string decompress(const string& input) {
    int index = 0;
    return decompress(input, index);
}



int main()
{
    cout << decompress("2[3[a]b]") << endl;
    return 0;
}

