#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> ArcW;
typedef vector<vector<ArcW>> GraphW;

// Global variables
const int INF = 1e9;
int n; // Number of vertex. 
int m; // Number of arcs.
int org; // Origen vertex.
int dest; // Destination vertex.
GraphW G; // Graph.
vector<int> D; // Vector of distances.
int counter;

void dijkstra() {
    D = vector<int>(n, INF);    // Initialize distance vector.
    D[org] = 0;                 // Distance 0 at origen.
    priority_queue<ArcW> Q;
    Q.push(ArcW(0, org));

    while(!Q.empty()) {
        int p = -Q.top().first; // Path weight.
        int v = Q.top().second; // Vertex. 
        //cout << counter << "| distancia vértice: " << p << " vértice: " << v << endl;
        ++counter;
        Q.pop();

        if (p == D[v]) {
            if (v == dest) return;  // Dest found.
            for (int i = 0; i < G[v].size(); ++i) {
                int adj = G[v][i].first;
                int pes = G[v][i].second;
                if (p + pes < D[adj]) {
                    D[adj] = p + pes;
                    Q.push(ArcW(-D[adj], adj));
                }
            }
        }
    }
}

int main() {
    while(cin >> n >> m) {
        counter = 0;
        G = GraphW(n);
        for (int i = 0; i < m; ++i) {   // Number of elements to treat = number of arcs (m).
            int u, v, c;
            cin >> u >> v >> c;
            G[u].push_back(ArcW(v, c));
        }
        cin >> org >> dest;
        dijkstra();

        if (D[dest] < INF) cout << D[dest] << endl;
        else cout << "no path from " << org << " to " << dest << endl;
        //cout << "-----------------------------------------------------" << endl;
    }
}
