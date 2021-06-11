#include<bits/stdc++.h>
using namespace std;

class Graph{
    int vertices, edges;
    int **adjmat;
    public:
    Graph(int v, int e){
        this->vertices = v;
        this->edges = e;
        adjmat = new int *[vertices];
        for(int i=0; i<vertices; i++){
            adjmat[i] = new int [vertices];
        }
    }

    void acceptGraph();
    void displayGraph();
    int primsAlgo(int v);
    int kruskal();
    void printmatrix(int **, int);
    int **copymat(int ** ,  int);
    int **getBlankMat(int);
};

void Graph::acceptGraph(){
    for(int i=0; i<edges; i++){
        int source, destination, weight;
        cout<<"\nEnter the details for "<<i<<" th edge : - ";
        cout<<"\nEnter the source :- ";
        cin>>source;
        cout<<"Enter the Destination :- ";
        cin>>destination;
        cout<<"Enter the weight of edge :- ";
        cin>>weight;
        adjmat[source][destination] = weight;
        adjmat[destination][source] = weight;
    }
}

void Graph::displayGraph(){
    cout<<"\ndisplaying graph \n";
    for(int i=0; i<vertices; i++){
        for(int j=0; j<vertices; j++){
            cout<<adjmat[i][j]<<" ";
        }
        cout<<"\n";
    }
}

int Graph::primsAlgo(int v){
    int** resultmat = getBlankMat(vertices);
    int** temp = copymat(adjmat, vertices);

    int count = 0; 
    int visited = 0;
    int weight = 0;
    int t1, t2, v2, temp1, temp2, root_temp1, root_temp2, min;
    int * reached = new int[vertices];
    int * father = new int[vertices];

    for(int i=0; i< vertices; i++)
        reached[i] = 0;
    reached[visited ++] = v;
    for(int i=0; i<vertices; i++)
        father[i] = -1;
    
    

    while (count < vertices-1)
    {
        min = 9999;
        for(int v1 = 0; v1<visited; v1++){
            for(int v2 =0; v2<vertices; v2++){
                if( temp[reached[v1]][v2] != 0   &&
                    temp[reached[v1]][v2] < min
                    ){
                    min = temp[reached[v1]][v2];
                    t1 = reached[v1];
                    t2 = v2;
                }
            }
        }
        
        temp1 = t1;
        temp2 = t2;
        temp[temp1][temp2] = temp[temp2][temp1] = 0;

        while(t1>=0){
            root_temp1 = t1;
            t1 = father[t1];
        }
        while(t2>=0){
            root_temp2 = t2;
            t2 = father[t2];
        }

        if(root_temp1 != root_temp2){
            resultmat[temp1][temp2]= resultmat[temp2][temp1] = min;
            weight += min;
            father[root_temp2] = root_temp1;
            count ++;
            reached[visited ++] =  temp2;

        }
    }
    printmatrix(resultmat, vertices);
    return weight;
}

int Graph::kruskal(){
    int** resultmat = getBlankMat(vertices);
    int** temp = copymat(adjmat, vertices);
    int count = 0;
    int weight = 0;
	int t1, t2, v2, temp1, temp2, root_temp1, root_temp2, min;
	int* father = new int[vertices];
	for (int i = 0; i < vertices; i++)
		father[i] = -1; 

	while (count < vertices - 1) // main loop
	{
		min = INT32_MAX;
		for (int v1 = 0; v1 < vertices; v1++) {
			for (v2 = 0; v2 < vertices; v2++) {
				if ((temp[v1][v2] != 0) && (temp[v1][v2] < min)) {
					min = temp[v1][v2];
					t1 = v1; t2 = v2;
				}
			}
		}
		temp1 = t1;
		temp2 = t2;
		temp[temp1][temp2] = temp[temp2][temp1] = 0; // so that it is marked as visited

		while (t1 >= 0) {
			root_temp1 = t1;
			t1 = father[t1];
		}

		while (t2 >= 0) {
			root_temp2 = t2;
			t2 = father[t2];
		}

		if (root_temp1 != root_temp2) {
			resultmat[temp1][temp2] = resultmat[temp2][temp1] = min;
			weight += min;
			father[root_temp2] = root_temp1;
			count++;
		}
	}
    printmatrix(resultmat, vertices);
    return weight;  
}




void Graph::printmatrix(int ** arr, int v){
    for(int i=0; i<v; i++){
        cout<<" ";
        for(int j=0; j<v; j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<"\n";
    }
}

int **Graph::copymat(int ** arr, int v){
    int ** curr = new int *[v];
    for(int i=0; i<v; i++){
        curr[i] = new int[v];
        for(int j=0; j<v; j++){
            curr[i][j] = arr[i][j];
        }
    }
    return curr;
}

int **Graph::getBlankMat(int v){
    int **newtree = new int *[v];
    for(int i=0;i<v; i++){
        newtree[i] = new int[v];
        for(int j=0; j<v;j++){
            newtree[i][j] = 0;
        }
    }
    return newtree;
}


int main(){
    int v, e;
    cout<<"\nEnter the no of vertice : ";
    cin>>v;
    cout<<"\nEnter the no of edges :";
    cin>>e;

    Graph g(v,e);
    // g.acceptGraph();
    // g.displayGraph();
    // cout<<g.primsAlgo(0);
    // cout<<g.kruskal();
    int ch;
    int k;
    do{
    cout<<"\n------------Menu ------------------";
    cout<<"\n1. Accept the graph ";
    cout<<"\n2. Display the graph ";
    cout<<"\n3. Prims Algorithm ";
    cout<<"\n4. Kruskal Algorithm ";
    cout<<"\n5. Exit ";
    cout<<"\n Enter the choice ";
    cin>>ch;
    switch (ch)
    {
    case 1:
        g.acceptGraph();
        break;

    case 2:
        g.displayGraph();
        break;

    case 3:
        k = g.primsAlgo(0);
        cout<<"Weight is : - " <<k;
        break;

    case 4:
        k = g.kruskal();
        cout<<"Weight is : - "<<k;
        break;

    case 5:
        cout<<"Terminating the program ";
        break;
    
    default:
        cout<<"\nWrong choice ";
        break;
    }
    }while(ch != 5);
    // g.acceptGraph();
    // g.displayGraph();
    // cout<<g.primsAlgo(0);
    // g.displayGraph();
    return 0;
}