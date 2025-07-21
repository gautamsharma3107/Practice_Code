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
        int n;
        cin>>n;
        int p[n],s[n];
        bool result = true;
        for(int j=0;j<n;j++) cin>>p[j];
        for(int j=0;j<n;j++) cin>>s[j];
        std::sort(p, p + n);
        std::sort(s, s + n);    
        
        if(p[0]==s[0])
        {
            for(int k=1;k<n;k++)
            {
                if((p[k]%p[0]!=0) || (s[k]%s[0]!=0))
                {
                    result = false;
                    break; // Exit immediately when condition fails
                }
                // Don't set result = true here, it's already true
            }
        }
        else
        {
            result = false; // First elements don't match
        }

        if(result) 
        {cout<<"yes"<<endl;}
        else 
        {cout<<"No"<<endl;}
    }

     return 0;
}