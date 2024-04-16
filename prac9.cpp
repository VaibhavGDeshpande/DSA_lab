
#include <iostream>
#include <string>
#include <fstream>
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
    int height(node *T);

public:
    AVL()
    {
        AVLroot = NULL;
    }
    void insert(word x) { AVLroot = insert1(AVLroot, x); }
    void preorder() { preorder1(AVLroot); }
    void inorder() { inorder1(AVLroot); }
    void levelwise();
    void search(word x);
    void makenull()
    {
        AVLroot = NULL;
    }
};

void AVL::search(word x)
{
    node *T = AVLroot;
    while (T != NULL)
    {
        if (strcmp(x.key, T->data.key) == 0)
        {
            cout << "Meaning is:" << T->data.meaning;
            return;
        }
        else if (strcmp(x.key, T->data.key) > 0)
            T = T->right;
        else
            T = T->left;
    }
    cout << "\n key not found:";
}
node *AVL::insert1(node *T, word x)
{
    if (T == NULL)
    {
        T = new node;
        T->data = x;
        T->left = NULL;
        T->right = NULL;
    }
    else if (strcmp(x.key, T->data.key) < 0)
    {
        T->left = insert1(T->left, x);
        if (BF(T) == 2)
        {
            if (strcmp(x.key, T->left->data.key) < 0)
                T = LL(T);
            else
                T = LR(T);
        }
        T->ht = height(T);
    }
    else
    {

        if (strcmp(x.key, T->data.key) > 0)
        {
            T->right = insert1(T->right, x);
            if (BF(T) == -2)
            {
                if (strcmp(x.key, T->right->data.key) > 0)
                {
                    T = RR(T);
                }
                else
                    T = RL(T);
            }
        }
    }
    return (T);
}

int AVL::height(node *T)
{
    int lh, rh;
    if (T == NULL)
        return (0);
    if (T->left == NULL)
        lh = 0;
    else
        lh = 1 + T->left->ht;
    if (T->right == NULL)
        rh = 0;
    else
        rh = 1 + T->right->ht;
    if (lh > rh)
        return (lh);
    return (rh);
}
node *AVL ::rotateright(node *x)
{
    node *y;
    y = x->left;
    x->left = y->right;
    y->right = x;
    x->ht = height(x);

    y->ht = height(y);
    return (y);
}
node *AVL ::rotateleft(node *x)
{
    node *y;
    y = x->right;
    x->right = y->left;
    y->left = x;
    x->ht = height(x);
    y->ht = height(y);
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
    T->left = rotateright(T->left);
    T = rotateleft(T);
    return (T);
}
int AVL::BF(node *T)
{
    int lh, rh;
    if (T == NULL)
        return (0);

    if (T->left == NULL)
        lh = 0;
    else
        lh = 1 + T->left->ht;
    if (T->right == NULL)
        rh = 0;
    else
        rh = 1 + T->right->ht;
    return (lh - rh);
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

int main()
{
    AVL A;
    int n, i, op;
    word x;
    ifstream f1;
    f1.open("indata.txt", ios::in);
    do
    {
        cout << "\n1)create:";
        cout << "\n2)search:";
        cout << "\n3)print:";
        cout << "\n4)quit:";
        cout << "\n Enter your choice:";
        cin >> op;
        switch (op)
        {
        case 1:
            A.makenull();
            while (!f1.eof())
            {
                f1 >> x.key >> x.meaning;
                A.insert(x);
            }
            break;
        case 2:
            cout << "\n Enter a data:";
            cin >> x.key;
            A.search(x);
            break;
        case 3:
            cout << "\npreorder sequence:\n";

            A.preorder();
            cout << "\nInordersequence:\n";
            A.inorder();
            break;
        }
    } while (op != 4);
}
