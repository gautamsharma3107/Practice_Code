//https://codeforces.com/problemset/problem/1971/C
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
#include <string>   
using namespace std;

int main()
{
    int t;
    cin>>t;
    int a,b,c,d;
    for(int i=1; i<=t; i++)
    {
        cin>>a>>b>>c>>d;
        int ab[2] = {a, b};
        int cd[2] = {c, d};
        sort(ab,ab+2);
        sort(cd,cd+2);
        // Count how many of cd[0] and cd[1] are between ab[0] and ab[1]
        int count = 0;
        if(cd[0] > ab[0] && cd[0] < ab[1]) count++;
        if(cd[1] > ab[0] && cd[1] < ab[1]) count++;

        if(count == 1) cout<<"YES";  // Exactly one point between means intersection
        else cout<<"NO";
        cout<<endl;

    }
    
}