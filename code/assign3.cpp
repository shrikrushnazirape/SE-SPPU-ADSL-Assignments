/*
Create an inordered threaded binary tree and perform inorder and preorder traversals. Analyze time and space complexity of the algorithm
*/

#include <iostream>

using namespace std;
class Node
{
    int data;
    Node *lchild,*rchild;
    int lbit,rbit;
public:
    Node()
    {
        data=0;
        lchild=NULL;
        rchild=NULL;
        lbit=rbit=0;
    }
    Node(int k)
    {
        data=k;
        lchild=NULL;
        rchild=NULL;
        lbit=rbit=0;
    }
    void getnode()
    {
        cout<<data;
    }
    friend class TBT;
};
class TBT
{
    Node *root,*header;
public:
    TBT()
    {
        root=NULL;
        header=NULL;
    }
    void insertNode(int data);
    void inordertraversal();
    void preordertraversal();
};
void TBT::insertNode(int data)
{
    if(root==NULL)
    {
     header=new Node(-99);
     header->lbit=0;
     header->rbit=0;
     header->rchild=header;
     header->lchild=root;
     root=new Node(data);
     root->lchild=header;
     root->rchild=header;
     cout<<"Root inserted Successfully "<<endl;
     return;
    }
        Node *ptr,*temp;
        ptr=root;
        temp=new Node(data);
        while(1)
        {
            if(ptr->data>data)
            {
                if(ptr->lbit!=0)
                    ptr=ptr->lchild;
                else
                {
                    temp->lbit=0;
                    temp->rbit=0;
                    temp->lchild=ptr->lchild;
                    temp->rchild=ptr;
                    ptr->lbit=1;
                    ptr->lchild=temp;
                    cout<<"Node Inserted Successfully "<<endl;
                    return;
                }
            }
            else
            {
                if(ptr->rbit!=0)
                {
                    ptr=ptr->rchild;
                }
                else
                {
                    temp->lchild=ptr;
                    temp->rchild=ptr->rchild;
                    temp->lbit=temp->rbit=0;
                    ptr->rchild=temp;
                    ptr->rbit=1;
                    cout<<"Node Inserted Successfully "<<endl;
                    return;
                }
             }
           }

}
void TBT::inordertraversal()
{
    Node *t=root;
    while(t->lbit!=0)
    {
        t=t->lchild;
    }
    while(t!=header)
    {
        cout<<t->data<<" -> ";
        if(t->rbit!=0)
        {
           t=t->rchild;
           while(t->lbit!=0)
           {
               t=t->lchild;
           }
        }
        else
        {
            t=t->rchild;
        }
    }
}
void TBT::preordertraversal()
{
    Node *t=root;
    while(t!=header)
    {
        while(t->lbit)
        {
            cout<<t->data<<" -> ";
            t=t->lchild;
        }
        cout<<t->data<<" -> ";
        while(t->rbit==0)
        {
            t=t->rchild;
            if(t==header)
            {
                return;
            }
        }
        t=t->rchild;
    }
}
int main()
{
    TBT T1;
    int data;
    int ch,op=1;
    while(op==1)
    {
    cout<<"\n------------------------------------------------------------------------------------------";
    cout<<"\n1.Insert";
    cout<<"\n2.Inorder Traversal";
    cout<<"\n3.Preorder Traversal";
    cout<<"\n0.Exit";
    cout<<"\n------------------------------------------------------------------------------------------";
    cout<<"\nEnter Choice : ";
    cin>>ch;
    switch(ch)
    {
    case 1:
        cout<<"Enter a data :- ";
        cin>>data;
        T1.insertNode(data);
        break;
    case 2:
        cout<<"Inorder Traversal :- "<<endl;
        T1.inordertraversal();
        cout<<"\nInorder Traversal Done!!!"<<endl;
        break;
    case 3:
        cout<<"Preorder Traversal :- "<<endl;
        T1.preordertraversal();
        cout<<"\nPreorder Traversal Done!!!"<<endl;
        break;
    default:
        cout<<"Enter Correct Option";
        break;
    }
    cout<<"Do you want to continue(1/0)?";
    cin>>op;
    }
    cout<<"\nThank You!!\n";
    return 0;
}
