#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <queue>
using namespace std;

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }

    TreeNode* getLeftChild() {
        return left;
    }

    TreeNode* getRightChild() {
        return right;
    }

    int getData() {
        return data;
    }

    void addLeftChild(TreeNode* node) {
        left = node;
    }

    void addRightChild(TreeNode* node) {
        right = node;
    }
};

class Tree {
public:
    TreeNode* root;

    Tree() {
        root = nullptr;
    }

    void insertNode(int value) {
        TreeNode* newNode = new TreeNode(value);
        if (root == nullptr) {
            root = newNode;
            return;
        }
        queue<TreeNode*> que;
        que.push(root);
        while (!que.empty()) {
            TreeNode* current = que.front();
            que.pop();
            if (current->left == nullptr) {
                current->left = newNode;
                return;
            } else {
                que.push(current->left);
            }
            if (current->right == nullptr) {
                current->right = newNode;
                return;
            } else {
                que.push(current->right);
            }
        }
    }
    void printTree() {
        if (root == nullptr) return;
        queue<TreeNode*> que;
        que.push(root);
        while (!que.empty()) {
            TreeNode* current = que.front();
            que.pop();
            cout << current->data << " ";
            if (current->left != nullptr) {
                que.push(current->left);
            }
            if (current->right != nullptr) {
                que.push(current->right);
            }
        }
        cout << endl;
    }

    int getDegree(int data) {
        TreeNode* current = root;
        while (current != nullptr) {
            if (current->data == data) {
                int degree = 0;
                if (current->left != nullptr) degree++;
                if (current->right != nullptr) degree++;
                return degree;
            }
            if (data < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return -1;
    }
        int getTreeHeight() {
            return getHeight(root);
        }
    int getHeight(TreeNode* node) {
        if (node == nullptr) {
            return -1;
        }
        int leftHeight = getHeight(node->getLeftChild());
        int rightHeight = getHeight(node->getRightChild());
        int maxHeight;
        if (leftHeight > rightHeight) {
            maxHeight = leftHeight;
        } else {
            maxHeight = rightHeight;
        }
        return 1 + maxHeight;
    }
        int getHeight(int data) {
            TreeNode* current = root;
            while (current != nullptr) {
                if (current->data == data) {
                    return getHeight(current);
                }
                if (data < current->data) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
            return -1;
        }

    TreeNode* getRoot() {
        return root;
    }
};

#endif
