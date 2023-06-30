#include <iostream>
#include <vector>
using namespace std;

typedef vector<char> Vchar;
typedef vector<Vchar> Board;
vector<pair<int,int>> movs = {{-1,0}, {-1,-1}, {0,-1}, {1,-1}, {0,1}, {1,1}, {1,0}, {-1,1}}; 

bool ok(int n, int i, int j) {
    return i >= 0 and j >= 0 and i < n and j < n;
}

void updatesafe(vector<vector<bool>>& safe, int i, int j) {
    int n = safe.size();
    for (int l = 0; l < n; ++l) {
        if (ok(n, i+movs[l].first, j+movs[l].second)) safe[i+movs[l].first][j+movs[l].second] = false;
    }
}

void kings(Board& B, vector<vector<bool>>& safe, int k, int kpart) {
    if (kpart == k) write();

    else {
        for (int i = 0; i < B.size(); ++i) {
            for (int j = 0; j < B.size(); ++j) {
                if (safe[i][j]) {
                    B[i][j] = 'K';
                    safe[i][j] = false;
                    updatesafe(safe, i, j);
                }
            }
        }
    }
}

int main() {
    int n, k;
    cin >> n >> k;
    Board(n, Vchar(n, '.'));
    vector<vector<bool>> safe(n, vector<bool>(n, true));
    kings(B, safe, k, 0);
}