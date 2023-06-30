// X20680

#include <iostream>
#include <vector>
using namespace std;

vector<char> xyz = {'x', 'y', 'z'};
int numw;

void write(vector<char> &let) {
    cout << numw << ": ";
    ++numw;
    for (int i = 0; i < let.size(); ++i) cout << let[i];
    cout << endl;
}

void words(int n, int nmax, int c, vector<char> &let, int equ) {
    if (n == nmax) write(let);

    else {
        for (int i = 0; i < 3; ++i) {
            if (nmax > 0 and let[nmax-1] == xyz[i]) ++equ;
            else equ = 0;
            
            if (equ < c) {
                let.push_back(xyz[i]);
                words(n, nmax + 1, c, let, equ);
                let.pop_back();
            }
        }
    }
}

int main() {
    int n, c;
    while (cin >> n >> c) {
        numw = 1;
        vector<char> let;
        words(n, 0, c, let, 0);
        cout << "--------------------" << endl;
    }
}



/*void words(int n, int nmax, int c, vector<int> used, vector<char> let) {
    if (n == nmax) write(let);

    else {
        if (used[0] < c) {
            let.push_back('x');
            ++used[0];
            words(n, ++nmax, c, used, let);
            --used[0];
        }

        if (used[1] < c) {
            let.push_back('y');
            ++used[1];
            words(n, ++nmax, c, used, let);
            --used[1];
        }

        if (used[2] < c) {
            let.push_back('z');
            ++used[2];
            words(n, ++nmax, c, used, let);
            --used[2];
        }
    }
}*/
