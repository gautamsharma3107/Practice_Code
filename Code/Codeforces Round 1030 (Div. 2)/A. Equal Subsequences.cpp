#include <iostream>
#include <string>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        string result(n, '0');
        
        // Place all k ones at the beginning
        for (int i = 0; i < k; i++) {
            result[i] = '1';
        }
        
        cout << result << endl;
    }
    return 0;
}