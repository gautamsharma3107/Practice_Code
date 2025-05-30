//https://codeforces.com/group/MWSDmqGsZm/contest/219774/problem/R
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
typedef long int li;
int main()
{
    int n;
    cin>>n;
    li a[n],b[n];
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    for(int i=0;i<n;i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<endl;
    for(int i=0;i<n;i++)
    {
        if(a[i]>a[i+1])
        {
            int temp=a[i];
            a[i]=a[i+1];
            a[i+1]=temp;
            cout<<a[i]<<" "<<a[i+1]<<endl;
        }
        else{
            cout<<a[i]<<" "<<a[i+1]<<endl;
        }
    }
    return 0;
}