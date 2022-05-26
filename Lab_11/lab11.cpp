// Author: TheBeerex
// Lab_11 ~~ Prims MST

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, int> intPair; // Every vertex has an associated weight to it

class Graph {
    private:
        int V; // # of vertices
        vector<intPair>* adj; // intPair vector array

    public:
        Graph(int V) {
            this->V = V;
            adj = new vector<intPair> [V];
        }

        void addEdge(int u, int v, int W) {
            adj[u].push_back(make_pair(v, W)); // put v in u's list
            adj[v].push_back(make_pair(u, W)); // put u in v's list
        }

        // Implementation of Prim's MST algorithm
        void primMST() {
            /*
            Initialize a min-priority queue Q.
            for all u ∈ V do
                u.key = ∞.
                u.π = NIL.
                Insert (Q, u).
            Decrease-key(Q, r, 0).
            while Q 6= ∅ do
                u = Extract-Min(Q).
                for all v ∈ Adj[u] do
                    if v ∈ Q and w(u, v) < v.key then
                        v.π = u.
                        Decrease-Key(Q, v, w(u, v)).
            */

            // Create min-priority queue to store vertices that are MST
            priority_queue< intPair, vector <intPair> , greater<intPair> > pq;

            // Create a vector for keys and initialize all keys as infinite (INT_MAX)
            vector<int> key(V, INT_MAX);

            // To store parent array which in turn store MST
            vector<int> parent(V, -1);

            // To keep track of vertices included in MST
            vector<bool> inMST(V, false);

            int src = 0; // Taking vertex 0 as source
            // Insert source itself in priority queue and initialize its key as 0.
            pq.push(make_pair(0, src));
            key[src] = 0;

            // Looping until priority queue is empty
            while (!pq.empty()) {
                // The first vertex in pair is the minimum key
                // vertex, extract it from priority queue.
                // vertex label is stored in second of pair (it
                // has to be done this way to keep the vertices
                // sorted key (key must be first item
                // in pair)
                int u = pq.top().second;
                pq.pop();

                //Different key values for same vertex may exist in the priority queue.
                //The one with the least key value is always processed first.
                //Therefore, ignore the rest.
                if(inMST[u] == true){
                    continue;
                }

                inMST[u] = true; // Include vertex in MST

                // Traverse all adjacent of u
                for (auto x : adj[u]) {
                    // Get vertex label and weight of current adjacent
                    // of u.
                    int v = x.first;
                    int weight = x.second;
        
                    // If v is not in MST and weight of (u,v) is smaller
                    // than current key of v
                    if (inMST[v] == false && key[v] > weight) {
                        // Updating key of v
                        key[v] = weight;
                        pq.push(make_pair(key[v], v));
                        parent[v] = u;
                    }
                }
            }

            // Prints MST
            for (int i = 1; i < V; i++) {
                cout << parent[i] << endl;
            }            
        }
};


int main() {
	int vertices, edges, tempX, tempY, tempW;
    cin >> vertices;
    cin >> edges;

    Graph g(vertices);

    for (int i = 0; i < edges; i++) {
        cin >> tempX >> tempY >> tempW; // TIL you can do this
        g.addEdge(tempX, tempY, tempW);
    }

    g.primMST();

    return 0;
}
