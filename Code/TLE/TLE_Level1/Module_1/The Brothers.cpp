// The Brothers
//https://codeforces.com/group/MWSDmqGsZm/contest/219158/problem/L
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

 int main()
{
    string first_name1,first_name2,sec_name1,sec_name2;
    cin>>first_name1>>sec_name1;
    cin>>first_name2>>sec_name2;
    if(sec_name1 == sec_name2)
    {
        cout<<"ARE Brothers"<<"\n";
    }
    else
    {
        cout<<"NOT"<<"\n";
    }
    return 0;
}