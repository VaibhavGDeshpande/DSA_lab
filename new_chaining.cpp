#include<iostream>
#include<cstring>

using namespace std;

class Hashfunction{
    typedef struct node{
        int key;
        char name[10];
    }Hash;
    
    Hash h[10];
    public:
        Hashfunction(){
            int i;
            for(i=0;i<10;i++)
            {
                h[i].key=-1;
                strcpy(h[i].name,"NULL");
            }
        }
        void insert();
        void display();
};

void Hashfunction :: display()
{
    int i;
        cout<<"\n\t\tkey\t\t\tName:";

    for (i=0;i<10;i++)
    {
        cout<<"\n\th["<<i<<"]\t"<<h[i].key<<"\t\t"<<h[i].name<<endl;
    }
}

void Hashfunction :: insert()
{
    char ans,n[10],ntemp[10];
    long k,temp;
    int v,hi,cnt=0,flag=0,i;

    do {
        if (cnt>=10)
        {
            cout<<"\n\t Hash Table is full"<<endl;
            break;
        }
        cout<<"Enter telephone No.:-";
        cin>>k;
        cout<<"Enter client name:-";
        cin>>n;
        hi=k%10;
        if (h[hi].key==-1)
        {
            h[hi].key=k;
            strcpy(h[hi].name,n);
        }
        else{
            if(h[hi].key%10!=hi)
            {
                temp=h[hi].key;
                strcpy(ntemp,h[hi].name);
                h[hi].key=k;
                strcpy(h[hi].name,n);

                for(i=hi+1;i<10;i++)
                {
                    if(h[i].key==-1)
                    {
                        h[i].key=temp;
                        strcpy(h[i].name,ntemp);
                        flag=1;
                        break;
                    }
                }
                for(i=0;i<hi && flag==0;i++)
                {
                    if(h[hi].key==-1)
                    {
                        h[hi].key=temp;
                        strcpy(h[hi].name,ntemp);
                        break;
                    }
                }
            }
            else{
                for(i=hi+1;i<10;i++)
                {
                    if(h[i].key==-1)
                    {
                        h[i].key=k;
                        strcpy(h[i].name,n);
                        flag=1;
                        break;
                    }
                }
                for(i=0;i<hi && flag==0;i++)
                {
                    if(h[i].key=k==-1)
                    {
                        h[i].key=k;
                        strcpy(h[hi].name,n);
                        break;
                    }
                }
            }
        }
        flag=0;
        cnt++;
        cout<<"\nDo you wish to insert more keys:y/n"<<endl;;
        cin>>ans;
    }while(ans=='y'|| ans=='Y');
}

int main(void)
{
    long k;
    int ch,index;
    char ans;
    Hashfunction obj;
    obj.insert();
    obj.display();
    return 0;
}