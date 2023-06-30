#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> Matrix;
typedef pair<int,int> Cord;
typedef vector<bool> vb;
typedef vector<vb> Board;

//Direccions de salt de cavall
const int NDIRS = 8;
Cord Dirs[8] = {make_pair(-2,-1),make_pair(-2,1),make_pair(-1,2),make_pair(1,2),make_pair(2,1),make_pair(2,-1),make_pair(1,-2),make_pair(-1,-2)};

//Check limits, and wether it was already visited
bool ok(Cord act, Cord inc, Board& b, Cord& newc) {
    int f = newc.first = act.first + inc.first;
    int c = newc.second = act.second + inc.second;
    if (f >= 0 and f < b.size() and c >= 0 and c < b[0].size() and b[f][c]) return true;
    return false;
}

int BFS(Board& b,Cord start, Cord goal,int w , int l) {
    queue<Cord> q;
    Matrix dist(b.size(),vi(b[0].size(),0));
    b[start.first][start.second] = false;
    q.push(Cord(start.first,start.second));
    while (not q.empty()) {
        Cord act = q.front();
        q.pop();
        if (act == goal) {
            return w - (l*dist[act.first][act.second]);
        }
        for (int i = 0; i < NDIRS; ++i) {
            Cord newc;
            if (ok(act,Dirs[i],b, newc)) {
                //Mark as seen
                b[newc.first][newc.second] = false;
                dist[newc.first][newc.second] = dist[act.first][act.second] + 1;
                q.push(newc);
            }
        }
    }
    return -1;
}



int main() {
    int n,m,w,l;
    while(cin >> n >> m >> w >> l) {
        int k;
        cin >> k;
        Cord goal,start;
        start = Cord(0,0);
        bool stop = false;
        int puntos = 0;
        for (int i = 0; i < k and not stop; ++i) {
            cin >> goal.first >> goal.second;
            Board b(n,vb(m,true));
            int bfs = BFS(b,start,goal,w,l);
            //If it is not possible to reach - or it does not benefit us (cost > benefit), dont make any moves to keep the score as high as possible
            if (bfs == -1) {
                stop = true;
            }
            else {
                puntos += bfs;
                start = goal;
            }
        }
        if (puntos < 0) puntos = 0;
        cout << puntos << endl;
    }
}