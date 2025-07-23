//https://codeforces.com/contest/2126/problem/B


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
        int p=0,q=0;
        for(int d=0;d<n;d++)
        {
           
            if(arr[d]==0)
            {
                p=p+1;
            }
            else if(arr[d]==1) p=0;

            if(p==k)
            {
                q=q+1;
                p=0;
                d=d+1;
            }

        }
        //cout<<n<<"    "<<k<<endl;  
        cout<<q<<endl;  
    }

     return 0;
}