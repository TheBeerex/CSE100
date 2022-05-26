// Author: TheBeerex
// Lab_10 ~~ SCCs

#include <iostream>
#include <list>
#include <stack>
#include <vector>

using namespace std;

class Graph {

	private:
		int V; // No. of vertices
		list<int> *adj; // An array of adjacency lists

		// Fills Stack with vertices (in increasing order of DFS finishing times)
		// The top element of Stack has the maximum finishing time
		void fillOrder(int v, bool visited[], stack<int> &Stack) {
			visited[v] = true; // Mark the current node as visited

			// Visit all vertices adjacent to v
			list<int>::iterator it;
			for (it = adj[v].begin(); it != adj[v].end(); ++it) {
				if (!visited[*it]) {
					fillOrder(*it, visited, Stack);
				}
			}

			// All vertices reachable from v are processed by now, push v
			Stack.push(v);
		}

		// Finds the SCCs of the graph using DFS
		void findSSCs(int root, int v, bool visited[], list<int>* SCCs){
			// Mark the v as visited and save it to the SCCs[root] list
			visited[v] = true;
			SCCs[root].push_back(v);

			// Visit all vertices adjacent to v
			list<int>::iterator it;
			for (it = adj[v].begin(); it != adj[v].end(); it++) {
				if (!visited[*it]) {
					findSSCs(root, *it, visited, SCCs);
				}
			}
		}

	public:
		Graph (int V) {
			this->V = V;
			adj = new list<int>[V];
		}

		~Graph() {
			delete[] adj;
		}

		void addEdge (int v, int w) {
			adj[v].push_back(w); // Add w to v’s list.
		}

		// Returns transpose of the graph
		Graph getTranspose() {
			Graph g(V);
			for (int v = 0; v < V; v++) {
				// Recur for all the vertices adjacent to this vertex
				list<int>::iterator it;
				for (it = adj[v].begin(); it != adj[v].end(); it++) {
					g.adj[*it].push_back(v);
				}
			}
			return g;
		}

		// The main function that finds and prints strongly connected components
		void printSCCs() {
			stack<int> Stack;

			// Mark all the vertices as not visited (For first DFS)
			bool *visited = new bool[V];
			for (int i = 0; i < V; i++) {
				visited[i] = false;
			}

			// Fill vertices in stack according to their finishing times
			for (int i = 0; i < V; i++) {
				if (visited[i] == false) {
					fillOrder(i, visited, Stack);
				}
			}

			Graph gr = getTranspose();

			// Mark all the vertices as not visited (For second DFS)
			for (int i = 0; i < V; i++) {
				visited[i] = false;
			}

			list<int>* SCCs = new list<int>[this->V];
			// Procress vertices in order of the Stack to find SCCs
			while (Stack.empty() == false) {
				// Pop a vertex from stack
				int v = Stack.top();
				Stack.pop();

				// Find SCCs of the popped vertex
				if (visited[v] == false) {
					gr.findSSCs(v, v, visited, SCCs);
				}
			}

			int* IDs = new int[this->V];
			// Create ID list
			for (int i = 0; i < V; i++) {
				if (!SCCs[i].empty()) {
					// Find minimum vertice of list
					auto min = SCCs[i].begin();
					for (auto it = SCCs[i].begin(); it != SCCs[i].end(); it++) {
						if (*min > *it) {
							min = it;
						}
					}
					// And place it at the front
					swap(*min, *SCCs[i].begin());
					// Then add elements to IDs
					for (auto it = SCCs[i].begin(); it != SCCs[i].end(); it++) {
						IDs[*it] = *SCCs[i].begin();
					}
				}
			}

			// Print IDs
			for (int i = 0; i < V; i++) {
				cout << IDs[i] << endl;
			}

			delete[] IDs;
			delete[] SCCs;
		}
};


int main() {
	int vertices, edges, temp1, temp2;
    cin >> vertices;

    Graph g(vertices);
    cin >> edges;

    for (int i = 0; i < edges; i++) {
        cin >> temp1;
        cin >> temp2;
        g.addEdge(temp1, temp2);
    }

    g.printSCCs();

    return 0;
}
