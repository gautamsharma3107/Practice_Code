//https://codeforces.com/problemset/problem/808/A

#include <iostream>
#include <algorithm>
#include <string>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        int d,b;
        cin>>d>>b;
        int door[d];
        for(int j=0;j<d;j++) cin>>door[j];
        //for(int j=0;j<d;j++) cout<<door[j]<<" ";
        //cout<<endl;
        int m=0,n=0, o=0;
        for(int j=0;j<d;j++)
        {
            if((door[j]==0)&& n==0)
            {
                m++;
            }
            else if((door[j]==1))
            {
                n++;
                o=0;
            }
            else if(door[j]==0)
            {
                n++;
                o++;
            }                                                                                                    
            
        }
        int r=n-o;
        //cout<<m<<" "<<n<<" "<<o<<" \n";
        if(b>=r) cout<<"YES\n";
        else cout<<"NO\n";

    }
    return 0;
}
//