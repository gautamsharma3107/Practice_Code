#include <iostream>
#include <bits/stdc++.h>
using namespace std;
typedef unsigned int ui;
typedef signed int si;
typedef long long int lli;
//typedef long long double lld;

int unique_digit(lli year)
{
    while(true)
    {
        year=year+1;
        ui a,b,c,d;
        a=year/1000;
        b=(year/100)%10;
        c=(year/10)%10;
        d=(year%10);
        if((a!=b)&&(b!=c)&&(c!=d)&&(a!=c)&&(a!=d)&&(b!=d))
        {
            break;
        }

        
    }
    cout<<year;
    return 0;
}

int main()
{
    lli year;
    cin>>year;
    if((year>=1000) && (year<=9000))
    {
        unique_digit(year);
    }
    return 0;

}