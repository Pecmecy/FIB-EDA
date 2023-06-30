#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

typedef vector<int> Vec;
typedef vector<Vec> Mat;
int INF = numeric_limits<int>::max();       // Exam correction: infinite.

int sminmax(Mat& G, vector<bool>& Vis, int vert) {
    int leng = 1;
    Vis[vert] = true;
    for (int u : G[vert]) {
        if (!Vis[u]) leng = leng + sminmax(G, Vis, u);
    }
    return leng;
}

pair<int, int> sminmax(Mat& G) {
    pair<int, int> minmax;
    int n = G.size();
    vector<bool> Vis(n, false);
    minmax.first = INF;     //Minimum
    minmax.second = 0;      //Maximum
    for (int i = 0; i < n; ++i) {
        if (!Vis[i]) {
            int comp = sminmax(G, Vis, i);
            if (comp < minmax.first) minmax.first = comp;
            if (comp > minmax.second) minmax.second = comp;
        }
    }
    return minmax;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        Mat G(n);
        int x, y;
        for (int i = 0; i < m; ++i) {
            cin >> x >> y;
            G[x].push_back(y);
            G[y].push_back(x);
        }
        pair<int, int> minmax = sminmax(G);
        cout << minmax.first << " " << minmax.second << endl;
        // for (int v : G[0]) cout << v << endl;
    }
}