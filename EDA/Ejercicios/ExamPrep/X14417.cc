//X14417
#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

typedef vector<string> Bline;
typedef vector<Bline> Board;
typedef vector<pair<int,int>> Pos;
vector<pair<int,int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};

bool ok(Board& B, int i, int j) {
    return i >= 0 and j >= 0 and i < B.size() and j < B[0].size() and B[i][j] != "*";
}

int bfs(Board& B, pair<int,int> org, pair<int,int> dest) {
    int n = B.size();
    int m = B[0].size();
    vector<vector<int>> dist(n, vector<int>(m, -1));    //Matriz de distancias, inicializada a -1 en todas sus posiciones.
    queue<pair<int,int>> Q;                             //Queue de coordenadas de la matriz.
    Q.push(org);
    dist[org.first][org.second] = 0;

    while (!Q.empty()) {
        pair<int,int> u = Q.front();
        Q.pop();
        if (u == dest) return dist[u.first][u.second];

        for (pair<int,int> d : dirs) {
            pair<int,int> v = u;
            v.first += d.first;
            v.second += d.second;
            if (ok(B, v.first, v.second) and dist[v.first][v.second] == -1) {
                Q.push(v);
                dist[v.first][v.second] = dist[u.first][u.second] + 1;
            }
        }
    } 
    return -1;
}

pair<int,int> findpos(string& word, Board& B) {
    pair<int,int> wordpos;
    for (int i = 0; i < B.size(); ++i) {
        for (int j = 0; j < B[0].size(); ++j) {
            if (word == B[i][j]) {
                wordpos.first = i;
                wordpos.second = j;
                return wordpos;
            } 
        }
    }
    return {-1,-1};
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        Board B(n, Bline(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) cin >> B[i][j];
        }

        int p;
        cin >> p;
        Bline words(p);
        for (int i = 0; i < p; ++i) cin >> words[i];

        Pos pos(p+1);
        pos[0].first = pos[0].second = 0;

        for (int i = 0; i < p; ++i) {
            pair<int,int> posstring = findpos(words[i], B);
            pos[i+1].first = posstring.first;
            pos[i+1].second = posstring.second;
        }

        int distotal = 0;
        bool ok = true;
        for (int i = 0; ok and i < pos.size()-1; ++i) {
            int d = bfs(B, pos[i], pos[i+1]);
            if (d == -1) ok = false;
            else distotal += d;
        }

        if (!ok) cout << "impossible" << endl;
        else {
            cout << distotal + p << endl;
        }
    }
}