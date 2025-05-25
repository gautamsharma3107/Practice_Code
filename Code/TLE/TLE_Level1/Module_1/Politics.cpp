//https://codeforces.com/problemset/problem/1818/A
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
typedef unsigned int ui;
int main()
{
    ui t,m,d;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        int k=1;
        cin>>m>>d;
        string p[m];
        for(int i=0;i<m;i++)
        {
            cin>>p[i];
        }
        for(int j=1;j<m;j++)
        if(p[0]==p[j])
        {
            k++;
        }
        cout<<k<<endl;
    }
    return 0;
}