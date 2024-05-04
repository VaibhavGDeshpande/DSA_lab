#include <iostream>
#define size 50
using namespace std;
struct node
{
	int data;
	node *L;
	node *R;
};
node *root, *temp, *t1;
int count, key;
class bst
{
public:
	int front, rear;
	void create();
	void insert(node *, node *);
	void disin(node *);
	void dispre(node *);
	void dispost(node *);
	void search(node *, int);
	int height(node *);
	void mirror(node *);
	void findminmax();
	void enque(node *);
	node *deque();
	void bfs();
	void del();
	node *delet(node *, int);
	node *findmin(node *);
	node *que[size];
	bst()
	{
		root = NULL;
		count = 0;
		front = rear = -1;
	}
};
void bst::bfs()
{
	node *t = new node;
	node *dummy = new node;
	if (dummy == NULL)
	{
		cout << "Insufficient memory :(";
	}
	dummy->L = root;
	dummy->R = NULL;
	dummy->data = ' ';
	t = dummy->L;
	enque(t);
	enque(dummy);
	t = deque();
	while (front != rear)
	{
		if (t != dummy)
		{
			cout << " " << t->data;
			if (t->L != NULL)
			{
				enque(t->L);
			}
			if (t->R != NULL)
			{
				enque(t->R);
			}
		}
		else
		{
			enque(t);
			cout << "\n";
		}
		t = deque();
	}
}
void bst::enque(node *n)
{
	if (rear == size - 1)
		cout << "Queue is full";
	rear = rear + 1;
	que[rear] = n;
}
node *bst::deque()
{
	node *n;
	if (front == rear)
		cout << "Queue is empty";
	front++;
	n = que[front];
	return n;
}
void bst::create()
{
	char ans;
	do
	{
		temp = new node;
		cout << "Enter the data : ";
		cin >> temp->data;
		temp->L = NULL;
		temp->R = NULL;
		if (root == NULL)
		{
			root = temp;
		}
		else
			insert(root, temp);
		cout << "Do you want to insert more value : " << endl;
		cin >> ans;
		count++;
		cout << endl;
	} while (ans == 'y');
	cout << "The Total no.of nodes are:" << count;
}
void bst::insert(node *root, node *temp)
{
	if (temp->data > root->data)
	{
		if (root->R == NULL)
		{
			root->R = temp;
		}
		else
			insert(root->R, temp);
	}
	else
	{
		if (root->L == NULL)
		{
			root->L = temp;
		}
		else
			insert(root->L, temp);
	}
}

void bst::disin(node *root)
{
	if (root != NULL)
	{
		disin(root->L);
		cout << root->data << "\t";
		disin(root->R);
		count++;
	}
}

void bst::dispre(node *root)
{
	if (root != NULL)
	{
		cout << root->data << "\t";
		dispre(root->L);
		dispre(root->R);
	}
}

void bst::dispost(node *root)
{
	if (root != NULL)
	{
		dispost(root->L);
		dispost(root->R);
		cout << root->data << "\t";
	}
}

void bst::search(node *root, int key)
{
	int flag = 0;
	cout << "\nEnter your key : " << endl;
	cin >> key;
	temp = root;
	while (temp != NULL)
	{
		if (key == temp->data)
		{
			cout << "Key found:)\n";
			flag = 1;
			break;
		}
		node *parent = temp;
		if (key > parent->data)
		{
			temp = temp->R;
		}
		else
		{
			temp = temp->L;
		}
	}
	if (flag == 0)
	{
		cout << "Key not found :(" << endl;
	}
}
int bst::height(node *root)
{
	int hl, hr;
	if (root == NULL)
	{
		return 0;
	}
	else if (root->L == NULL && root->R == NULL)
	{
		return 0;
	}
	hr = height(root->R);
	hl = height(root->L);
	if (hr > hl)
	{
		return (1 + hr);
	}
	else
	{
		return (1 + hl);
	}
}
void bst::findminmax()
{
	if (root == NULL)
	{
		cout << "\n Tree not exist";
	}
	else
	{
		t1 = root;

		while (t1->L != NULL)
		{
			t1 = t1->L;
		}

		cout << "\n Smallest no." << t1->data;
		t1 = root;

		while (t1->R != NULL)
		{
			t1 = t1->R;
		}
		cout << "\n Largest no." << t1->data;
	}
}

void bst::mirror(node *root)
{
	temp = root;
	if (root != NULL)
	{
		mirror(root->L);
		mirror(root->R);
		temp = root->L;
		root->L = root->R;
		root->R = temp;
	}
}
void bst::del()
{
	int x;
	cout << "\nEnter data to be deleted";
	cin >> x;
	delet(root, x);
}
node *bst::delet(node *T, int x)
{
	if (T == NULL)
	{
		cout << "\nElement not found";
		return (T);
	}
	if (x < T->data)
	{
		T->L = delet(T->L, x);
		return (T);
	}
	if (x > T->data)
	{
		T->R = delet(T->R, x);
		return T;
	}
	if (T->L == NULL && T->R == NULL)
	{
		temp = T;
		free(temp);
		return (NULL);
	}
	if (T->L == NULL)
	{
		temp = T;
		T = T->R;
		delete temp;
		return T;
	}
	if (T->R == NULL)
	{
		temp = T;
		T = T->L;
		delete temp;
		return T;
	}
	temp = findmin(T->R);
	T->data = temp->data;
	T->R = delet(T->R, temp->data);
	return T;
}
node *bst::findmin(node *T)
{
	while (T->L != NULL)
	{
		T = T->L;
	}
	return T;
}
int main()
{
	bst t;
	int ch;
	char ans;
	do
	{
		cout << "\n*****************MENU******************";
		cout << "\n1-Insert new node\n2-Number of nodes in longest path\n3-Minimum and Maximum node\n4-Mirror\n5-Search element\n6-Inorder Traversal\n7-Preorder Traversal\n8-Postorder Traversal\n9-Delete Element\n10-BFS" << endl;
		cout << "\nEnter your choice...";
		cin >> ch;
		switch (ch)
		{
		case 1:
			t.create();
			break;
		case 2:
			cout << "\nNumber of nodes in longest path:" << (1 + (t.height(root)));
			break;
		case 3:
			t.findminmax();
			break;
		case 4:
			t.mirror(root);
			cout << "\nThe mirror of tree is: ";
			t.disin(root);
			break;
		case 5:
			t.search(root, key);
			break;
		case 6:
			cout << "\n***************INORDER**************" << endl;
			t.disin(root);
			break;
		case 7:
			cout << "\n***************PREORDER**************" << endl;
			t.dispre(root);
			break;
		case 8:
			cout << "\n*******************POSTORDER**************" << endl;
			t.dispost(root);
			break;
		case 9:
			t.del();
			break;
		case 10:
			cout << "\n**********BFS TRAVERSAL***************\n";
			t.bfs();
			break;
		}
		cout << "\nDo you want to continue : ";
		cin >> ans;
	} while (ans == 'y');
	return 0;
}
