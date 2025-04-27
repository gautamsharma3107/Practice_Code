// Digits Summation
// https://codeforces.com/group/MWSDmqGsZm/contest/219158/problem/F
#include <iostream>
using namespace std;

int main()
{
    int a,b;
    cin>>a>>b;
    int sum = (a%10)+(b%10);
    cout<<sum;
    return 0;
}