#include <iostream>
#include <vector>
using namespace std;


void write(vector<int>& partsol) {
    cout << "(";
    for (int i = 0; i < partsol.size()-1; ++i) cout << partsol[i] << ",";
    cout << partsol.back() << ")" << endl; 
}

bool balanced(int x, int y, int d) {
    //cout << x << " " << y << endl;
    return abs(x-y) <= d;
}

void balanced_seq(vector<int>& partsol, vector<bool>& used, int n, int d) {
    if (partsol.size() == n) write(partsol);

    else {
        for (int i = 1; i <= n; ++i) {
            //cout << "for i = " << i << ": ";
            if (!used[i] and (partsol.size() == 0 or balanced(partsol.back(), i, d))) {
                used[i] = true;
                partsol.push_back(i);
                balanced_seq(partsol, used, n, d);
                used[i] = false;
                partsol.pop_back();
            }
        }
    }
}

int main() {
    int n, d;
    cin >> n >> d;
    vector<int> partsol;
    vector<bool> used(n+1, false);
    balanced_seq(partsol, used, n, d);
}