//
// Created by light on 20-2-15.
//
#include <iostream>
#include <vector>

using namespace std;

// Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode *reConstructBinaryTree(vector<int> pre, vector<int> vin) {
    if (pre.empty() || vin.empty()) return NULL;
    TreeNode *root = new TreeNode(pre[0]);
    vector<int> lpre, lvin, rpre, rvin;

    for (int i = 0; i < vin.size(); i++) {
        if (vin[i] == pre[0]) {
            lpre = vector<int>(pre.begin() + 1, pre.begin() + i + 1);
            lvin = vector<int>(vin.begin(), vin.begin() + i);
            rpre = vector<int>(pre.begin() + i + 1, pre.end());
            rvin = vector<int>(vin.begin() + i + 1, vin.end());
            root->left = reConstructBinaryTree(lpre, lvin);
            root->right = reConstructBinaryTree(rpre, rvin);
        }
    }
    return root;
}