
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct AVLNode{
	int data, height;
	AVLNode *left, *right;
	AVLNode(int data, AVLNode *left=NULL, AVLNode *right=NULL){
		this->data = data;
		this->left = left;
		this->right = right;
		this->height = 0;
	}
};
int max(const int a, const int b){
	if (a < b)	return b;
	return a;
}
class BST{
	AVLNode *root;
public:
	BST(){	root = NULL;	}
	AVLNode* leftRotation(AVLNode* temp){
		AVLNode* temp_right = temp->right;
		temp->right	= temp_right->left;
		temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
		temp_right->left = temp;
		temp = temp_right;
		temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
		return temp;
	}
	AVLNode* rightRotation(AVLNode* temp){
		AVLNode* temp_left = temp->left;
		temp->left	= temp_left->right;
		temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
		temp_left->right = temp;
		temp = temp_left;
		temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
		return temp;
	}
	int getHeight(AVLNode* t) const{
		if (!t)	return -1;
		return t->height;
	}
	int getHeight() const{
		if (!root)	return 0;
		int lh = getHeight(root->left);
		int rh = getHeight(root->right);
		return max(lh, rh) + 1;
	}
	AVLNode* doRightRotation(AVLNode* temp){
		int balance = getHeight(temp->left->left) - getHeight(temp->left->right);
		if (balance < 0) 	temp->left = leftRotation(temp->left);
		temp = rightRotation(temp);
		return temp;
	}
	AVLNode* doLeftRotation(AVLNode* temp){
		int balance = getHeight(temp->right->left) - getHeight(temp->right->right);
		if (balance > 0) 	temp->right = rightRotation(temp->right);
		temp = leftRotation(temp);
		return temp;
	}
	AVLNode* doRotation(AVLNode* temp){
		int lh = getHeight(temp->left);
		int rh = getHeight(temp->right);
		int balance =  lh - rh ;
		if (balance > 1)
			temp = doRightRotation(temp);
		else if (balance < -1)
			temp = doLeftRotation(temp);
		return temp;		
	}
	AVLNode* insert(int d, AVLNode *temp){	
		if (temp==NULL)	return new AVLNode(d);
		if (temp->data>d) 		temp->left = insert(d, temp->left);
		else if (temp->data<d) temp->right = insert(d, temp->right);
		temp = doRotation(temp);
		temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
		return temp;	
	}
	void insert(int d){	
		root = insert(d, root);
	}
	AVLNode* findLeftMost(AVLNode *t){
		if (t->left == NULL)	return t;
		return findLeftMost(t->left);
	}
	AVLNode* remove(int d, AVLNode *temp){	
		if (temp==NULL)			return NULL;
		if (temp->data>d) 		temp->left = remove(d, temp->left);
		else if (temp->data<d) 	temp->right = remove(d, temp->right);
		else{	//this is the node to be deleted
			if (temp->left == NULL && temp->right == NULL){
				delete temp;	//delete leaf node and return null
				return NULL;
			}
			else if (temp->left == NULL && temp->right != NULL){
				AVLNode *tempR = temp->right;	//Before deletion save right child
				delete temp;					//delete current node
				return tempR;				//return right child to connect with grand parent
			}
			else if (temp->right == NULL){
				AVLNode *tempL = temp->left;		//Before deletion save left child
				delete temp;					//delete current node
				return tempL;				//return left child to connect with grand parent
			}
			else{	//node has both left and right child nodes
				AVLNode *toBeReplaced = 	findLeftMost(temp->right);//you can either find left most in right sub tree or right most in left sub tree
				temp->data = toBeReplaced->data;
				temp->right = remove(temp->data, temp->right);//delete the left most node having same data but single or zero child node being left most
			}		
		}
		temp = doRotation(temp);
		temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
		return temp;	
	}
	void remove(int d){	
		root = remove(d, root);
	}
	void inorder(AVLNode* t){
		if (t!=NULL){
			inorder(t->left);
			cout << t->data << ' ';
			inorder(t->right);
		}
	}
	void inorder(){
		inorder(root);
		cout << '\n';
	}
	void preorder(AVLNode* t){
		if (t!=NULL){
			cout << t->data << ' ';
			preorder(t->left);
			preorder(t->right);
		}
	}
	void preorder(){
		preorder(root);
		cout << '\n';
	}
	void removeNodes(AVLNode* t){
		if (t!=NULL){
			removeNodes(t->left);
			removeNodes(t->right);
			delete t;
		}
	}
	~BST(){
		removeNodes(root);
	}
};

int main(){
	srand(time(0));
	BST tree;
	int val;
	for (int i=0;i<30;i++){
		val = rand()%90+10;
		tree.insert(val);
	}
	cout << "Height: " << tree.getHeight() << '\n';
	cout << "\nPre Order:\t";
	tree.preorder();
	cout << "In Order:\t";
	tree.inorder();
	for (int i=0;i<60;i++){	//As we are generating data randomly, there is a chance that we come with an existing node, so run loop 60 times
		val = rand()%90+10;
		tree.remove(val);
	}
	cout << "Height: " << tree.getHeight() << '\n';
	cout << "\nPre Order:\t";
	tree.preorder();
	cout << "In Order:\t";
	tree.inorder();
	return 0;
}
AVL_Tree.cpp
External

Displaying AVL_Tree.cpp.