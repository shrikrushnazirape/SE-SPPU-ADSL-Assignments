/*
Beginning with an empty binary search tree, Construct binary search tree by inserting
the values in the order given. After constructing a binary tree -
i. Insert new node, ii. Find number of nodes in longest path from root, iii. Minimum data
value found in the tree, iv. Change a tree so that the roles of the left and right pointers
are swapped at every node, v. Search a value
*/

#include <iostream>
#define max 20
using namespace std;

class Node{
	int data;
	Node *lchild, *rchild;
public:
	Node(){
		lchild = NULL;
		rchild = NULL;
		data = 0;
	}
	Node(int k){
		lchild = NULL;
		rchild = NULL;
		data = k;
	}

	friend class Queue;
	friend class Stack;
	friend class BT;
};

class Queue{
	int front,rear;
	int count;
	Node *item[max];
public:
	Queue(){
		front = -1;
		rear = -1;
		count = 0;
	}

	bool isEmpty();
	bool isFull();
	void push(Node *ptr);
	Node* pop();
	void printQueue();
	int Qsize();
};

bool Queue::isEmpty(){
	if(front == -1 || front > rear){
		return true;
	}
	else return false;
}

bool Queue::isFull(){
	if(rear == max -1){
		return true;
	}
	else return false;
}

void Queue::push(Node *ptr){
	if(this->isFull()){
		cout<<"Queue is Full \n";
		return;
	}
	else if(front == -1){
		front++;
		count++;
		rear ++;
		item[rear] = ptr;
	}
	else{
		rear ++;
		count++;
		item[rear]=ptr;
	}
}

Node* Queue::pop(){

	if(isEmpty()){
		cout<<"Nothing to show";
		return NULL;
	}
	Node *temp = new Node();
	temp = item[front];
	front ++;
	count--;
	return temp;
}

int Queue::Qsize()
{
    return count;
}

void Queue::printQueue(){
	if(isEmpty()){
		cout<<"Empty!! nothing to show\n";
		return;
	}
	for(int i=front; i<=rear; i++){
		cout<<item[i]->data<<" ";
	}
}

class Stack{
	int top;
	Node* items[max];
public:
	Stack(){
		top = -1;
	}
	bool isEmpty();
	void push(Node * ptr);
	Node *pop();
};

bool Stack::isEmpty(){
	return (top < 0);
}

void Stack:: push(Node* ptr){
	if(top >=(max-1)){
		cout<<"Stack Overflow";
	}
	items[++top]=ptr;
}

Node* Stack::pop(){
	if(isEmpty()){
		return NULL;
	}
	return items[top--];

}

class BT{
	Node *root;
public:
	BT(){
		root=NULL;
	}
	Node* getroot();
	void createTreeNonRecursivly();
	void createTreeRecursivly();
	Node* createrec();

	void inorderTraversalRecursivly(Node *t);
	void preorderTraversalRecursivly(Node *t);
	void postorderTraversalRecursivly(Node *t);

	void inorderTraversalIterativly();
	void preorderTraversalIterativly();
	void postorderTraversalIterativly();

	int findmax(int a,int b);
	int findheightrecursively(Node *t);
	int findheightiteratively();

	void swaptreerecursively(Node *t);
	void swaptreeiteratively();

	int leafnoderecursively(Node *t);
	int internalnoderecursively(Node *t);
	int leafnodeiteratively();
	int internalnodeiteratively();

    Node* CopyBTrecursively(Node *t);
    void operator = (BT & t1);

    void DeleteBTrecursively(Node *t);
    void DeleteBTiteratively();

};

Node* BT::getroot()
{
    return root;
}

void BT::createTreeNonRecursivly(){
	Queue q;
	cout<<"Enter the Root Data :- ";
	int n;
	cin>>n;
	Node *t = new Node(n);
	if(root ==NULL){
		root =t;
		q.push(t);
	}
	while(!q.isEmpty()){
		Node* t2 = q.pop();
		cout<<"press 1 if has left node else 0 ";
		int k1;
		cin>>k1;
		if(k1 ==1){
			cout<<"Enter the left data :- ";
			int ldata;
			cin>>ldata;
			Node *left = new Node(ldata);
			t2->lchild = left;
			q.push(t2->lchild);
		}
		cout<<"press 1 if has right node else 0 ";
		int k2;
		cin>>k2;
		if(k2 ==1){
			cout<<"Enter the right data :- ";
			int rdata;
			cin>>rdata;
			Node *right = new Node(rdata);
			t2->rchild = right;
			q.push(t2->rchild);
		}
	}
}

