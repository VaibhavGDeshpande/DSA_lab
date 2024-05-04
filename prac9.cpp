#include <iostream> 
#include <fstream> 
#include <cstring> 
using namespace std; 
 
struct word 
{ 
char key[15]; 
char meaning[20]; 
}; 
 
struct node 
{ 
word data; 
node *left, *right; 
int ht; 
}; 
 
class AVL 
{ 
private: 
node *AVLroot; 
 
node *insert1(node *, word); 
void preorder1(node *); 
void inorder1(node *); 
node *rotateright(node *); 
node *rotateleft(node *); 
node *RR(node *); 
node *LL(node *); 
node *LR(node *); 
node *RL(node *); 
int BF(node *); 
int height(node *); 
 
public: 
AVL() 
{ 
AVLroot = NULL; 
} 
void insert(word x) { AVLroot = insert1(AVLroot, x); } 
void preorder() { preorder1(AVLroot); } 
void inorder() { inorder1(AVLroot); } 
void search(word x); 
void printTree(); // Added function to print the entire tree 
void copyToFile(); // Added function to copy tree to file 
void menu(); // Added function to display menu options 
void userInput(); // Added function to take user input for adding words 
void copyHelper(node *T, ofstream &file); // Declaration of copyHelper 
}; 
 
node *AVL::insert1(node *T, word x) 
{ 
if (T == NULL) 
{ 
T = new node; 
T->data = x; 
T->left = NULL; 
T->right = NULL; 
T->ht = 1; // initialize height to 1 for leaf nodes 
} 
else if (strcmp(x.key, T->data.key) > 0) 
{ 
T->right = insert1(T->right, x); 
if (BF(T) == -2) 
if (strcmp(x.key, T->right->data.key) > 0) 
T = RR(T); 
else 
T = RL(T); 
} 
else if (strcmp(x.key, T->data.key) < 0) 
{ 
T->left = insert1(T->left, x); 
if (BF(T) == 2) 
if (strcmp(x.key, T->left->data.key) < 0) 
T = LL(T); 
else 
T = LR(T); 
} 
T->ht = max(height(T->left), height(T->right)) + 1; // update height 
return (T); 
} 
 
int AVL::height(node *T) 
{ 
if (T == NULL) 
return (0); 
return T->ht; 
} 
 
node *AVL ::rotateright(node *x) 
{ 
node *y; 
y = x->left; 
x->left = y->right; 
y->right = x; 
x->ht = max(height(x->left), height(x->right)) + 1; 
y->ht = max(height(y->left), height(y->right)) + 1; 
return (y); 
} 
 
node *AVL ::rotateleft(node *x) 
{ 
node *y; 
y = x->right; 
x->right = y->left; 
y->left = x; 
x->ht = max(height(x->left), height(x->right)) + 1; 
y->ht = max(height(y->left), height(y->right)) + 1; 
return (y); 
} 
 
node *AVL ::RR(node *T) 
{ 
T = rotateleft(T); 
return (T); 
} 
 
node *AVL ::LL(node *T) 
{ 
T = rotateright(T); 
return (T); 
} 
 
node *AVL ::LR(node *T) 
{ 
T->left = rotateleft(T->left); 
T = rotateright(T); 
return (T); 
} 
 
node *AVL ::RL(node *T) 
{ 
T->right = rotateright(T->right); 
T = rotateleft(T); 
return (T); 
} 
 
int AVL::BF(node *T) 
{ 
if (T == NULL) 
return (0); 
 
return (height(T->left) - height(T->right)); 
} 
 
void AVL::preorder1(node *T) 
{ 
if (T != NULL) 
{ 
cout << "(" << T->data.key << "-" << T->data.meaning << ")"; 
preorder1(T->left); 
preorder1(T->right); 
} 
} 
 
void AVL::inorder1(node *T) 
{ 
if (T != NULL) 
{ 
inorder1(T->left); 
cout << "(" << T->data.key << "---" << T->data.meaning << ")"; 
inorder1(T->right); 
} 
} 
 
void AVL::search(word x) 
{ 
node *T = AVLroot; 
while (T != NULL) 
{ 
if (strcmp(x.key, T->data.key) == 0) 
{ 
cout << "Meaning is: " << T->data.meaning << endl; 
return; 
} 
if (strcmp(x.key, T->data.key) > 0) 
T = T->right; 
else 
T = T->left; 
} 
cout << "Key not found." << endl; 
} 
 
void AVL::printTree() 
{ 
cout << "Inorder traversal of AVL tree:" << endl; 
inorder1(AVLroot); 
cout << endl; 
} 
 
void AVL::copyToFile() 
{ 
ofstream file("tree.txt"); 
if (!file) 
{ 
cout << "Unable to open file." << endl; 
return; 
} 
copyHelper(AVLroot, file); 
file.close(); 
cout << "Tree copied to file successfully." << endl; 
} 
 
void AVL::copyHelper(node *T, ofstream &file) 
{ 
if (T == NULL) 
return; 
copyHelper(T->left, file); 
file << T->data.key << " " << T->data.meaning << endl; 
copyHelper(T->right, file); 
} 
 
void AVL::menu() 
{ 
int choice; 
do 
{ 
cout << "\nMenu:\n"; 
cout << "1. Print Inorder Traversal\n"; 
cout << "2. Print Preorder Traversal\n"; 
cout << "3. Copy Tree to File\n"; 
cout << "4. Search for a Word\n"; 
cout << "5. Exit\n"; 
cout << "Enter your choice: "; 
cin >> choice; 
switch (choice) 
{ 
case 1: 
inorder(); 
break; 
case 2: 
preorder(); 
break; 
case 3: 
copyToFile(); 
break; 
case 4: 
{ 
word w; 
cout << "Enter the word to search: "; 
cin >> w.key; 
search(w); 
} 
break; 
case 5: 
cout << "Exiting...\n"; 
break; 
default: 
cout << "Invalid choice. Please try again.\n"; 
} 
} while (choice != 5); 
} 
 
void AVL::userInput() 
{ 
int numWords; 
cout << "Enter the number of words to add: "; 
cin >> numWords; 
for (int i = 0; i < numWords; ++i) 
{ 
word w; 
cout << "Enter word " << i + 1 << " (key meaning): "; 
cin >> w.key >> w.meaning; 
insert(w); 
} 
} 
 
int main() 
{ 
AVL A; 
A.userInput(); // Take user input for adding words 
A.menu(); 
 
return 0; 
} 
