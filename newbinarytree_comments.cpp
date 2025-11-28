#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

// ==============================================
// Node Class Template (Represents a tree node)
// ==============================================
template <typename T>
class Node
{
public:
    T info;             // Stores data of node
    Node<T> *left;      // Pointer to left child
    Node<T> *right;     // Pointer to right child

    // Constructor initializes a node with value and null children
    Node(T val = 0)
    {
        info = val;
        left = nullptr;
        right = nullptr;
    }
};

// ==============================================
// Binary Tree Class Template
// ==============================================
template <typename T>
class Binary_Tree
{
private:
    Node<T> *root; // Pointer to root node of tree

    // --------------------------
    // Recursive Search Function
    // Searches entire tree (NOT BST search)
    // --------------------------
    Node<T> *Search(Node<T> *curr, T val)
    {
        if (curr == nullptr)
            return nullptr;     // Not found
        if (curr->info == val)
            return curr;       // Found

        // Search in left subtree
        Node<T> *found = Search(curr->left, val);
        if (found)
            return found;

        // Search in right subtree
        return Search(curr->right, val);
    }

    // --------------------------
    // Delete entire subtree recursively
    // Used by destructor
    // --------------------------
    void RemoveSubtree(Node<T> *curr)
    {
        if (!curr)
            return;
        RemoveSubtree(curr->left);   // Delete left subtree
        RemoveSubtree(curr->right);  // Delete right subtree
        delete curr;                 // Delete current node
    }

    // --------------------------
    // Traversal Helper Functions
    // (Recursive)
    // --------------------------
    void PreOrder(Node<T> *curr)
    {
        if (!curr)
            return;
        cout << curr->info << " ";   // Visit root
        PreOrder(curr->left);        // Visit left subtree
        PreOrder(curr->right);       // Visit right subtree
    }

    void InOrder(Node<T> *curr)
    {
        if (!curr)
            return;
        InOrder(curr->left);         // Visit left subtree
        cout << curr->info << " ";   // Visit root
        InOrder(curr->right);        // Visit right subtree
    }

    void PostOrder(Node<T> *curr)
    {
        if (!curr)
            return;
        PostOrder(curr->left);       // Visit left subtree
        PostOrder(curr->right);      // Visit right subtree
        cout << curr->info << " ";   // Visit root
    }

    // --------------------------
    // Counting Functions
    // --------------------------
    int CountNodes(Node<T> *curr)
    {
        if (!curr)
            return 0;
        return 1 + CountNodes(curr->left) + CountNodes(curr->right);
    }

    int CountLeaves(Node<T> *curr)
    {
        if (!curr)
            return 0;
        if (!curr->left && !curr->right)
            return 1;  // Leaf node
        return CountLeaves(curr->left) + CountLeaves(curr->right);
    }

    int CountInternalNodes(Node<T> *curr)
    {
        if (!curr || (!curr->left && !curr->right))
            return 0; // Null or leaf → not internal
        return 1 + CountInternalNodes(curr->left) +
                   CountInternalNodes(curr->right);
    }

    // Height = longest path from this node to a leaf
    int Height(Node<T> *curr)
    {
        if (!curr)
            return 0;
        return 1 + max(Height(curr->left), Height(curr->right));
    }

    // --------------------------
    // Min & Max Value Search
    // Works since tree can be ANY structure (not BST)
    // --------------------------
    T FindMin(Node<T> *curr)
    {
        if (!curr)
            throw runtime_error("Tree is empty");

        T mn = curr->info;
        if (curr->left)
            mn = min(mn, FindMin(curr->left));
        if (curr->right)
            mn = min(mn, FindMin(curr->right));
        return mn;
    }

    T FindMax(Node<T> *curr)
    {
        if (!curr)
            throw runtime_error("Tree is empty");

        T mx = curr->info;
        if (curr->left)
            mx = max(mx, FindMax(curr->left));
        if (curr->right)
            mx = max(mx, FindMax(curr->right));
        return mx;
    }

    // --------------------------
    // Compare Two Trees
    // Structure + value check
    // --------------------------
    bool IsEqual(Node<T> *a, Node<T> *b)
    {
        if (a == nullptr && b == nullptr)
            return true;
        if (a == nullptr || b == nullptr)
            return false;

        return (a->info == b->info) &&
               IsEqual(a->left, b->left) &&
               IsEqual(a->right, b->right);
    }

    // --------------------------
    // Mirror Tree (swap children)
    // --------------------------
    void Mirror(Node<T> *curr)
    {
        if (!curr)
            return;
        swap(curr->left, curr->right);
        Mirror(curr->left);
        Mirror(curr->right);
    }

