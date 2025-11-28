#include<iostream>
using namespace std;


class BSTNode {
public:
    int data;
    BSTNode* left;
    BSTNode* right;
    

    BSTNode(int d) {
        data = d;
        left = right = NULL;
    }
};

class IntBST {
private:
    BSTNode* root;

    void destroy(BSTNode* b) {
        if (b == NULL) return;
        destroy(b->left);
        destroy(b->right);
        delete b;
    }

    bool recSearch(BSTNode* b, int key) {
        if (b == NULL) return false;
        if (b->data == key) return true;
        if (key < b->data)
            return recSearch(b->left, key);
        else
            return recSearch(b->right, key);
    }

    int countNodes(BSTNode* b) {
        if (b == NULL) return 0;
        return  1 + countNodes(b->left) + countNodes(b->right);
    }



    int getHeight(BSTNode* b) {
        if (b == NULL) return -1;
        int leftsubTree = getHeight(b->left);
        int rightsubTree  = getHeight(b->right);

                return 1 + max (leftsubTree ,rightsubTree); 


    }





    void doubleTree(BSTNode* b) {
        if (b == NULL) return;

        doubleTree(b->left);
        doubleTree(b->right);

        BSTNode* oldLeft = b->left;
        b->left = new BSTNode(b->data);
        b->left->left = oldLeft;
    }

    
public:
    IntBST() {
        root = NULL;
    }

    ~IntBST() {
        destroy(root);
    }

    void insert(int d) {
        BSTNode* newNode = new BSTNode(d);

        if (root == NULL) {
            root = newNode;
            return;
        }

        BSTNode* current = root;
        BSTNode* parent = NULL;

        while (current != NULL) {
            parent = current;
            if (d < current->data)
                current = current->left;
            else
                current = current->right;
        }
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
    
};

int main() {
    IntBST b;    

    b.insert(50); b.insert(40);
    b.insert(75);b.insert(25);b.insert(65);
    b.insert(80);

    cout << "ssearching 65.....  ";
    cout << (b.recSearch(65) ? "find" : "not Find") << endl;
 cout<<endl;
    cout << "searching 90..... ";
    cout << (b.recSearch(90) ? "find" : "not find") << endl;
  cout<<endl;

    cout << "total nodes: " << b.countNodes() << endl;

    cout << "height of tree: " << b.getHeight() << endl;
 cout<<endl;
    cout<<endl;
    cout << "doubling tree"<<endl;
    b.doubleTree();
  cout<<endl;
  

}