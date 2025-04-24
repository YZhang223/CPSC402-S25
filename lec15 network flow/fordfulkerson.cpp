#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9; // Infinity

// Struct to represent an edge in the graph
struct Edge {
  int u;
  int v;
  int w;
};


// Function to find the maximum flow in a network flow graph
int fordFulkerson(vector<vector<int>>& adjList, vector<Edge>& edges, int source, int sink) {
    int n = adjList.size();

    vector<vector<int>> capacity(n, vector<int>(n, 0)); // Initialize the capacity matrix
    for(auto e : edges) {
        capacity[e.u][e.v] += e.w; // Add the edge to the capacity matrix
    }
    
    int maxFlow = 0;


    //use BFS to find an augmenting path from source to sink
    
    while(true) {
      // Initialize parent array to -1 for all nodes
      vector<int> parent(n, -1);
      // Initialize queue with source node and set its parent to itself
      queue<int> q;
      parent[source] = source;
      q.push(source);
      // Start BFS
      while(!q.empty()) {
        // Get next node to visit from queue
        int u = q.front();
        q.pop();
        // Visit all neighbors of u
        for(int v : adjList[u]) {
	        // If v has not been visited yet and the residual capacity is positive
	        if(parent[v] == -1 && capacity[u][v] > 0) {
	        // Set parent of v to u
	        parent[v] = u;
	        // Add v to queue to be visited later
	        q.push(v);
	      }
      }
    }
      
    
    if(parent[sink] == -1) { // No path from source to sink
	    break;
    }

    // Update the residual capacities of the edges in the augmenting path
    int pathFlow = INF;
    for (int v = sink; v != source; v = parent[v]) {
	    int u = parent[v];
	    // Find the minimum residual capacity along the augmenting path
	    pathFlow = min(pathFlow, capacity[u][v]);
    }
      
    // Update the residual capacities of the edges in the augmenting path and the maximum flow
    for (int v = sink; v != source; v = parent[v]) {
	    int u = parent[v];
	    // Subtract the flow of the augmenting path from the residual capacity of the edge from u to v
	    capacity[u][v] -= pathFlow;
	    // Add the flow of the augmenting path to the residual capacity of the edge from v to u
	    capacity[v][u] += pathFlow;
    }
    // Add the flow of the augmenting path to the maximum flow
    maxFlow += pathFlow;
  }
  return maxFlow;
}

int main() {
  string name;
  cout << "Enter file name: ";
  cin >> name;
  
  ifstream inputFile(name);
    if(!inputFile) {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }
    int n, m, s, t;
    inputFile >> n >> m >> s >> t;
    vector<vector<int>> adjList(n);
    vector<Edge> edges(m);
    for(int i = 0; i < m; i++) {
        int u, v, w;
        inputFile >> u >> v >> w;
        edges[i] = {u, v, w};
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    inputFile.close();
    int maxFlow = fordFulkerson(adjList, edges, s, t);
    cout << "Maximum Flow: " << maxFlow << endl;
    return 0;
}
