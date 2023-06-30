#include <iostream>
#include <vector>
using namespace std;

int n, ones;
vector<int> res;

void write() {
    for (int i = 0; i < n; ++i) {
        if (i != n-1) cout << res[i] << " ";
        else cout << res[i] << endl;
    }
}

void zerones(int indx, int ocount, int zcount) {
    if (indx == n) write();

    else {
        if (zcount < n-ones) {
            res[indx] = 0;
            zerones(indx+1, ocount, zcount+1);
        }

        if (ocount < ones) {
        res[indx] = 1;
        zerones(indx+1, ocount+1, zcount);
        }
    }   
}

int main() {
    cin >> n >> ones;
    res = vector<int> (n);
    zerones(0, 0, 0);
}