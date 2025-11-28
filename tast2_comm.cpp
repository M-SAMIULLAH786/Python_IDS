#include<iostream>
using namespace std;

/*-------------------------------------
   CLASS: BSTNode
   Represents a single node of the tree.
--------------------------------------*/
class BSTNode {
public:
    int data;          // Stores integer value in node
    BSTNode* left;     // Pointer to left child
    BSTNode* right;    // Pointer to right child

    // Constructor initializes node with data and sets children to NULL
    BSTNode(int d) {
        data = d;
        left = right = NULL;
    }
};

/*-------------------------------------
   CLASS: IntBST
   Implements a Binary Search Tree (BST)
--------------------------------------*/
class IntBST {
private:
    BSTNode* root;  // Root pointer of the whole BST

    /*-------------------------------------
       destroy()
       Deletes entire tree using Postorder
    --------------------------------------*/
    void destroy(BSTNode* b) {
        if (b == NULL) return;
        destroy(b->left);
        destroy(b->right);
        delete b; // delete node after children
    }

    /*-------------------------------------
       recSearch()
       Recursively searches for a key
    --------------------------------------*/
    bool recSearch(BSTNode* b, int key) {
        if (b == NULL) return false;           // key not found
        if (b->data == key) return true;       // key found

        // Go left if key < node data, else go right
        if (key < b->data)
            return recSearch(b->left, key);
        else
            return recSearch(b->right, key);
    }

    /*-------------------------------------
       countNodes()
       Returns total number of nodes
    --------------------------------------*/
    int countNodes(BSTNode* b) {
        if (b == NULL) return 0;
        return 1 + countNodes(b->left) + countNodes(b->right);
    }

    /*-------------------------------------
       getHeight()
       Returns height of tree
       Height of empty tree = -1
    --------------------------------------*/
    int getHeight(BSTNode* b) {
        if (b == NULL) return -1;

        int leftsubTree = getHeight(b->left);   // height of left subtree
        int rightsub = getHeight(b->right);  // height of right subtree

        return 1 + (lh > rh ? lh : rh); // 1 + max(left,right)
    }

    /*-------------------------------------
       doubleTree()
       Converts tree into "double tree":
       For each node, create a duplicate
       and insert it as left child.
    --------------------------------------*/
    void doubleTree(BSTNode* b) {
        if (b == NULL) return;

        doubleTree(b->left);
        doubleTree(b->right);

        BSTNode* oldLeft = b->left;         // store original left child
        b->left = new BSTNode(b->data);     // duplicate inserted as left child
        b->left->left = oldLeft;            // original left child moved under duplicate
    }

    /*-------------------------------------
       printPaths()
       Prints all root-to-leaf paths
    --------------------------------------*/
    void printPaths(BSTNode* b, int path[], int pathLen) {
        if (b == NULL) return;

        path[pathLen] = b->data;  // add current node to path
        pathLen++;

        // If leaf node → print complete path
        if (b->left == NULL && b->right == NULL) {
            for (int i = 0; i < pathLen; i++) {
                cout << path[i];
                if (i != pathLen - 1) cout << " -> ";
            }
            cout << endl;
        }
        else {
            printPaths(b->left, path, pathLen);
            printPaths(b->right, path, pathLen);
        }
    }

public:
    // Constructor sets root to NULL
    IntBST() {
        root = NULL;
    }

    // Destructor automatically deletes all nodes
    ~IntBST() {
        destroy(root);
    }

    /*-------------------------------------
       insert()
       Inserts a new node in BST
    --------------------------------------*/
    void insert(int d) {
        BSTNode* newNode = new BSTNode(d);

        if (root == NULL) {   // tree is empty
            root = newNode;
            return;
        }

        BSTNode* current = root;
        BSTNode* parent = NULL;

        // Find correct position
        while (current != NULL) {
            parent = current;
            if (d < current->data)
                current = current->left;
            else
                current = current->right;
        }

        // Insert new node under correct parent
        if (d < parent->data)
            parent->left = newNode;
        else
            parent->right = newNode;
    }

    bool recSearch(int key) {
        return recSearch(root, key);
    }

    int countNodes() {
        return countNodes(root);
    }

    int getHeight() {
        return getHeight(root);
    }

    void doubleTree() {
        doubleTree(root);
    }

    void printAllPaths() {
        int path[100];
        printPaths(root, path, 0);
    }
};

/*-------------------------------------
           MAIN FUNCTION
--------------------------------------*/
int main() {
    IntBST b;    // create BST object

    // Insert sample values
    b.insert(50);
    b.insert(40);
    b.insert(75);
    b.insert(25);
    b.insert(65);
    b.insert(80);

    cout << "\nSearching 65 → ";
    cout << (b.recSearch(65) ? "Found" : "Not Found") << endl;

    cout << "\nSearching 90 → ";
    cout << (b.recSearch(90) ? "Found" : "Not Found") << endl;

    cout << "\nTotal Nodes: " << b.countNodes() << endl;

    cout << "Height of Tree: " << b.getHeight() << endl;

    cout << "\nAll Root-to-Leaf Paths:\n";
    b.printAllPaths();

    cout << "\nDoubling Tree...\n";
    b.doubleTree();

    cout << "\nAll Paths After Doubling Tree:\n";
    b.printAllPaths();

    return 0;
}
