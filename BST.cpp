#include <iostream>
template<class T>
class Node
{
public:
    T data;
    Node<T>* left;
    Node<T>* right;
    Node(T value) : data(value), left(nullptr), right(nullptr) {}
};
template<class T>
class BST
{
private:
	Node<T> *root;
    void inOrderHelper(Node<T> *p);
    void preOrderHelper(Node<T> *p);
    void postOrderHelper(Node<T> *p);
    Node<T>* findMin(Node<T>* node); // Helper function to find the minimum node in a subtree
    Node<T>* deleteNode(Node<T>* root, T node);  // Helper function to delete a node
public:
	BST() : root(nullptr) {}
	void insert(T node);
	bool search(T node);
	void inOrder();
    void preOrder();
    void postOrder();
	void deleteMethod(T p);
};
template<class T>
void BST<T>::insert(T node) {
    Node<T> *newNode = new Node<T>(node);
    
    if (root == nullptr) {
        root = newNode;
    } else {
        Node<T> *current = root;
        Node<T> *parent = nullptr;
        
        while (current != nullptr) {
            parent = current;
            if (node < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        
        if (node < parent->data) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }
}

// Helper function to find the minimum node in a subtree
template<class T>
Node<T>* BST<T>::findMin(Node<T>* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Helper function to delete a node
template<class T>
Node<T>* BST<T>::deleteNode(Node<T>* root, T node) {
    if (root == nullptr) {
        return root;
    }

    if (node < root->data) {
        root->left = deleteNode(root->left, node);
    } else if (node > root->data) {
        root->right = deleteNode(root->right, node);
    } else {
        // Node with only one child or no child
        if (root->left == nullptr) {
            Node<T> *temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node<T> *temp = root->left;
            delete root;
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        Node<T> *temp = findMin(root->right);
        root->data = temp->data;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Public function
template<class T>
void BST<T>::deleteMethod(T node) {
    root = deleteNode(root, node);
}
template<class T>
bool BST<T>::search(T node) {
    Node<T> *current = root;
    while (current != nullptr) {
        if (current->data == node) {
            return true;
        } else if (node < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return false;
}
template<class T>
void BST<T>::inOrderHelper(Node<T> *p) {
    if (p != nullptr) {
        inOrderHelper(p->left);
        std::cout << p->data << " ";
        inOrderHelper(p->right);
    }
}

// Public function
template<class T>
void BST<T>::inOrder() {
    inOrderHelper(root);
    std::cout << std::endl;
}
template<class T>
void BST<T>::preOrderHelper(Node<T> *p) {
    if (p != nullptr) {
        std::cout << p->data << " ";
        preOrderHelper(p->left);
        preOrderHelper(p->right);
    }
}

// Public function
template<class T>
void BST<T>::preOrder() {
    preOrderHelper(root);
    std::cout << std::endl;
}
template<class T>
void BST<T>::postOrderHelper(Node<T> *p) {
    if (p != nullptr) {
        postOrderHelper(p->left);
        postOrderHelper(p->right);
        std::cout << p->data << " ";
    }
}

// Public function
template<class T>
void BST<T>::postOrder() {
    postOrderHelper(root);
    std::cout << std::endl;
}
int main()
{
	BST<int> obj;
	obj.insert(5);
	obj.insert(3);
	obj.insert(7);	
	obj.insert(2);
	obj.insert(4);
	obj.insert(6);
	obj.insert(8);
	
	obj.inOrder();
	obj.preOrder();
	obj.postOrder();
    
 	obj.deleteMethod(2);;
 	
 	obj.inOrder();

	return 0;
}