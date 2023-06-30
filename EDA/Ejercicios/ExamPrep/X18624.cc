#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<char> vow = {'a', 'e', 'i', 'o', 'u'};

void write(vector<char>& respart) {
    for (int i = 0; i < respart.size(); ++i) cout << respart[i];
    cout << endl;
}

bool isvowel(char c) {
    for(int j = 0; j < 5; ++j) {
        if (c == vow[j]) return true;
    }
    return false;
}

void Ruins(string& letters, vector<char>& respart, int n, int m, int nact) {
    if (nact == n) write(respart);

    else {
        for (int i = 0; i < m; ++i) {    
            if (!isvowel(letters[i]) or nact == 0 or !isvowel(respart[nact-1])) {
                respart[nact] = letters[i];
                Ruins(letters, respart, n, m, nact+1);
            }
        }
    }
}


int main() {
    int n, m;
    while (cin >> n >> m) {
        string letters;
        cin >> letters;
        sort(letters.begin(), letters.end());
        vector<char> respart(n);
        Ruins(letters, respart, n, m, 0);
        cout << "----------" << endl;
    }
}