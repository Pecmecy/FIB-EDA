//X57029
#include <iostream>
#include <vector>
using namespace std;

vector<pair<int,char>> dir = {{-1,'d'}, {0,'h'}, {1,'u'}};

void write(vector<char>& movs, int n) {
    for (int i = 0; i < n; ++i) cout << movs[i];
    cout << endl;
}

void pathing(vector<char>& movs, pair<int,int>& pos, int n) {
    if (pos.first == n) write(movs, n);

    else {
        for (int i = 0; i < 3; ++i) {
            if (pos.second + dir[i].first >= 0) {
                movs.push_back(dir[i].second);
                ++pos.first;
                pos.second += dir[i].first;
                pathing(movs, pos, n);
                --pos.first;
                pos.second -= dir[i].first;
                movs.pop_back();
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    vector<char> movs;
    pair<int,int> pos;
    pos.first = pos.second = 0;     //.first = horizontal, .second = vertical
    pathing(movs, pos, n);
}