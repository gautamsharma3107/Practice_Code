//Max and Min
//https://codeforces.com/group/MWSDmqGsZm/contest/219158/problem/K
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

 int main()
{
    int a,b,c;
    cin>>a>>b>>c;
    auto mi = min({a,b,c});
    auto ma = max({a,b,c});
    cout<<mi<<" "<<ma;
    return 0;
}