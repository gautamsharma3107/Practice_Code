

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
        cin>>n>>limit;
        int bag[n];
        int m=1;
        int rem = 0;
        for(int j=0; j<n;j++)
        {
            cin>>bag[j];
            bag[j]=bag[j]*m;
            if(bag[j]>limit) {
                
                
                rem++;
                
            }
            else{m++;}
            //cout<<rem<<endl;
        }

        cout<<rem<<endl;
    }
    return 0;

}