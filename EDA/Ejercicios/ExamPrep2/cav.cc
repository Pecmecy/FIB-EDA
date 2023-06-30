#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
using namespace std;

typedef vector<vector<char>> Board;
typedef vector<char> Row;
typedef vector<vector<int>> Matrix;
struct Position {
    int i;
    int j;
};

list<Position> BFS(Board& b,Position inicial) {
    int n = b.size();
    int m = b[0].size();
    Position p;
    Matrix vist(n,vector<int>(m,0));
    list<Position> empt;
    empt.push_back(inicial);
    queue<list<Position>> q;
    q.push(empt);
    while(not q.empty()) {
        list<Position> actpath = q.front();
        Position act = *(actpath.rbegin());
        q.pop();
        //Found the farmer
        if (b[act.i][act.j] == 'F') {
            return actpath;
        }

        //abajo
        p.i = act.i + 1; p.j = act.j;
        if (p.i < n and p.j < m and p.i >= 0 and p.j >= 0 and b[p.i][p.j] != 'X' and vist[p.i][p.j] == 0) {
            vist[p.i][p.j] = 1;
            list<Position> newpath = actpath;
            newpath.push_back(p);
            q.push(newpath);
        }
        //arriba
        p.i = act.i - 1; p.j = act.j;
        if (p.i < n and p.j < m and p.i >= 0 and p.j >= 0 and b[p.i][p.j] != 'X' and vist[p.i][p.j] == 0) {
            vist[p.i][p.j] = 1;
            list<Position> newpath = actpath;
            newpath.push_back(p);
            q.push(newpath);        }
        //derecha
        p.i = act.i; p.j = act.j+1;
        if (p.i < n and p.j < m and p.i >= 0 and p.j >= 0 and b[p.i][p.j] != 'X' and vist[p.i][p.j] == 0) {
            vist[p.i][p.j] = 1;
            list<Position> newpath = actpath;
            newpath.push_back(p);
            q.push(newpath);        }
        //izquierda
        p.i = act.i; p.j = act.j-1;
        if (p.i < n and p.j < m and p.i >= 0 and p.j >= 0 and b[p.i][p.j] != 'X' and vist[p.i][p.j] == 0) {
            vist[p.i][p.j] =  1;
            list<Position> newpath = actpath;
            newpath.push_back(p);
            q.push(newpath);        }
        //abajo,derecha
        p.i = act.i + 1; p.j = act.j+1;
        if (p.i < n and p.j < m and p.i >= 0 and p.j >= 0 and b[p.i][p.j] != 'X' and vist[p.i][p.j] == 0) {
            vist[p.i][p.j] = 1;
            list<Position> newpath = actpath;
            newpath.push_back(p);
            q.push(newpath);        }
        //abajo,izquierda
        p.i = act.i + 1; p.j = act.j-1;
        if (p.i < n and p.j < m and p.i >= 0 and p.j >= 0 and b[p.i][p.j] != 'X' and vist[p.i][p.j] == 0) {
            vist[p.i][p.j] = 1;
            list<Position> newpath = actpath;
            newpath.push_back(p);
q.push(newpath);        }
        //arriba,derecha
        p.i = act.i - 1; p.j = act.j+1;
        if (p.i < n and p.j < m and p.i >= 0 and p.j >= 0 and b[p.i][p.j] != 'X' and vist[p.i][p.j] == 0) {
            vist[p.i][p.j] = 1;
            list<Position> newpath = actpath;
            newpath.push_back(p);
            q.push(newpath);        }
        //arriba,izquierda
        p.i = act.i - 1; p.j = act.j - 1;
        if (p.i < n and p.j < m and p.i >= 0 and p.j >= 0 and b[p.i][p.j] != 'X' and vist[p.i][p.j] == 0) {
            vist[p.i][p.j] = 1;
            list<Position> newpath = actpath;
            newpath.push_back(p);
            q.push(newpath);        }
    }
    empt.clear();
    return empt;
}

int main() {
    int n,m;
    while(cin >> n >> m) {
        Board b(n,Row(m));
        Position p;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> b[i][j];
                if (b[i][j] == 'K') {
                    p.i = i; p.j = j;
                }
            }
        }
        list<Position> L = BFS(b,p);
        cout << L.size();
        if (L.size() != 0) {
            cout << "  ";
            for (auto cam : L) {
                cout << cam.i << " " << cam.j;
                cout << "  ";
            }
        }
        cout << endl;
    }
}