Node* BT::createrec(){
	int data;
	cout<<"Enter the Data else enter the -1 ";
	cin>>data;
	if(data == -1){
		return NULL;
	}

	Node *t = new Node(data);
	cout<<"Enter the left child data of "<<t->data <<" ";
	t->lchild=createrec();
	cout<<"Enter the right child data of "<<t->data <<" ";
	t->rchild=createrec();
	return t;
}

void BT::createTreeRecursivly(){
	cout<<"Creating the list  Recursively ";
	Node *treelist = createrec();
	root = treelist;
}

void BT::inorderTraversalRecursivly(Node* t){
	if(t!=NULL){
		inorderTraversalRecursivly(t->lchild);
		cout<<t->data << " -> ";
		inorderTraversalRecursivly(t->rchild);
	}
}

void BT::preorderTraversalRecursivly(Node *t){
	if(t!=NULL){
		cout<<t->data<< " -> ";
		preorderTraversalRecursivly(t->lchild);
		preorderTraversalRecursivly(t->rchild);
	}
}

void BT::postorderTraversalRecursivly(Node *t){
	if(t!=NULL){
		postorderTraversalRecursivly(t->lchild);
		postorderTraversalRecursivly(t->rchild);
		cout<<t->data<<" -> ";
	}
}

void BT::inorderTraversalIterativly(){
	Stack s;
	Node *curr = root;
	while(curr !=NULL || s.isEmpty() == false){
		while(curr!=NULL){
			s.push(curr);
			curr = curr->lchild;
		}
		curr = s.pop();
		cout<<curr->data<<" -> ";
		curr = curr->rchild;
	}
}

void BT::preorderTraversalIterativly(){
	if(root == NULL){
		return;
	}
	Stack s;
	s.push(root);
	while(!s.isEmpty()){
		Node *node = s.pop();
		cout<<node->data<<" -> ";

		if(node->rchild){
			s.push(node->rchild);
		}
		if(node->lchild){
			s.push(node->lchild);
		}
	}
}

void BT::postorderTraversalIterativly(){
	if(root == NULL){
		return;
	}
	else{
		Stack s1, s2;
		s1.push(root);
		Node *node;
		while(!s1.isEmpty()){
			node=s1.pop();
			s2.push(node);

			if(node->lchild){
				s1.push(node->lchild);
			}
			if(node->rchild){
				s1.push(node->rchild);
			}
		}
		while(!s2.isEmpty()){
			node = s2.pop();
			cout<<node->data<<" -> ";
		}

	}
}

int BT::findmax(int a,int b)
{
    if(a>=b)
        return a;
    else
        return b;
}

int BT::findheightrecursively(Node *t)
{

    if (t == NULL) {
        return -1;
    }
    return 1 + findmax(findheightrecursively(t->lchild),findheightrecursively(t->rchild));
}

int BT::findheightiteratively()
{
    if(root==NULL)
    {
        return 0;
    }
    Queue Q;
    Q.push(root);
    int height=0;
    while(true)
    {
        int nodecount=Q.Qsize();
        if(nodecount==0)
        {
          return height;
        }
        height++;
        while(nodecount>0)
        {
            Node* current2 = Q.pop();
            if(current2->lchild!=NULL)
                Q.push(current2->lchild);
            if(current2->rchild!=NULL)
                Q.push(current2->rchild);
            nodecount--;
        }
    }

}

void BT::swaptreerecursively(Node *t)
{
    if(t==NULL)
        return;
    else
    {
        Node* temp;
        swaptreerecursively(t->lchild);
        swaptreerecursively(t->rchild);
        temp=t->lchild;
        t->lchild=t->rchild;
        t->rchild=temp;
    }
}

void BT::swaptreeiteratively()
{
    if(root==NULL)
    {
        return ;
    }
    Queue Q;
    Q.push(root);
    while(!Q.isEmpty())
    {
        Node* temp6=Q.pop();
        swap(temp6->lchild,temp6->rchild);
        if(temp6->lchild)
            Q.push(temp6->lchild);
        if(temp6->rchild)
            Q.push(temp6->rchild);
    }
}

