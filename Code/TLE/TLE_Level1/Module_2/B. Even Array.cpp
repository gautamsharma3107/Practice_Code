//https://codeforces.com/problemset/problem/1367/B

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
        int n,p=0,e=0,o=0;
        cin>>n;
        int a[n];
        for(int i=0;i<n;i++)
        {
            cin>>a[i];
            if((i%2==0 && a[i]%2==0) || (i%2==1 && a[i]%2==1))
            {
                

            }
            else{
                if((i%2==0 && a[i]%2==1)) e++;
                else if((i%2==1 && a[i]%2==0)) o++;
                p++;
                
            }
            
        }//cout<<"p="<<p;
        if((p%2==0 || p==0) && e==o)
        {
            int m =p/2;
            cout<<m;
        }
        else cout<<"-1";
        cout<<endl;
    }
    return 0;
}