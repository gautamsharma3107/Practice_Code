//https://atcoder.jp/contests/abc305/tasks/abc305_a


#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

int main()
{
    int t;
    cin>>t;
    
    for(int i=0;i<t;i++)
    {
        int n,k;
        cin>>n>>k;
        int arr[n];
        for(int j=0;j<n;j++) cin>>arr[j];
        for(int d=0;d<n;d++)
        {
            int p=0,q=0;
            if(arr[i]==0)
            {
                p=p+1;
            }
            else p=0;

            if(p==k);
            {
                n=n+1;
                i=i+1;
            }

        }  
        cout<<n;  
    }

     return 0;
}