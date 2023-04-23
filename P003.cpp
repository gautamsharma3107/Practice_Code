#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    // Complete the code.
    string arr[10] = {"zero","one","two","three","four","five","six","seven","eight","nine"};
    string* ptr;
    *ptr = arr[0];
    cout<< *(ptr+1) <<endl;
     
    return 0;
}