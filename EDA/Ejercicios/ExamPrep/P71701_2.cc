#include <iostream>
#include <vector>
using namespace std;

typedef vector<bool> Vec;
typedef vector<Vec> Tab;

int n, k;
int movi[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int movj[8] = {0, -1, -1, -1, 0, 1, 1, 1};

void write(Tab& t) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (t[i][j]) cout << "K";
            else cout << ".";
        }
        cout << endl;
    }
    cout << "----------" << endl;
}

void nextmove(int i, int j, int& ni, int& nj) {
    if (j < n-1) {
        ni = i;
        nj = j+1;
    } 

    else {
        ni = i+1;
        nj = 0;
    }
}

bool safemove(int x, int y) {
    return 0 <= x and x < n and 0 <= y and y < n;
}

bool moveking(int i, int j, Tab& t) {
    for (int l = 0; l < 8; ++l) {
        int ip = i + movi[l];
        int jp = j + movj[l];
        if (safemove(ip, jp) and t[ip][jp]) return false;
    }
    return true;
}

void nkings(int i, int j, Tab& t, int s) {
    if(s == k) write(t);

    else if(i != n) {
        int ni, nj;
        nextmove(i, j, ni, nj);

        if (moveking(i, j, t)) {
            t[i][j] = true;
            nkings(ni, nj, t, s+1);
        }
        t[i][j] = false;
        nkings(ni, nj, t, s);
    }
}

int main() {
    cin >> n >> k;
    Tab t(n, Vec(n, false));
    nkings(0, 0, t, 0);
}
