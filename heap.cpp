#include <iostream>
#include <vector>
using namespace std;

void buildHeap(vector<int>& H) {
    int n = H.size() - 1;

    for (int i = n / 2; i >= 1; i--) {
        int k = i;
        int val = H[k];
        bool isHeap = false;

        while (!isHeap && 2 * k <= n) {
            int j = 2 * k;

            if (j < n && H[j] < H[j + 1]) {
                j++;
            }

            if (val >= H[j]) {
                isHeap = true;
            } else {
                H[k] = H[j];
                k = j;
            }
        }

        H[k] = val;
    }
}

int main() {
    int n;
    cin >> n;

    vector<int> H(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> H[i];
    }

    buildHeap(H);

    for (int i = 1; i <= n; i++) {
        cout << H[i] << " ";
    }
    cout << endl;

    return 0;
}
