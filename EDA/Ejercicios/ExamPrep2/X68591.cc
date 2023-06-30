#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

typedef vector<int> Vec;
typedef vector<Vec> Mat;
int INF = std::numeric_limits<int>::max();

int bfs(Mat& M, Vec& dist, int org) {
    int size = 1;
    queue<int> Q;
    Q.push(org);
    dist[org] = 0;

    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();

        for (auto v : M[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                ++size;
                Q.push(v);
            }
        }
    }
    return size;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        Mat M(n);
        for (int i = 0; i < m; ++i) {
            int x, y;
            cin >> x >> y;
            M[x].push_back(y);
            M[y].push_back(x);
        }

        int maxsize, minsize;
        maxsize = 0;
        minsize = INF;
        Vec dist(n, -1);
        for (int i = 0; i < n; ++i) {
            if (dist[i] == -1) {
                int size = bfs(M, dist, i);
                if (size > maxsize) maxsize = size;
                if (size < minsize) minsize = size;
            }
        }
        if (minsize == INF) minsize = 0;
        cout << minsize << " " << maxsize << endl;
    }
}