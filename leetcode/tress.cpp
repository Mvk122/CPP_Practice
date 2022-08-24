#include <vector>
#include <iostream>
#include <unordered_map>
#include <bits/stdc++.h>


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


// invert binary tree
void invertTree_f(TreeNode* node) {
    if (node != nullptr) {
        TreeNode* temp =  node->left;
        node->left = node->right;
        node->right = temp;

        if (node->left != nullptr) {
            invertTree_f(node->left);
        }
        if (node->right != nullptr) {
            invertTree_f(node->right);
        }
    }
}

TreeNode* invertTree(TreeNode* root) {
    invertTree_f(root);
    return root;
}

// is valid BST
bool isValidBST(TreeNode* root) {
    if (root != nullptr) {
        if (root->left != nullptr) {
            if (root->left->val > root->val) {
                return false;
            } else {
                isValidBST(root->left);
            }
        }
        if (root->right != nullptr) {
            if (root->right->val < root->val) {
                return false;
            } else {
                isValidBST(root->right);
            }
        }
    }
    return true;
}

int main() {
    TreeNode *mything = new TreeNode(2);
    TreeNode *bruh = new TreeNode(1);
    TreeNode *moment = new TreeNode(3);
    mything->left = bruh;
    mything->right = moment;
    isValidBST(mything);
}