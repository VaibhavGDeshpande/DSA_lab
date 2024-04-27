#include <iostream>
using namespace std;

struct node
{
    int data;
    node *next;
} *hashtable[10];

class hashg
{
public:
    hashg()
    {
        for (int i = 0; i < 10; i++)
        {
            hashtable[i] = NULL;
        }
    }
    int hashfunction(int value)
    {
        return value % 10;
    }
    node *create_node(int x)
    {
        node *temp = new node;
        temp->data = x;
        temp->next = NULL;
        return temp;
    }
   
    void chaining(int val)
    {
        int hash_val = hashfunction(val);
        node *head = create_node(val);
        node *temp = hashtable[hash_val];
        if (temp == NULL)
        {
            hashtable[hash_val] = head;
        }
        else
        {
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = head;
        }
    }
    void display_chaining()
    {
        for (int i = 0; i < 10; i++)
        {
            node *temp = new (node);
            temp = hashtable[i];
            cout << "a[" << i << "] :";
            while (temp != NULL)
            {
                cout << "->" << temp->data;
                temp = temp->next;
            }
            cout << endl;
        }
    }
    int search(int key){
        int hash_value = hashfunction(key);
        node* temp = hashtable[hash_value];
        while(temp != NULL){
            if(temp->data == key){
                cout << "Key found at index " << hash_value << endl;
                return hash_value;
            }
            temp = temp->next;
        }
        cout << "Key not found" << endl;
        return -1;
    }

    int delete_node(int key){
        int hash_value = hashfunction(key);
        node* temp = hashtable[hash_value];
        node* head = hashtable[hash_value];
        if(temp == NULL){
            cout << "Key not found" << endl;
            return -1;
        }
        if(temp->data == key){
            hashtable[hash_value] = temp->next;
            delete temp;
            return 1;
        }

        while(temp != NULL){
            if(temp->data == key){
                while(head->next != temp){
                    head = head->next;
                }
                head->next = temp->next;
                delete temp;
                return 1;
            }
            temp = temp->next;
        }
        return -1;
    }
};

int main(){
    hashg h;
    int opt, num, num2;
    int flag = 1;
    while(flag == 1){
        cout<<"<------------------------------------->"<<endl;
        cout << "1. Insert an element" << endl;
        cout << "2. Display" << endl;
        cout << "3. Search element" << endl;
        cout << "4. Delete element" << endl;
        cout << "5. Exit" << endl;
        cout<<"<------------------------------------->"<<endl;

        cout << "Enter the option: ";
        cin >> opt;
        switch(opt){
            case 1:
                cout << "Enter the element: ";
                cin >> num;
                h.chaining(num);
                break;
            case 2:
                h.display_chaining();
                break;
            case 3:
                cout << "Enter the element to search: ";
                cin >> num2;
                h.search(num2);
                break;
            case 4:
                cout << "Enter the element to delete: ";
                cin >> num2;
                h.delete_node(num2);
                break;
            case 5:
                cout << "Program ended" <<endl;
                flag = 0;
        }
    }
    return 0;
}

