// X83283
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<int> Vec;
typedef vector<Vec> Mat;

int BFS(Mat& G) {
    int n = G.size();
    vector<int> dist(n, -1);
    dist[0] = 0;
    queue<int> Q;
    Q.push(0);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int v : G[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                Q.push(v);
            }
        }
    }

    int maxdist = 0;
    for (int i = 0; i < n; ++i) {
        //cout << "la distancia de " << i << " es: " << dist[i] << endl;
        if (dist[i] != -1 and dist[i] > dist[maxdist]) maxdist = i;
    }
    return maxdist;
}


int main() {
    int n, m;
    while (cin >> n >> m) {
        Mat G(n);
        for (int i = 0; i < m; ++i) {
            int x, y;
            cin >> x >> y;
            G[x].push_back(y);
            G[y].push_back(x);
        }
        cout << BFS(G) << endl;
    }
}