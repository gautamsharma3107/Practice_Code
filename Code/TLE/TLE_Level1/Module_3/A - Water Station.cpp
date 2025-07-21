//https://atcoder.jp/contests/abc305/tasks/abc305_a


#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    int remainder = n % 5;
    
    if (remainder <= 2) {
        // Round down
        cout << n - remainder << "\n";
    } else {
        // Round up  
        cout << n + (5 - remainder) << "\n";
    }
    
    return 0;
}