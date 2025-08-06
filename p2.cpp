

#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
#include <string>
using namespace std;
typedef unsigned int ui;
typedef signed int si;
typedef long long int lli;
typedef long double ld;



int main()
{
    int t;
    cin>>t;

    for(int i = 0;i<t;i++)
    {
        int n, limit;
        cin>>n;
        vector<int> ai;
        int k;
        while(cin<<k && int i<n)
        {
            ai.push_back(k);
            i++;
        }


        for(int i= 0;i<n;i++)
        {
            if(ar[i]<ar[i+1])
            {
                cout<<"L";
            }
            else cout<<"R";
        }
    }
    return 0;

}