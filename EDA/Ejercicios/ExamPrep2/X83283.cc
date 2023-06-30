#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<int> Vec;
typedef vector<Vec> Mat;

int farthest(Mat& M) {
    int n = M.size();
    vector<int> dist(n, -1);
    queue<int> Q;
    Q.push(0);
    dist[0] = 0;

    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (auto v : M[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                Q.push(v);
            }
        }
    }
    int fdist = 0;
    int farthest = 0;
    for (int i = 0; i < dist.size(); ++i) {
        if (dist[i] > fdist) {
            farthest = i;
            fdist = dist[i];
        }
    }

    return farthest;
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

        cout << farthest(M) << endl;
    }
}