// Memo and Momo
// https://codeforces.com/group/MWSDmqGsZm/contest/326175/problem/B
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

 int main()
{
    int a,b,k;
    cin>>a>>b>>k;
    if((a%k==0)&&(b%k==0))
    {
        cout<<"Both";
    }
    else if(a%k==0)
    {
        cout<<"Memo";
    }
    else if(b%k==0)
    {
        cout<<"Momo";
    }
    else{
        cout<<"No One";
    }
    return 0;
}