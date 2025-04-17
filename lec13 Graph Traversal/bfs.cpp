#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

void bfs(int u, vector<bool>& visited, vector<vector<int>>& adj_list) {

  queue<int> q;
  
  q.push(u);
  visited[u] = true;

  while (!q.empty()) {
    int v = q.front();
    q.pop();
    cout << v << " ";

    //for each neighbour w of v
    //if w is not visited, mark w as visited,
    //then add w to the queue
    for (int w : adj_list[v]) {
      if (!visited[w]) {
	visited[w] = true;
	q.push(w);
      }
    }
  }
}

int main() {
  //read in file name
  string name;
  cout << "Enter the file name: ";
  cin >> name;

  //read the graph into adjacency list
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


  cout << "BFS traversal: ";
  //start bfs from vertex 1
  bfs(1, visited, adj_list);
  cout << endl;


  return 0;
}
