//https://atcoder.jp/contests/abc305/tasks/abc305_a


#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

void nearest_station(int n)
{
    if((n%5<3) || (n%5==0))
    {
        int a= n-(n%5);
        cout<<a<<"\n";
    }
    else
    {
        int a= n+(n%5)-1;
        cout<<a<<"\n";
    }
}

int main()
{
    int N;
     cin>>N;
     nearest_station(N);
     return 0;
}