#include <iostream>
#include <limits>
#include <tuple>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
};

//tuple order:max, min, is_binary
tuple<int, int, bool> is_binary_impl(Node* parent) {
    if(parent == nullptr) return make_tuple(numeric_limits<int>::lowest(), numeric_limits<int>::max(), true);
    auto rl = is_binary_impl(parent->left);
    if(!std::get<2>(rl)) return make_tuple(0,0,false);
    auto rr = is_binary_impl(parent->right);
    if(!std::get<2>(rr)) return make_tuple(0,0,false);

    if((std::get<0>(rl) >= parent->value) || (std::get<1>(rr) <= parent->value)) return make_tuple(0,0,false);
    return make_tuple(max(parent->value, max(std::get<0>(rl), std::get<0>(rr))), min(parent->value, min(std::get<1>(rl), std::get<1>(rr))), true);
}


int main()
{
    cout << "Hello World!" << endl;
    return 0;
}

