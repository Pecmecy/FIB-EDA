//X39187
#include <iostream>
#include <vector>
using namespace std;

void write(vector<char>& ops) {
    for (auto c : ops) cout << c;
    cout << endl;
}

void transaction(vector<char>& ops, int n, int c, int sh) {
    if (ops.size() == n) write(ops);

    else {
        if (c > 0) {
            ops.push_back('b');
            transaction(ops, n, c-1, sh+1);
            ops.pop_back();
        }

        if (sh > 0) {
            ops.push_back('s');
            transaction(ops, n, c+1, sh-1);
            ops.pop_back();
        }
    }
}

int main() {
    int n, c;
    cin >> n >> c;
    vector<char> ops;
    transaction(ops, n, c, 0);
}