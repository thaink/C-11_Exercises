#include <iostream>
#include <vector>
using namespace std;

int volume_of_lake(vector<unsigned int>& vec) {
    if(vec.size() == 0) return 0;
    int left_index = 0, right_index = vec.size()-1, sum = 0, total = 0;
    for (int index = 0; index < vec.size(); ++index) {
        if(vec[index] >= vec[left_index]) {
            total += (index-left_index)* vec[left_index] - sum;
            left_index = index;
            sum = vec[index];
        } else {
            sum += vec[index];
        }
    }
    sum = 0;
    for (int index = right_index; index >= left_index; --index) {
        if(vec[index] >= vec[right_index]) {
            total += abs(right_index-index)* vec[right_index] - sum;
            right_index = index;
            sum = vec[index];
        } else {
            sum += vec[index];
        }
    }
    return total;
}


int main()
{
    vector<unsigned int> vec{1,3,2,4,1,3,1,4,5,2,2,1,4,2,2};
    cout << volume_of_lake(vec) << endl;
    return 0;
}