    // --------------------------
    // Print all root-to-leaf paths
    // --------------------------
    void PrintAllPaths(Node<T> *curr, vector<T> &path)
    {
        if (!curr)
            return;
        path.push_back(curr->info);

        if (!curr->left && !curr->right)
        {
            for (T val : path)
                cout << val << " ";
            cout << endl;
        }
        else
        {
            PrintAllPaths(curr->left, path);
            PrintAllPaths(curr->right, path);
        }

        path.pop_back(); // Backtrack
    }

    // --------------------------
    // Check completeness using BFS
    // Complete tree rule:
    // → No node should appear after a null in BFS
    // --------------------------
    bool IsComplete(Node<T> *root)
    {
        if (!root) return true;

        queue<Node<T> *> q;
        q.push(root);
        bool nullSeen = false;

        while (!q.empty())
        {
            Node<T> *curr = q.front();
            q.pop();

            if (!curr)
                nullSeen = true;
            else
            {
                if (nullSeen)
                    return false;
                q.push(curr->left);
                q.push(curr->right);
            }
        }
        return true;
    }

public:
    // Constructor creates root node
    Binary_Tree(T val = 0)
    {
        root = new Node<T>(val);
    }

    // Destructor deletes entire tree
    ~Binary_Tree()
    {
        RemoveSubtree(root);
    }

    // --------------------------
    // Setters
    // --------------------------
    void SetRoot(T v)
    {
        if (!root)
            root = new Node<T>(v);
        else
            root->info = v;
    }

    // Search parent → attach new left child
    void SetLeftChild(T parentVal, T childVal)
    {
        Node<T> *parent = Search(root, parentVal);
        if (!parent)
            return;

        if (!parent->left)
            parent->left = new Node<T>(childVal);
        else
            parent->left->info = childVal;
    }

    // Search parent → attach new right child
    void SetRightChild(T parentVal, T childVal)
    {
        Node<T> *parent = Search(root, parentVal);
        if (!parent)
            return;

        if (!parent->right)
            parent->right = new Node<T>(childVal);
        else
            parent->right->info = childVal;
    }

    // --------------------------
    // Public Traversal Calls
    // --------------------------
    void PreOrder() { PreOrder(root); cout << endl; }
    void InOrder() { InOrder(root); cout << endl; }
    void PostOrder() { PostOrder(root); cout << endl; }

    // BFS traversal
    void LevelOrder()
    {
        if (!root) return;

        queue<Node<T> *> q;
        q.push(root);
        while (!q.empty())
        {
            Node<T> *curr = q.front();
            q.pop();
            cout << curr->info << " ";
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        cout << endl;
    }

    // --------------------------
    // Public Utility Wrappers
    // --------------------------
    bool IsEmpty() { return root == nullptr; }

    int GetHeight() { return Height(root); }

    int GetNodeCount() { return CountNodes(root); }

    int GetLeafCount() { return CountLeaves(root); }

    int GetInternalCount() { return CountInternalNodes(root); }

    T GetMin() { return FindMin(root); }

    T GetMax() { return FindMax(root); }

    void MakeMirror() { Mirror(root); }

    bool IsComplete() { return IsComplete(root); }

    bool IsEqual(Binary_Tree<T> &other) { return IsEqual(root, other.root); }

    void PrintAllPaths()
    {
        vector<T> path;
        PrintAllPaths(root, path);
    }
};

// ==============================================
// MAIN FUNCTION - TESTING
// ==============================================
int main()
{
    Binary_Tree<int> tree(1);

    // Manually building tree
    tree.SetLeftChild(1, 2);
    tree.SetRightChild(1, 3);
    tree.SetLeftChild(2, 4);
    tree.SetRightChild(2, 5);
    tree.SetLeftChild(3, 6);
    tree.SetRightChild(3, 7);

    cout << "PreOrder: ";
    tree.PreOrder();

    cout << "InOrder: ";
    tree.InOrder();

    cout << "PostOrder: ";
    tree.PostOrder();

    cout << "LevelOrder: ";
    tree.LevelOrder();

    cout << "\nNode Count: " << tree.GetNodeCount();
    cout << "\nLeaf Count: " << tree.GetLeafCount();
    cout << "\nInternal Count: " << tree.GetInternalCount();
    cout << "\nHeight: " << tree.GetHeight();
    cout << "\nMin Value: " << tree.GetMin();
    cout << "\nMax Value: " << tree.GetMax();
    return 0;
}
