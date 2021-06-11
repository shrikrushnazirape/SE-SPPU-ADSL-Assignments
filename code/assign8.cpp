/*
Given sequence k = k1 <k2 < … <kn of n sorted keys, with a search probability pi for each key ki . Build the Binary search tree that has the least search cost given the access probability for each key.

Or

A Dictionary stores keywords and its meanings. Provide facility for adding new keywords, deleting keywords, updating values of any entry. Provide facility to display whole data sorted in ascending/ Descending order. Also find how many maximum comparisons may require for finding any keyword. Use Height balance tree and find the complexity for finding a keyword.
*/
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<iomanip>
# define INF 99999999
using namespace std;

class Node
{
	public:
	int data;
	Node *left;
	Node *right;
	Node()
	{
		data = 0;
		left=NULL;
		right=NULL;
	}
	Node(int data)
	{
		this->data=data;
		left=NULL;
		right=NULL;
	}
};


class element
{
	public:
		int cost;
		int root;
	element()
	{
		cost=0;
		root=0;
	}
};


class OBST
{
	Node *root;
	int *keys;
	int *frq;
	int n;

	element **CM;
	public :
		int mincost;
	public:
		OBST()
		{
			 root = NULL;
			 keys = frq = NULL;
			 CM = NULL;
			n = mincost = 0;
		}
		void Add_data();
		void Find_cost();
		int weight(int i,int j);
		void Tree(int n);
		Node* Tree_rec(int i,int j,int n);
		void Preorder(Node *T);
		void Inorder(Node *T);
		void show();

		Node * getroot()
		{
			return root;
		}
};


int OBST::weight(int i,int j)
{
	int sum=0;
	for(int t=i+1;t<=j;t++)
	{
		sum=sum+this->frq[t];
	}
	return sum;
}

void OBST::Add_data()
{
	cout<<"\n\t Enter Total number of keys :  ";
	int n;
	cin>>n;
	this->n=n;
	keys=new int [n+1];
	frq=new int[n+1];
	CM=new element* [n+1];
	for(int i=0;i<=n;i++)
	{
		CM[i]=new element[n+1];
	}
	cout<<"\n\t Enter keys and frequency Pairs... \n"<<endl;
	for(int i=1;i<=n;i++)
	{
		cout << "\n\t Enter Key ["<<i<<"] :  ";
		cin>>keys[i];
		cout << "\n\t Enter Frequency of '"<<keys[i]<<"' :  ";
		cin>>frq[i];

	}
	for(int i=0;i<=n;i++)
	{
		this->CM[i][i].cost=0;
	}
	for(int i=0;i<=n-1;i++)
	{
		this->CM[i][i+1].cost=frq[i+1];
		this->CM[i][i+1].root=i+1;
	}

	this->Find_cost();
}

void OBST::Find_cost()
{
	for(int d=2;d<=n;d++)
	{
		for(int i=0;i<=n-d;i++)
		{
			int min=999999;
			int temp;
			for(int r=i+1;r<=i+d;r++)
			{
				if((CM[i][r-1].cost+CM[r][i+d].cost)<min)
				{
					min=(CM[i][r-1].cost+CM[r][i+d].cost);
					temp=r;

				}
			}
			CM[i][i+d].cost=min+weight(i,i+d);
			CM[i][i+d].root=temp;
		}
	}

	this->mincost=CM[0][n].cost;
	Tree(n);
}

void OBST::Tree(int n)
{
	int ind=CM[0][n].root;
	root=new Node(this->keys[ind]);
	root->left=Tree_rec(0,ind-1,n);
	root->right=Tree_rec(ind,n,n);

}

Node* OBST::Tree_rec(int i,int j,int n)
{
	if(i==j)
	{
		return NULL;
	}
	int ind=CM[i][j].root;
	Node *p=new Node(keys[ind]);
	p->left=Tree_rec(i,ind-1,n);
	p->right=Tree_rec(ind,j,n);
	return p;
}

void OBST::Preorder(Node *T)
{
	if(T!=NULL)
	{
		cout<<T->data<<"  ";
		Preorder(T->left);
		Preorder(T->right);

	}
}
void OBST::Inorder(Node *T)
{
	if(T!=NULL)
	{

		Inorder(T->left);
		cout<<T->data<<"  ";
		Inorder(T->right);

	}
}

void OBST::show()
{
	cout<<"\n\t Cost Matrix :  \n\t\t\t ";
	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=n;j++)
		{
			cout<<CM[i][j].cost<<"-"<<CM[i][j].root<<"  ";
		}
		cout<<"\n\n\t\t\t ";
	}
}

int main()
{
	OBST O;

	char ch;
	do
	{
		cout<<"\n === MAIN MENU ===";
		cout<<"\n\t 1. Insert Data";
		cout<<"\n\t 2. Cost Matrix";
		cout<<"\n\t 3. Traversals of OBST";
		cout<<"\n\t 4. Least Search Cost";
		cout<<"\n\t 5. Exit";
		cout<<"\n\n\t Enter choice :  ";
		cin>>ch;
		switch(ch)
		{

			case '1':
				O.Add_data();
				break;

			case '2':
				O.show();
				break;

			case '3':
				cout<<"\n\t Inorder Traversal     :  ";
				O.Inorder(O.getroot());
				cout<<"\n\t Preorder Traversal    :  ";
				O.Preorder(O.getroot());
				cout<<"\n\n";
				break;

			case '4':
				cout<<"\n\t\t Least Search Cost :  "<<O.mincost;
				cout<<"\n\n";
				break;

			case '5':
				cout<<"\n\t\t Thank You...!!!";
				cout<<"\n\n";
				exit(0);
				break;

			default :
				cout<<"\n\t Invalid choice...!!!";
		}


	}while(ch!='0');
}
