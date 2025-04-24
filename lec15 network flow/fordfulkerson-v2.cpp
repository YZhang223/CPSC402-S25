#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9; // Infinity

struct Edge {
    int u;
    int v;
    int w;
};

// Ford-Fulkerson Algorithm (Edmonds-Karp BFS version)
int fordFulkerson(vector<vector<int>>& adjList, vector<Edge>& edges, int source, int sink, vector<vector<int>>& flow) {
    int n = adjList.size();
    vector<vector<int>> capacity(n, vector<int>(n, 0));
    flow.assign(n, vector<int>(n, 0));

    for (auto& e : edges) {
        capacity[e.u][e.v] += e.w;
    }

    int maxFlow = 0;

    while (true) {
        vector<int> parent(n, -1);
        queue<int> q;
        q.push(source);
        parent[source] = source;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adjList[u]) {
                if (parent[v] == -1 && capacity[u][v] > 0) {
                    parent[v] = u;
                    q.push(v);
                }
            }
        }

        if (parent[sink] == -1) break;

        int pathFlow = INF;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, capacity[u][v]);
        }

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            capacity[u][v] -= pathFlow;
            capacity[v][u] += pathFlow;

            // Adjust the flow matrix to reflect actual flow
            if (flow[v][u] > 0) {
                int pushedBack = min(flow[v][u], pathFlow);
                flow[v][u] -= pushedBack;
                pathFlow -= pushedBack;
            }
            if (pathFlow > 0) {
                flow[u][v] += pathFlow;
            }
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main() {
    string name;
    cout << "Enter file name: ";
    cin >> name;

    ifstream inputFile(name);
    if (!inputFile) {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }

    int n, m, s, t;
    inputFile >> n >> m >> s >> t;
    vector<vector<int>> adjList(n);
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        inputFile >> u >> v >> w;
        edges[i] = {u, v, w};
        adjList[u].push_back(v);
        adjList[v].push_back(u); // For residual graph
    }
    inputFile.close();

    vector<vector<int>> flow;
    int maxFlow = fordFulkerson(adjList, edges, s, t, flow);
    cout << "Maximum Flow: " << maxFlow << endl;

    cout << "Flow Graph (u -> v : flow):" << endl;
    for (auto& e : edges) {
        if (flow[e.u][e.v] > 0) {
            cout << e.u << " -> " << e.v << " : " << flow[e.u][e.v] << endl;
        }
    }

    return 0;
}
