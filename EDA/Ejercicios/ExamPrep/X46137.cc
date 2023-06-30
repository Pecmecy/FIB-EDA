//X46137
#include <iostream>
#include <vector>
using namespace std;

vector<char> ab = {'a','b'};

void write(vector<char>& W, int n) {
    for (int i = 0; i < n; ++i) cout << W[i];
    cout << endl;
}

bool prefix(int a, int b, int i) {
    if (i == 0) ++a;
    else ++b;
    return abs(a - b) <= 2;
}

void compensated(vector<char>& W, vector<int>& abnum, int n) {
    if (W.size() == n) write(W, n);

    else {
        for (int i = 0; i < 2; ++i) {
            if (prefix(abnum[0], abnum[1], i)) {
                ++abnum[i];
                W.push_back(ab[i]);
                compensated(W, abnum, n);
                --abnum[i];
                W.pop_back();
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    vector<char> word;
    vector<int> abnum(2, 0);
    compensated(word, abnum, n);
}