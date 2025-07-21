#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
typedef unsigned int ui;
typedef signed int si;
typedef long long int lli;

int full_house(lli c[])
{
    for(lli i=0;i<5;i++)
    {
        cin>>c[i];
    }
    
    sort(c, c+5);
    if(((c[0]==c[1])&&(c[2]==c[1])&&(c[3]==c[4])) || ((c[0]==c[1])&&(c[2]==c[3])&&(c[3]==c[4])))
    {
        cout<<"Yes";
    }
    else cout<<"No";
    
    return 0;
}

int main()
{
    lli cards[5];
    
    full_house(cards);
    
    return 0;

}