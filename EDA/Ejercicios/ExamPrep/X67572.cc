//X67572
#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef vector<string> Words;

void write(Words& W, vector<int>& partsol, int n) {
    for (int i = 0; i < n; ++i) {
        cout << W[partsol[i]];
    }
    cout << endl;
}

void concatenated(Words& W, vector<int>& partsol, vector<bool>& used, int n) {
    if (partsol.size() == n) write(W, partsol, n);

    else {
        for (int i = 0; i < n; ++i) {
            if (!used[i] and (partsol.size() == 0 or W[partsol.back()].back() != W[i][0])) {
                used[i] = true;
                partsol.push_back(i);
                concatenated(W, partsol, used, n);
                partsol.pop_back();
                used[i] = false;
            }
        }  
    }
}

int main() {
    int n;
    cin >> n;
    Words W(n);
    for (int i = 0; i < n; ++i) cin >> W[i];

    vector<int> partsol;
    vector<bool> used(n, false);
    concatenated(W, partsol, used, n);
}