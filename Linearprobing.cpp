#include<iostream>
using namespace std;


struct node{
    public:
        int data;
        node*next;

}*hashtable[10];

class hashg{
    public:
    hashg()
    {
        for(int i=0;i<10;i++)
        {
            hashtable[i]=NULL;
        }
    }
    int hashfunction(int val)
    {
        return (val%10);
    }

    node*create_node(int x)
    {
        node*newnode=new(node);
        newnode->next=NULL;
        newnode->data=x;
        return newnode;
    }

    void disp()
    {
        for(int i=0;i<10;i++)
        {
            node*temp=new(node);
            temp=hashtable[i];
            cout<<"a["<<i<<"] :";
            while(temp!=NULL)
            {
                cout<<"->"<<temp->data;
                temp=temp->next;
            }
            cout<<endl;
        }
    }

    void insert_val(int val)
    {
        int hash_val=hashfunction(val);
        node*temp=new(node);
        node*head=new(node);
        head=create_node(val);
        temp=hashtable[hash_val];
        if(temp==NULL)
        {
            hashtable[hash_val]=head;
        }
        else
        {
            while(temp->next=NULL)
            {
                temp=temp->next;
            }
            temp->next=head;

        }
    }
    void linearprobing(int val)
    {
        int hash_val=hashfunction(val);
        node*temp=new(node);
        node*head=new(node);
        head=create_node(val);
        temp=hashtable[hash_val];
        if(temp==NULL)
        {
            hashtable[hash_val]=head;
        }
        else
        {
            hashtable[(hash_val+1)%10]=head;
        }
    }
    int search_ele(int val)
    {
        bool flag=0;
        int hash_val=hashfunction(val);
        node*temp=hashtable[hash_val];
        cout<<"Element found at: "<<endl;
        while(temp!=NULL)
        {
            if(temp->data==val)
            {
                cout<<hash_val<<":"<<temp->data<<endl;
                flag=1;
                
            }
            temp=temp->next;
            if(!flag)
            return -1;
       
        }
             return 0;
        
    }
    void del_ele(int val)
    {
        int hash_val=hashfunction(val);
        node*temp=hashtable[hash_val];
        
            if(temp==NULL)
            {
            cout<<"No element found"<<endl;
            return;
            }
            else if(temp->data==val)
            {
                hashtable[hash_val]=temp->next;
                return;
            }
            while((temp->next)->data!=val)
            {
                temp=temp->next;
            }
            temp->next=temp->next->next;
            
       }
    

};
int main()
{
    int ch;
    int data,search,del;
    hashg h;
    do{
        cout<<"---------Menu----------"<<endl;
        cout<<"1.insert\n";
         cout<<"2.display\n"; 
         cout<<"3.search\n"; 
           cout<<"4.delete\n"; 
           cout<<"6.linear"<<endl;
         cout<<"5.exit\n"; 
         
         cout<<"Enter your choice: ";
        cin>>ch;
        switch(ch)
        {
            case 1:
            cout<<"Enter the phone no.to insert"<<endl;
            cin>>data;
            h.insert_val(data);
            break;
            case 2:
            h.disp();
            break;
            case 3:
            cout<<"Element to be searched: ";
            cin>>search;
            if(h.search_ele(search)==-1)
            {
                cout<<"No ele for"<<endl;
                continue;
            }
            break;
            case 4:
            cout<<"Enter the ele to be deleted"<<endl;
            cin>>del;
            h.del_ele(del);
            cout<<"ele delted"<<endl;
            break;
            case 5:
            cout<<"Thank you!"<<endl;
            case 6:
            cout<<"Enter the phone no.to insert"<<endl;
            cin>>data;
            h.linearprobing(data);
            break;
        }
    }while(ch!=5);

}
