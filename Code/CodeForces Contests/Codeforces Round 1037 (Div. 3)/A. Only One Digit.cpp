//https://codeforces.com/contest/2126/problem/A

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
        int x;
        cin>>x;
        int d =9;
        while(x>0)
        {
            
            int k=x%10;
            if(k<d)
            {
                d=k;
            }

            x=x/10;

        }
        cout<<d<<endl;
    }

     return 0;
}