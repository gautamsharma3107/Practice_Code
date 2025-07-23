//https://codeforces.com/contest/2121/problem/A


#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        int n,s;
        cin>>n>>s;
        int x[n];
        for(int j=0;j<n;j++) cin>>x[j];
        int a1=x[n-1]-x[0];
        //cout<<a1;
       int k1=x[n-1]-s;
       int k2=s-x[0];
       if(s<x[0]) cout<<x[n-1]-s<<"\n";
       else if(s>x[n-1]) cout<<s-x[0]<<"\n";
       else {
                if(k1>=k2) cout<<k2+a1<<"\n";
                else cout<<k1+a1<<"\n";
            }
       
        



    }
    
    return 0;
}
