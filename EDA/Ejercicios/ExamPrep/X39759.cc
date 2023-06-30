#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<pair<int, int>> Goals;
vector<pair<int,int>> movs = {{-2,-1}, {-1,-2}, {1,-2}, {2,-1}, {2,1}, {1,2}, {-1,2}, {-2,1}};

bool correct(int i, int j, int n, int m) {
    return i >= 0 and j >= 0 and i < n and j < m;
}

int bfs(pair<int,int>& org, pair<int,int>& dest, int n, int m) {
    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int,int>> Q;
    Q.push(org);
    dist[org.first][org.second] = 0;

    while(!Q.empty()) {
        pair<int,int> u = Q.front();
        Q.pop();
        if (u == dest) return dist[u.first][u.second];

        for (auto d : movs) {
            pair<int,int> v = u;
            v.first += d.first;
            v.second += d.second;

            if (correct(v.first, v.second, n, m) and dist[v.first][v.second] == -1) {
                Q.push(v);
                dist[v.first][v.second] = dist[u.first][u.second] + 1;
            }
        }
    }
    return -1;
}

int main() {
    int n, m, W, L, k;
    while (cin >> n >> m >> W >> L >> k) {
        Goals pos(k+1);
        pos[0].first = pos[0].second = 0;
        for (int i = 1; i <= k; ++i) cin >> pos[i].first >> pos[i].second;

        int points = 0;
        int finpoints = 0;
        bool ok = true;
        for (int i = 0; ok and i < pos.size() - 1; ++i) {
            int dist = bfs(pos[i], pos[i+1], n, m);
            if (dist == -1) ok = false;
            
            else {
                points += W;
                points -= dist*L;
                
                if (points > finpoints) finpoints = points;
            }
        }

        cout << finpoints << endl;
    }
}