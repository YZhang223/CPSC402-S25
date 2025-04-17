#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Vertex {
    int num; // DFS number
    int low; // Low point
    bool visited; // Visited flag
    int parent; // Parent in DFS tree
    vector<int> adj; // Adjacency list
};

class Graph {
public:
  
    Graph(int n) : vertices(n) {}
    void addEdge(int u, int v) {
        vertices[u].adj.push_back(v);
        vertices[v].adj.push_back(u);
    }
    void findArtPoints() {
        counter = 0;

	//initialize the values
        for (int i = 0; i < vertices.size(); i++) {
            vertices[i].num = -1;
            vertices[i].visited = false;
            vertices[i].parent = -1;
        }

	for (int i = 0; i < vertices.size(); i++) {
            if (!vertices[i].visited) {
	      //first compute the DFS number
	      assignNum(i);

	      //then compute the low value
	      assignLow(i);
            }
        }
    }
private:
    void assignNum(int v) {

      //standard DFS algorithm
      vertices[v].num = counter++;
      vertices[v].visited = true;
      for (int i = 0; i < vertices[v].adj.size(); i++) {
	int w = vertices[v].adj[i];
	if (!vertices[w].visited) {
	  vertices[w].parent = v;
	  assignNum(w);
	}
      }
    }

  
  void assignLow(int v) {
    vertices[v].low = vertices[v].num; //rule 1
    
    for (int i = 0; i < vertices[v].adj.size(); i++) {
      int w = vertices[v].adj[i];

      //{v, w} is a forward edge
      if (vertices[w].num > vertices[v].num) 
	{
	  //find low(w) first
	  assignLow(w);

	  //if w is not the root and low(w) >= num(v),
	  //then v is an articulation point
	  if (vertices[w].low >= vertices[v].num && vertices[v].parent != -1) {
	    cout << v << " is an articulation point" << endl;
	  }

	  //compute low(v)
	  vertices[v].low = min(vertices[v].low, vertices[w].low); //rule 3
	}

      //{v, w} is a back edge
      else if (vertices[w].num < vertices[v].num && w != vertices[v].parent) {
	//rule 2
	vertices[v].low = min(vertices[v].low, vertices[w].num);
      }
    }
  }
  
  vector<Vertex> vertices;
  int counter;
};

int main() {
  //input file name
  string name;
  cout << "Enter the file name: ";
  cin >> name;

  //read graph into adjacency list
  ifstream infile(name);
  int n, m;
  infile >> n >> m;
  Graph g(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    infile >> u >> v;
    g.addEdge(u, v);
  }

  //find articulation points
  g.findArtPoints();
  
  return 0;
}
