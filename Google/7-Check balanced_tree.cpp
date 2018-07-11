#include <iostream>

using namespace std;

struct Node{
    int value;
    Node* left;
    Node* right;
};

int balance_height(Node* n) {
    if(n=nullptr) return 0;
    int h1 = balance_height(n->left);
    int h2 = balance_height(n->right);
    if(min(h1,h2) == -1) return -1;
    if(abs(h1-h2)>1) return -1;
    return max(h1,h2)+1;
}

bool is_balanced_tree(Node* root) {
    int h1 = balance_height(root);
    if (h1>0) return true;
    return false;
}


int main()
{
    cout << "Hello World!" << endl;
    return 0;
}

