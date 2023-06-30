#include <iostream>
#include <vector>
using namespace std;

vector<char> letters = {'x' , 'y' , 'z' };
int numw;

void writewords (int n, int c , vector<char>& partial_sol, int consec , int k) {
    if (k == n) {
        cout << numw << ": ";
        ++numw;
        for (char aux : partial_sol ) cout << aux;
        cout << endl;
    }

    else {
    for (int i = 0; i < 3; ++i) {
        bool repeated = (k > 0 and partial_sol [k-1] == letters [i]);
        int new_consec = ( repeated ? consec + 1 : 1);
        if (new_consec <= c) {
            partial_sol [k] = letters [i ];
            writewords(n, c , partial_sol ,new_consec,k+1); 
            }
        }
    }
}

int main () {
    int n, c ;
    while (cin >> n >> c) {
        numw = 1;
        vector<char> partial_sol(n);
        writewords(n,c , partial_sol ,0,0);
        cout << string(20, '-' ) << endl;
    }
}