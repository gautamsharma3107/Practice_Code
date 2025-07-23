//Find largest in the array

#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
typedef long long int  lli;

int main()
{
    int s,k;
    int p=0;
    cin>>k>>s;
    if(k>s)
    {
        k=s;
    }

    for(int x=0;x<=k;x++)
    {
        for(int y=0;y<=k;y++)
        {
        int z=s-x-y;
        if(z<=k && z>=0)
        {
            
            if((x+y+z)==s)
            {
              p++;  
            }
        }}
    }
    cout<<p;
}