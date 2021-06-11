/*
Create an inordered threaded binary tree and perform inorder and preorder traversals. Analyze time and space complexity of the algorithm.*/

#include <iostream>
using namespace std;

class Node
{
    int data;
    Node *rchild, *lchild;
    bool rbit, lbit;

public:
    Node()
    {
        data = 0;
        lchild = NULL;
        rchild = NULL;
        rbit = lbit = false;
    }
    Node(int key)
    {
        data = key;
        lchild = NULL;
        rchild = NULL;
        rbit = lbit = false;
    }
    friend class TBT;
};

class TBT
{
    Node *header, *root;

public:
    TBT()
    {
        header = NULL;
        root = NULL;
    }
    void insertInTBT(int);
    void inorderTraversal();
    void preorderTraversal();
    void search(int , Node*, Node*);
    void deleteNodeTBT(Node *, Node *);
};

void TBT::insertInTBT(int key)
{
    if (root == NULL)
    {
        header = new Node(-99);
        header->rchild = header;
        root = new Node(key);
        root->lchild = header;
        root->rchild = header;
        header->lchild = root;
        cout << "\nRoot Inserted Successfully";
        return;
    }
    Node *ptr, *temp;
    ptr = root;
    temp = new Node(key);
    while (true)
    {
        if (ptr->data > key)
        {
            if (ptr->lbit)
            {
                ptr = ptr->lchild;
            }
            else
            {
                temp->lchild = ptr->lchild;
                temp->rchild = ptr;
                ptr->lbit = true;
                ptr->lchild = temp;
                cout << "\nNode Inserted Successfully";
                return;
            }
        }
        else{
        if (ptr->rbit)
        {
            ptr = ptr->rchild;
        }
        else
        {
            temp->lchild = ptr;
            temp->rchild = ptr->rchild;
            ptr->rchild = temp;
            ptr->rbit = true;
            cout << "\nNode Inserted Successfully";
            return;
        }
        }
    }
}

void TBT::inorderTraversal()
{
    Node *temp = root;
    while (temp->lbit)
    {
        temp = temp->lchild;
    }
    while (temp != header)
    {
        cout << temp->data << " -> ";
        if (temp->rbit)
        {
            temp = temp->rchild;
            while (temp->lbit)
            {
                temp = temp->lchild;
            }
        }
        else
        {
            temp = temp->rchild;
        }
    }
}

void TBT::preorderTraversal()
{
    Node *temp = root;
    while (temp != header)
    {
        cout << temp->data << " -> ";
        if (temp->lbit)
        {
            temp = temp->lchild;
        }
        else
        {
            if (temp->rbit)
            {
                temp = temp->rchild;
            }
            else
            {
                while (temp->rbit == false )
                {
                    temp = temp->rchild;
                }
                temp = temp->rchild;
            }
        }
    }
}

// void TBT::search(int key, Node ** parent, Node **loc){
// 	if(root == NULL){
// 		loc = NULL;
// 		parent = NULL;
// 		return;
// 	}
// 	parent = NULL;
// 	loc =NULL;
// 	Node *ptr;
// 	ptr = root;
// 	while(ptr!= NULL){
// 		if(key == ptr->data){
// 			loc = ptr;
// 			return;
// 		}
// 		else if(key< ptr->data){
// 			parent = ptr;
// 			ptr=ptr->lchild;
// 		}
// 		else{
// 			parent = ptr;
// 			ptr = ptr->rchild;
// 		}
// 	}
// 	if(loc == NULL){
// 		cout<<"Not found";
// 	}

// }

void TBT::deleteNodeTBT(Node *ptr, Node *temp)
{
    if (temp->lbit && temp->rbit)
    {
        Node *cs = temp->rchild;
        while (cs->lbit != 0)
        {
            ptr = cs;
            cs = cs->lchild;
        }
        temp->data = cs->data;
        temp = cs;
        delete temp;
        return;
    }
    if(temp->lbit==0 && (temp->rbit == 0)){
        if(ptr->lbit){
            ptr->lchild = temp->lchild;
            ptr->lbit = 0;
        }
        ptr->rchild = temp->rchild;
        ptr->rbit = 0;
    delete(temp);
    return;
    }
    if(temp->lbit && temp->rbit == 0){
        temp = temp->lchild;
        if(ptr->lchild == temp){
            ptr->lchild = temp;
        }
        else{
            ptr->rchild = temp;
        }
        while(temp->rbit){
            temp = temp->rchild;
        }
    }
}

int main()
{
    TBT t;
    t.insertInTBT(10);
    t.insertInTBT(5);
    t.insertInTBT(15);
    cout << "\n";
    t.inorderTraversal();
    cout << "\n";
    t.preorderTraversal();
    return 0;
}