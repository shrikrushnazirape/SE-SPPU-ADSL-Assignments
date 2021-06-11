#include <iostream>
using namespace std;


void init(int**, int);
void print(int**, int);
int** assign(int**, int);

class Graph {
	int vertex, edges;
	int** adj_mat;
public:
	Graph();
	Graph(int, int);
	void acceptGraph();
	int Prims(int);
	int Kruskal();
	void display();
};

Graph::Graph() {
	vertex = 1;
	edges = 0;
	adj_mat = new int* [vertex];
	init(adj_mat, vertex);
}

Graph::Graph(int v, int e) {
	vertex = v;
	edges = e;
	adj_mat = new int* [vertex];
	init(adj_mat, vertex);
}

void Graph::acceptGraph() {
	int src, dest, weight;
	for (int i = 0; i < edges; i++) {
		cout << "Enter the source: ";  cin >> src;
		cout << "Enter the destination: "; cin >> dest;
		cout << "Enter weight of the edge: "; cin >> weight;
		adj_mat[src-1][dest-1] = adj_mat[dest-1][src-1] = weight;
	}
}

int Graph::Prims(int v) {
	int** spanning_tree = new int* [vertex];
	int** temp_mat = assign(adj_mat, vertex);
	init(spanning_tree, vertex);
	int count = 0;
	int visited = 0;
	int weight = 0;
	int t1, t2, v2, temp1, temp2, root_temp1, root_temp2, min; 
	int* reached = new int[vertex];
	int* father = new int[vertex];

	for (int i = 0; i < vertex; i++)
		reached[i] = 0;
	reached[visited++] = v;

	for (int i = 0; i < vertex; i++)
		father[i] = -1;
		 
	while (count < vertex-1) // main loop
	{
		min = INT32_MAX;
		for (int v1 = 0; v1 < visited; v1++) {
			for (v2 = 0; v2 < vertex; v2++) {
				if ((temp_mat[reached[v1]][v2]!=0) && (temp_mat[reached[v1]][v2] < min)) {
					min = temp_mat[reached[v1]][v2];
					t1 = reached[v1]; t2 = v2;
				}
			}
		}
		temp1 = t1; 
		temp2 = t2;
		temp_mat[temp1][temp2] = temp_mat[temp2][temp1] = 0; // so that it is marked as visited
		
		while (t1 >= 0) {
			root_temp1 = t1;
			t1 = father[t1];
		}

		while (t2 >= 0) {
			root_temp2 = t2;
			t2 = father[t2];
		}

		if (root_temp1 != root_temp2) {
			spanning_tree[temp1][temp2] = spanning_tree[temp2][temp1] = min;
			weight += min;
			father[root_temp2] = root_temp1;
			count++;
			reached[visited++] = temp2;
		}
	}
	cout << "\nThe minimum spanning tree is\n";
	print(spanning_tree, vertex);
	return weight;
}

int Graph::Kruskal() {
	int** spanning_tree = new int* [vertex];
	int** temp_mat = assign(adj_mat, vertex);
	init(spanning_tree, vertex);
	int count = 0;
	int weight = 0;
	int t1, t2, v2, temp1, temp2, root_temp1, root_temp2, min;
	int* father = new int[vertex];

	for (int i = 0; i < vertex; i++)
		father[i] = -1;

	while (count < vertex - 1) // main loop
	{
		min = INT32_MAX;
		for (int v1 = 0; v1 < vertex; v1++) {
			for (v2 = 0; v2 < vertex; v2++) {
				if ((temp_mat[v1][v2] != 0) && (temp_mat[v1][v2] < min)) {
					min = temp_mat[v1][v2];
					t1 = v1; t2 = v2;
				}
			}
		}
		temp1 = t1;
		temp2 = t2;
		temp_mat[temp1][temp2] = temp_mat[temp2][temp1] = 0; // so that it is marked as visited

		while (t1 >= 0) {
			root_temp1 = t1;
			t1 = father[t1];
		}

		while (t2 >= 0) {
			root_temp2 = t2;
			t2 = father[t2];
		}

		if (root_temp1 != root_temp2) {
			spanning_tree[temp1][temp2] = spanning_tree[temp2][temp1] = min;
			weight += min;
			father[root_temp2] = root_temp1;
			count++;
		}
	}
	cout << "\nThe minimum spanning tree is\n";
	print(spanning_tree, vertex);
	return weight;
}

void Graph::display() {
	cout << endl;
	for (int i = 0; i < vertex; i++) {
		cout << "    ";
		for (int j = 0; j < vertex; j++) {
			cout << adj_mat[i][j] << "  ";
		}
		cout << endl;
	}
}

void init(int** arr, int size) {
	for (int i = 0; i < size; i++) {
		arr[i] = new int[size];
		for (int j = 0; j < size; j++) {
			arr[i][j] = 0;
		}
	}
}

int** assign(int** arr, int size) {
	int** curr = new int* [size];
	for (int i = 0; i < size; i++) {
		curr[i] = new int[size];
		for (int j = 0; j < size; j++) {
			curr[i][j] = arr[i][j];
		}
	}
	return curr;
}

void print(int** arr, int n) {
	for (int i = 0; i < n; i++) {
		cout << "    ";
		for (int j = 0; j < n; j++) {
			cout << arr[i][j] << "  ";
		}
		cout << endl;
	}
}


int main() {

	int n, V, E, k;
	cout << "Enter the number of vertices and edges in Graph" << endl;
	cout << "Enter vertices: "; 
	cin >> V;
	cout << "Enter edges: ";
	cin >> E;
	Graph G(V, E);
	do
	{
		cout << "\nMenu\n\t1.Accept Graph\n\t2.Prims\n\t3.Kruskal\n\t4.Exit\n";
		cout << "\n\tSelect option: "; 
		cin >> n;

		switch (n)
		{
		case 1:
			G.acceptGraph();
			G.display();
			break;
		case 2:
			cout << "\nEnter the vertex to start with: ";
			cin >> k;
			cout << "The weight of graph is: " << G.Prims(k) << endl;
			break;
		case 3:
			cout << "The weight of graph is: " << G.Kruskal() << endl;
			break;
		default:
			break;
		}
	} while (n != 4);

	return 0;
}