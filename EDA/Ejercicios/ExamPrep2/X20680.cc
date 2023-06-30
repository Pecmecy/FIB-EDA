#include <iostream>
#include <vector>
using namespace std;


void write(vector<char>& p) {
    for (auto c : p) cout << c;
    cout << endl;
}

void consec(vector<char>& partsol, int n, int c, int x, int y, int z) {
    if (partsol.size() == n) write(partsol);

    else {
        if (x + 1 <= c) {
            partsol.push_back('x');
            consec(partsol, n, c, x+1, 0, 0);
            partsol.pop_back();
        }

        if (y + 1 <= c) {
            partsol.push_back('y');
            consec(partsol, n, c, 0, y+1, 0);
            partsol.pop_back();
        }

        if (z + 1 <= c) {
            partsol.push_back('z');
            consec(partsol, n, c, 0, 0, z+1);
            partsol.pop_back();
        }
    }
}

int main() {
    int n, c;
    while (cin >> n >> c) {
        vector<char> partsol;
        consec(partsol, n, c, 0, 0, 0);
        cout << "--------------------" << endl;
    }
}