void BT::operator = (BT &t1){
	root = CopyBTrecursively(t1.root);
}

Node * BT::CopyBTrecursively(Node* ptr){
    	Node *copyNode = NULL;
	if(ptr){
		copyNode = new Node(ptr->data);
		copyNode->lchild = CopyBTrecursively(ptr->lchild);
		copyNode->rchild = CopyBTrecursively(ptr->rchild);
	}
	return copyNode;
}

int BT::leafnoderecursively(Node *t)
{
    if(t==NULL)
        return 0;
    if(t->lchild==NULL && t->rchild==NULL)
        return 1;
    else
        return leafnoderecursively(t->lchild)+leafnoderecursively(t->rchild);
}

int BT::internalnoderecursively(Node *t)
{

    if(t == NULL || (t->lchild == NULL && t->rchild == NULL))
        return 0;
    return 1+internalnoderecursively(t->lchild)+internalnoderecursively(t->rchild);
}

int BT::leafnodeiteratively()
{
    if(root==NULL)
        return 0;
    Queue Q;
    int count=0;
    Q.push(root);
    while(!Q.isEmpty())
    {
        Node* temp4=Q.pop();
        if(temp4->lchild!=NULL)
            Q.push(temp4->lchild);
        if(temp4->rchild!=NULL)
            Q.push(temp4->rchild);
        if(temp4->lchild==NULL && temp4->rchild==NULL)
            count++;
    }
    return count;
}

int BT::internalnodeiteratively()
{
    if(root == NULL)
        return 0;
    Queue Q;
    int count1=0;
    Q.push(root);
    while(!Q.isEmpty())
    {
        Node *temp5=Q.pop();
        if(temp5->lchild!=NULL)
            Q.push(temp5->lchild);
        if(temp5->rchild!=NULL)
            Q.push(temp5->rchild);
        if(temp5->lchild!=NULL && temp5->rchild!=NULL)
            count1++;

    }
    return count1;
}

void BT::DeleteBTrecursively(Node* t)
{
    if (t==NULL)
        return;
    DeleteBTrecursively(t->lchild);
    DeleteBTrecursively(t->rchild);
    cout << "\n Deleting node: " <<t->data;
    delete t;
}

void BT::DeleteBTiteratively()
{
    if(root==NULL)
    {
        return;
    }
    Queue Q;
    Q.push(root);
    while(!Q.isEmpty())
    {
        Node *temp3=Q.pop();
        if(temp3->lchild!=NULL)
        {
            Q.push(temp3->lchild);
        }
        if(temp3->rchild!=NULL)
        {
            Q.push(temp3->rchild);
        }
        delete temp3;
    }
    root=NULL;
}

int mainMenu(){
	int ch;
	cout<<"\n-----------------------Menu------------------------\n";
	cout<<"\n1.	 Recursive Operation";
	cout<<"\n2.	 Iterative Operation";
	cout<<"\n0.	 End the Prgoram";
	cout<<"\nEnter the Correct Option :- ";
	cin>>ch;
	cout<<"\n----------------------------------------------------\n";
	return ch;
}

int RecMenu(){
	int k;
	cout<<"\n ------------------Recursive Menu-----------------";
	cout<<"\n1.	Inorder Traversal";
	cout<<"\n2.	Preorder Traversal";
	cout<<"\n3.	Postorder Traversal";
	cout<<"\n4.	Mirror The Tree";
	cout<<"\n5.	Height of the Tree";
	cout<<"\n6.	Copy the Tree";
	cout<<"\n7.	No of Nodes in the tree";
	cout<<"\n8.	Erase all nodes in tree";
	cout<<"\n0.	Return to Main Menu";
	cout<<"\n Enter the Correct Option :- ";
	cin>>k;
	cout<<"\n---------------------------------------------------\n";
	return k;
}

int NonRecMenu(){
	int l;
	cout<<"\n ------------------Iterative Menu-----------------";
	cout<<"\n1.	Inorder Traversal";
	cout<<"\n2.	Preorder Traversal";
	cout<<"\n3.	Postorder Traversal";
	cout<<"\n4.	Mirror The Tree";
	cout<<"\n5.	Height of the Tree";
	cout<<"\n6.	Copy the Tree";
	cout<<"\n7.	No of Nodes in the tree";
	cout<<"\n8.	Erase all nodes in tree";
	cout<<"\n0.	Return to Main Menu";
	cout<<"\n Enter the Correct Option :- ";
	cin>>l;
	cout<<"\n---------------------------------------------------\n";
	return l;
}

