#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> Sec;

void write(Sec& partsol) {
    cout << "(";
    for (int i = 0; i < partsol.size(); ++i) {
        if (i != partsol.size()-1) cout << partsol[i] << ",";
        else cout << partsol[i] << ")" << endl;
    }
}

void wells(Sec& partsol, vector<bool>& used, int n, int k) {
    if (partsol.size() == n) write(partsol);

    else {
        for (int i = 1; i < n+1; ++i) {
            if (!used[i] and (partsol.size() <= 1 or !(partsol[partsol.size()-2] + i > partsol.back()*2))) {    
                partsol.push_back(i);
                used[i] = true;
                wells(partsol, used, n, k+1);
                used[i] = false;
                partsol.pop_back();
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    Sec partsol;
    vector<bool> used(n+1, false);
    wells(partsol, used, n, 1);
}