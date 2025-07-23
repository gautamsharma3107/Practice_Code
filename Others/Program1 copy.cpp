//Find largest in the array

#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
typedef long long int  lli;

int main()
{
    int n;
    cin>>n;
    int k=0;
    for(int i=0;i<n;i++)
    {
        int p;
        cin>>p;
        if(p>k) k=p;
    }
    cout<<k;
    return 0;
}