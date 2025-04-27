//Comparison
//https://codeforces.com/group/MWSDmqGsZm/contest/219158/problem/V
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

 int main()
{
    int a,b; char s;
    cin>>a>>s>>b;
    if(s == '>')
    {
        if(a>b)
        {
            cout<<"Right";
        }
        else
        {
            cout<<"Wrong";
        }
    }
    else if(s == '<')
    {
        if(a<b)
        {
            cout<<"Right";
        }
        else
        {
            cout<<"Wrong";
        };
    }
    else
    {
        if(a==b)
        {
            cout<<"Right";
        }
        else
        {
            cout<<"Wrong";
        }
    }
    return 0;
}