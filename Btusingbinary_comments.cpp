#include <iostream>
#include <math.h>
#include <queue>
#include <utility>
using namespace std;

// ---------------------- NODE CLASS ----------------------
// Each node of a Binary Tree contains:
//  - an integer data value
//  - a pointer to the left child
//  - a pointer to the right child
class DNode
{
public:
    int data;
    DNode *rightchild;
    DNode *leftchild;

    // Constructor: initializes a node with value v and no children
    explicit DNode(int v) : data(v), rightchild(nullptr), leftchild(nullptr) {}
};

// ---------------------- BINARY TREE CLASS ----------------------
template <class T>
class Binarytree
{
    DNode *root; // Pointer to root of binary tree

    // ----------- PRIVATE HELPER FUNCTIONS -----------

    // Recursive search in the binary tree
    DNode *search(DNode *curr, T v)
    {
        if (curr == nullptr)
            return nullptr;  // Value not found

        if (curr->data == v)
            return curr;     // Found the node

        // Search in left subtree first, if not found then in right subtree
        DNode *t = search(curr->leftchild, v);
        if (!t)
            t = search(curr->rightchild, v);

        return t;
    }

    // Recursively delete all nodes in subtree (postorder deletion)
    void remove(DNode *curr)
    {
        if (curr == nullptr)
            return;

        remove(curr->leftchild);
        remove(curr->rightchild);

        delete curr;
    }

    // Tree Traversals (Recursive)
    void preorder(DNode *curr)
    {
        if (!curr) return;
        cout << curr->data << " "; // Visit root
        preorder(curr->leftchild);
        preorder(curr->rightchild);
    }

    void postorder(DNode *curr)
    {
        if (!curr) return;
        postorder(curr->leftchild);
        postorder(curr->rightchild);
        cout << curr->data << " "; // Visit root last
    }

    void inorder(DNode *curr)
    {
        if (!curr) return;
        inorder(curr->leftchild);
        cout << curr->data << " "; // Visit root in the middle
        inorder(curr->rightchild);
    }

    // ---------- LeetCode Helper Algorithms ----------

    // Height / Maximum depth of the tree
    int maxDepthRec(DNode *curr)
    {
        if (!curr) return 0;
        int L = maxDepthRec(curr->leftchild);
        int R = maxDepthRec(curr->rightchild);
        return 1 + max(L, R);
    }

    // Invert a binary tree (swap left-right for each node)
    DNode* invertTreeRec(DNode *curr)
    {
        if (!curr) return nullptr;
        DNode *L = invertTreeRec(curr->leftchild);
        DNode *R = invertTreeRec(curr->rightchild);
        curr->leftchild = R;
        curr->rightchild = L;
        return curr;
    }

    // Check if root-to-leaf path equals target sum
    bool hasPathSumRec(DNode *curr, int target)
    {
        if (!curr) return false;

        target -= curr->data;

        // If leaf and sum matches
        if (!curr->leftchild && !curr->rightchild)
            return target == 0;

        return hasPathSumRec(curr->leftchild, target) ||
               hasPathSumRec(curr->rightchild, target);
    }

    // Sum of all left leaves in the tree
    int sumOfLeftLeavesRec(DNode *curr, bool isLeft)
    {
        if (!curr) return 0;

        if (!curr->leftchild && !curr->rightchild)
            return isLeft ? curr->data : 0;

        return sumOfLeftLeavesRec(curr->leftchild, true) +
               sumOfLeftLeavesRec(curr->rightchild, false);
    }

    // Height and Diameter (pair approach)
    pair<int,int> diameterRec(DNode *curr)
    {
        if (!curr) return {0, 0}; // height, diameter

        auto L = diameterRec(curr->leftchild);
        auto R = diameterRec(curr->rightchild);

        int height = 1 + max(L.first, R.first);
        int throughRoot = L.first + R.first;
        int best = max({throughRoot, L.second, R.second});

        return {height, best};
    }

public:
    // Constructor initializes empty tree
    Binarytree() : root(nullptr) {}

    // Set root node (replace existing tree if any)
    void setroot(T v)
    {
        if (root) remove(root);
        root = new DNode((int)v);
    }

    // Insert left child for a parent value p
    void setleftchild(T p, T v)
    {
        DNode *n = search(root, p);
        if (!n) return;
        if (!n->leftchild)
            n->leftchild = new DNode((int)v);
    }

    // Insert right child for a parent value p
    void setrightchild(T p, T v)
    {
        DNode *n = search(root, p);
        if (!n) return;
        if (!n->rightchild)
            n->rightchild = new DNode((int)v);
    }

    // Delete subtree starting from node with value
    void remove(T value)
    {
        DNode *target = search(root, value);
        if (!target)
        {
            cout << "Node not found.\n";
            return;
        }
        remove(target);
        cout << "Subtree deleted.\n";
    }

    // Public wrappers for traversal
    void Preorder() { preorder(root); }
    void Postorder() { postorder(root); }
    void Inorder() { inorder(root); }

    // Level Order Traversal (BFS)
    void levelorder()
    {
        if (!root) return;

        queue<DNode*> Q;
        Q.push(root);

        while (!Q.empty())
        {
            DNode *curr = Q.front();
            Q.pop();
            cout << curr->data << " ";

            if (curr->leftchild)
                Q.push(curr->leftchild);
            if (curr->rightchild)
                Q.push(curr->rightchild);
        }
    }

    // LeetCode algorithm wrappers
    int maxDepth() { return maxDepthRec(root); }
    void invertTree() { root = invertTreeRec(root); }
    bool hasPathSum(int targetSum) { return hasPathSumRec(root, targetSum); }
    int sumOfLeftLeaves() { return sumOfLeftLeavesRec(root, false); }
    int diameterOfBinaryTreeNodes() { return diameterRec(root).second + 1; }

    // Full clearing
    void clear()
    {
        remove(root);
        root = nullptr;
    }
};


// ---------------------- MAIN FUNCTION ----------------------
int main()
{
    Binarytree<int> bt;

    // Create this structure:
    //           10
    //          /  \
    //         5    15
    //        / \  /  \
    //       3  7 12  18

    bt.setroot(10);
    bt.setleftchild(10, 5);
    bt.setrightchild(10, 15);
    bt.setleftchild(5, 3);
    bt.setrightchild(5, 7);
    bt.setleftchild(15, 12);
    bt.setrightchild(15, 18);

    cout << "Preorder:   ";
    bt.Preorder();
    cout << "\nInorder:    ";
    bt.Inorder();
    cout << "\nPostorder:  ";
    bt.Postorder();
    cout << "\nLevelorder: ";
    bt.levelorder();

    return 0;
}
