#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

typedef vector<char> Vchar;
Vchar vowels = {'a','e','i','o','u'};

void write(Vchar& ps) {
    for (auto c : ps) cout << c;
    cout << endl;
}

bool isvowel(char c) {
    for (auto i : vowels) {
        if (c == i) return true;
    }

    return false;
}

void ruins(Vchar& l, Vchar& ps, bool antvow, int n, int k) {
    if (k == n) write(ps);

    else {
        for (int i = 0; i < l.size(); ++i) {    
            if (isvowel(l[i]) and (ps.size() == 0 or !antvow)) {
                ps[k] = l[i];
                ruins(l, ps, true, n, k+1);
            }

            if (!isvowel(l[i])) {
                ps[k] = l[i];
                ruins(l, ps, false, n, k+1);
            }
        }
    }
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        Vchar letters(m);
        for (int i = 0; i < m; ++i) cin >> letters[i];
        sort(letters.begin(), letters.end());

        Vchar partsol(n);
        ruins(letters, partsol, false, n, 0);
        cout << "----------" << endl;
    }
}