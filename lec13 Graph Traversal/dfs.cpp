#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void dfs(int u, vector<bool>& visited, vector<vector<int>>& adj_list) {


  visited[u] = true;
  cout << u << " ";

  for (int v : adj_list[u]) {
    if (!visited[v]) {
      dfs(v, visited, adj_list);
    }
  }
}

int main() {

  //read in the file name
  string name;
  cout << "Enter the file name: ";
  cin >> name;

  //read the graph into the adjacency list
  int n, m;
  ifstream infile(name);
  infile >> n >> m;

  vector<vector<int>> adj_list(n+1);

  for (int i = 0; i < m; i++) {
    int u, v;
    infile >> u >> v;
    adj_list[u].push_back(v);
    adj_list[v].push_back(u); // since the graph is undirected
  }
  
  infile.close();

  //create the boolean array
  vector<bool> visited(n+1, false);

  cout << "DFS traversal: ";
  //start dfs from vertex 1
  dfs(1, visited, adj_list);
  cout << endl;
    
  return 0;
}
