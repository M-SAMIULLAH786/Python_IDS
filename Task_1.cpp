#include <iostream>
using namespace std;


class StudentNode 
{
public:
    int rollNo;         
    string name;        
    double cgpa;         
    StudentNode* left;   
    StudentNode* right;  

    StudentNode(int r, string n, double c)
    
    {
        rollNo = r;
        name = n;
        cgpa = c;
        left = right = NULL;     
    }
};


class StudentBST

{
private:
    StudentNode* root; 

    void destroy(StudentNode* s)
    
    {
        if (s == NULL) return;   
        
        destroy(s->left);        
        destroy(s->right);       

        delete s;                
    }

    void InOrder(StudentNode* s) 
    {
        if (s == NULL) return;

        InOrder(s->left);  

        cout << "roll: " << s->rollNo
             << ", name: " << s->name
             << ", sgpaa: " << s->cgpa << endl;

        InOrder(s->right); 
    }

    void InRange(StudentNode* s, double startCgpa, double endCgpa) {
        if (s == NULL) return;

        InRange(s->left, startCgpa, endCgpa);

        if (s->cgpa >= startCgpa && s->cgpa <= endCgpa) 
        {
            cout << "roll: " 
            << s->rollNo
                 << ", name: " << s->name
                 << ", cgpa: " << s->cgpa 
                 << endl;
        }

        InRange(s->right, startCgpa, endCgpa);
    }






    StudentNode* removeNode(StudentNode* root, int rn,bool & found)
     {


        if (root == NULL) return NULL;

        if (rn < root->rollNo)
            root->left = 
            removeNode(root->left, rn, found);
 
        else if (rn > root->rollNo)
            root->right = removeNode(root->right, rn, found);

        else {
            found = true; 

            if (root->left == NULL && root->right == NULL) {
                delete root;
                return NULL;
            }

            else if (root->left == NULL) {
                StudentNode* temp = root->right;
                delete root;
                return temp;
                
            }

            else if (root->right == NULL) {
                StudentNode* temp = root->left;
                delete root;
                return temp;
            }

            else {
                StudentNode* temp = root->right;
                while (temp->left != NULL)
                    temp = temp->left;

                root->rollNo = temp->rollNo;
                root->name = temp->name;
                root->cgpa = temp->cgpa;

                root->right = removeNode(root->right, temp->rollNo, found);
            }
        }
        return root;
    }

public:

    
    StudentBST() {
        root = NULL;
    }

    ~StudentBST() {
        destroy(root);
    }

    bool insert(int r, string n, double c) {
        StudentNode* newNode = new StudentNode(r, n, c);

        if (root == NULL) {  
            root = newNode;
            return true;
        }

        StudentNode* current = root;
        StudentNode* parent = NULL;

        while (current != NULL) {
            parent = current;

            if (r < current->rollNo)
                current = current->left;
            else if (r > current->rollNo)
                current = current->right;
            else {
                delete newNode;  
                return false;     
            }
        }

        if (r < parent->rollNo)
            parent->left = newNode;
        else
            parent->right = newNode;

        return true;
    }



    bool search(int r) {
        StudentNode* current = root;

        while (current != NULL) {
            if (r == current->rollNo) {
                cout << "student find here"<<endl;
                cout << "roll: " << current->rollNo
                     << ", name: " << current->name
                     << ", cgpa: " << current->cgpa << endl;
                return true;
            }
            else if (r < current->rollNo)
                current = current->left;
            else
                current = current->right;
        }

        cout << "student not find.\n";
        return false;
    }

    bool remove(int rn) {
        bool found = false;
        root = removeNode(root, rn, found);

        if (!found)
            cout << "studnt not find.\n";

        return found;
    }

    void InOrder() {
        InOrder(root);
    }

    void displayInRange(double cs, double ce) {
        InRange(root, cs, ce);
    }
};

int main() {
    StudentBST s;
    int choice;

    while (true) {
        cout << "1. insert a new student:";cout << "2. search for a student:";cout << "3. See list of students (inorder):";
        cout << "4. Remove a student:";cout << "5. display student in cgpa range:";cout << "6. Quit:";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int r; string n; double c;
            cout << "enter roll,name,cgpa: ";
            cin >> r >> n >> c;
            if (s.insert(r, n, c))
                cout << "insertion success!\n";
            else
                cout << "duplicate roll num\n";
        }

        else if (choice == 2) {
            int r;
            cout << "enter roll: ";
            cin >> r;
            s.search(r);
        }

        else if (choice == 3) {
            s.InOrder();
        }

        else if (choice == 4) {
            int r;
            cout << "enter roll u wnat to delete: ";
            cin >> r;
            s.remove(r);
        }

        else if (choice == 5) {
            double a, b;
            cout << "enter the cgpa start and also the end range: ";
            cin >> a >> b;
            s.displayInRange(a, b);
        }

        else break;
    }
}
