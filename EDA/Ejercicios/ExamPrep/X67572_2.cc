#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef vector<string> Words;

void write(Words& words, vector<int>& partres) {
    for (int i = 0; i < partres.size(); ++i) cout << words[partres[i]];
    cout << endl;
}

void concatenated(Words& words, vector<int>& partres, vector<bool>& used, int n) {
    if (partres.size() == n) write(words, partres);

    else {
        for (int i = 0; i < n; ++i) {
            if (!used[i] and (partres.size() == 0 or words[partres.back()].back() != words[i][0])) {
                used[i] = true;
                partres.push_back(i);
                concatenated(words, partres, used, n);
                used[i] = false;
                partres.pop_back();
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    Words words(n);
    for (int i = 0; i < n; ++i) cin >> words[i];
    vector<int> partres;
    vector<bool> used(n);
    concatenated(words, partres, used, n);
}