//Ali Baba and Puzzles
//https://codeforces.com/group/MWSDmqGsZm/contest/326175/problem/D
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

 int main()
{
    long long a,b,c,d;
    cin>>a>>b>>c>>d;
    if((a+b-c == d)|| (a-b+c == d)||(a*b+c == d)||(a+b*c == d)||(a*b-c == d)||(a-b*c == d))
    {
        cout<<"YES";
    }
    else{
        cout<<"NO";
    }
    return 0;
}