//https://codeforces.com/problemset/problem/59/A
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
//#include <string>

using namespace std;

int main()
{
    string s;
    cin>>s;
    int c=0,l=0;
    for(int i=0;i<s.length();i++)
    {
        if(s[i]>='A' && s[i]<='Z')
        {
            c++;
        }
        else{
            l++;
        }
    }
    if(c>l)
    {
        for(int i=0;i<s.length();i++)
        {
            s[i]= toupper(s[i]);
        
        }
        
    }
    else 
    {
        for(int i=0;i<s.length();i++)
        {
            s[i]= tolower(s[i]);
        
        }
    }
    cout<<s;
    
    return 0;
}