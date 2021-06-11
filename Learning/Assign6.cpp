#include<bits/stdc++.h>
#define MaxQSize 20
using namespace std;


// Queue Data Structure


class Queue{
    int arr[MaxQSize];
    int front, rear;

public:
    Queue(){
        front = -1;
        rear = -1;
    
    }
    bool isEmpty(){
        return (front == -1 ||
                front > rear);
    }

    bool isFull(){
        return (rear == MaxQSize-1);
    }

    void enqueue(int data){
        if(isFull()){
            cout<<"!!queue Overflow ";
            return;
        }
        if(isEmpty()){
            front = 0;
            rear = 0;
            arr[rear]=data;
            return;
        }
        rear++;
        arr[rear] = data;

    }
    int dequeue(){
        if(isEmpty()){
            cout<<"nothing to show";
            return -1;
        } 
        int d = arr[front];
        front ++;
        return d;
    }
};






class NodeEdge{
    int data;
    NodeEdge *next;

public:
    NodeEdge(){
        data = 0;
        next = NULL;
    }
    NodeEdge(int k){
        data = k;
        next = NULL;
    }
    friend class Graph;
};

class Graph{
    int noOfVertices, noOfEdges;
    NodeEdge **adjList;


    //data member for traversal
    bool *isVisitedDFS;
    
public:
    Graph(int v, int e){
        this->noOfVertices = v;
        this->noOfEdges = e;
        adjList = new  NodeEdge* [noOfVertices];
       
        for(int i=0; i<noOfVertices; i++){
            adjList[i]=NULL;
            
        }
    }
    void AcceptGraph();
    void DisplayGraph();
    void DFScall(int);
    void DFS(int start, bool visited[]);
    void BFS(int);

};


void Graph::AcceptGraph(){
    int source,  destination;
    for(int i=0; i<noOfEdges; i++){
        cout<<"Enter the details of "<<i+1<<" th edge";
        cout<<"\nEnter the source";
        cin>>source;
        cout<<"Enter the destination";
        cin>>destination;

        NodeEdge * temp1 = new NodeEdge(source);
        NodeEdge * temp2 = new NodeEdge(destination);

        if(adjList[source] == NULL){
            adjList[source] = temp2;
        }
        else{
            NodeEdge *t1 = adjList[source];
            while(t1->next != NULL){
                t1 = t1->next;
            }
            t1->next = temp2;
        }


        if(adjList[destination] == NULL){
            adjList[destination] = temp1;
        }
        else{
            NodeEdge *t2 = adjList[destination];
            while(t2->next != NULL){
                t2 = t2->next;
            }
            t2->next = temp1;
        }
    }
}


void Graph::DisplayGraph(){
    for(int i=0; i<noOfVertices; i++){
        cout<<"--"<<i<<"--->";
        NodeEdge *iterator = adjList[i];
        while(iterator != NULL){
            cout<<"   "<<iterator->data<<"   ";
            iterator = iterator->next;
        }
        cout<<"\n";
    }
}


void Graph::DFScall(int start){
    bool *visited = new bool[noOfVertices];
    for(int i=0; i<noOfVertices; i++){
        visited[i] = false;
    }
    DFS(start, visited);
}


void Graph::DFS(int start, bool visited[]){
    visited[start] = true;
    cout<<start<<" ";
    NodeEdge *temp;
    temp = adjList[start];
    while(temp!=NULL){
        if(!visited[temp->data]){
            DFS(temp->data, visited);
        }
        temp = temp->next;
    }

}

void Graph::BFS(int start){
    bool *visited = new bool[noOfVertices];
    for(int i=0; i<noOfVertices; i++){
        visited[i] = false;
    }
    Queue q;
    q.enqueue(start);
    visited[start] = true;
    while(!q.isEmpty()){
        int d = q.dequeue();
        cout<<d<<" ";
        NodeEdge *temp = adjList[d];

        for(temp; temp!=NULL; temp=temp->next){
            if(!visited[temp->data]){
                visited[temp->data] = true;
                q.enqueue(temp->data);
                
            }            
        }

    }
}

/*

            0
          /   \
         1     2
         | \   |
         |  \  |
         3 --- 4
         |     |
          \   /
            5

*/



int main(){
    int v,e;

    cout<<"\nEnter the no of vertices :- ";
    cin>>v;
    cout<<"\nEnter the no of Edges    :- ";
    cin>>e;
    Graph g(v,e);
    g.AcceptGraph();
    int ch;
    do{
        cout<<"\n------------Menu---------------------";
        cout<<"\n1. Display a Graph ";
        cout<<"\n2. Traversal";
        cout<<"\n0. Exit the program";
        cout<<"\nEnter the correct option ";
        cin>>ch;
        switch (ch)
        {
        case 0:
            cout<<"\nEnding the program ";
            break;
        case 1:
            g.DisplayGraph();

        case 2:
            int k;
            cout<<"\n 1. BFS \n 2. DFS \n Enter option";
            cin>>k;
            if(k==1){
                cout<<"\nBFS Traversal \n";
                g.BFS(0);
            }
            else if(k==2){
                cout<<"\nDFS Traversal \n";
                g.DFScall(0);
            }
            else{
                cout<<"incorrect option";
            }
            break;
        default:
            cout<<"\nIncorrect Option";
            break;
        }

    }while(ch != 0);
    
    cout<<endl;



    
    return 0;
}