int main(){
    BT b,c,d,e;
	int ch;
	do{
		ch = mainMenu();
		switch (ch)
		{
		case 1:
		{


			int cr;
			b.createTreeRecursivly();
			Node *ptr1;
			ptr1= b.getroot();
			do{
			cr = RecMenu();
			switch (cr)
			{
			case 1:
				cout<<"\nInorder Traversal :- ";
				b.inorderTraversalRecursivly(ptr1);
				break;
			case 2:
				cout<<"\nPreorder Traversal :- ";
				b.preorderTraversalRecursivly(ptr1);
				break;
			case 3:
				cout<<"\nPostorder Traversal :- ";
				b.postorderTraversalRecursivly(ptr1);
				break;
			case 4:
			    cout<<"Original tree :-";
			    b.inorderTraversalRecursivly(ptr1);
				cout<<"\nMirroring the Tree :-";
				b.swaptreerecursively(ptr1);
				b.inorderTraversalRecursivly(ptr1);
				break;
			case 5:
				cout<<"\n Height of the tree :- ";
				cout<<b.findheightrecursively(ptr1);
				break;
			case 6:
				cout<<"\n Copying the tree :- ";
				d=b;
				cout<<"\nFirst Tree :- ";
				b.inorderTraversalIterativly();
				cout<<"\nSecond Tree :- ";
				d.inorderTraversalIterativly();
				break;
			case 7:
				cout<<"\n Node count:- ";
				int full, internal, leaf;
				internal = b.internalnoderecursively(ptr1);
				leaf = b.leafnoderecursively(ptr1);
				full = internal+leaf;
				cout<<"\n Total Nodes :- "<<full;
				cout<<"\n Internal Nodes :- "<<internal;
				cout<<"\n Leaf Nodes :- "<<leaf;
				break;
			case 8:
				cout<<"\n Deleting the tree";
				b.DeleteBTrecursively(ptr1);
				break;
			case 0:
				cout<<"\n Returning to the main menu";
				break;
			default:
				cout<<"\n Wrong Option Selected";
				break;

			}
			}while(cr!=0);
			break;
		}
		case 2:
		{
			int cnr;
			c.createTreeNonRecursivly();
			do{
			cnr = NonRecMenu();
			switch (cnr)
			{
			case 1:
				cout<<"\n Inorder Traversal :- ";
				c.inorderTraversalIterativly();
				break;
			case 2:
				cout<<"\n Preorder Traversal :- ";
				c.preorderTraversalIterativly();
				break;
			case 3:
				cout<<"\n Postorder Traversal :- ";
				c.postorderTraversalIterativly();
				break;
			case 4:
			    cout<<"Original tree :- ";
                c.inorderTraversalIterativly();
				cout<<"\nmirroring the Tree :- ";
				c.swaptreeiteratively();
				c.inorderTraversalIterativly();
				break;
			case 5:
				cout<<"\n Height of the tree :- ";
				int k;
				k= c.findheightiteratively();
				cout<<k;
				break;
			case 6:
				cout<<"\n Copying the tree :- ";
				e=c;
				cout<<"\nFirst Tree :- ";
				c.inorderTraversalIterativly();
				cout<<"\nSecond Tree :- ";
				e.inorderTraversalIterativly();
				break;
			case 7:
				cout<<"\n Node Count";
				int x,y,z;
				x=c.internalnodeiteratively();
				y=c.leafnodeiteratively();
				z=x+y;
				cout<<"\nTotal :- "<<z;
				cout<<"\ninternal  :- "<<x;
				cout<<"\nleaf :- "<<y;
				break;
			case 8:
				c.DeleteBTiteratively();
				cout<<"\nDeleted the Tree";
				break;
			case 0:
				cout<<"\nReturning to the main menu";
				break;
			default:
				cout<<"\nincorrect Option";
				break;

			}
			}while(cnr!=0);
			break;
		}
		case 0:{
			break;
		}
		default:
		{
			cout<<"\nWrong Option ";
			break;
		}
		}
	}while(ch!=0);
	return 0;
}
