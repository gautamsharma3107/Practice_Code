//https://codeforces.com/problemset/problem/266/B
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

int main()
{
    int n,t;
    cin>>n>>t;
    string s;
    cin>>s;
    int a=s.length();

    for(int i=0;i<t;i++)
    {
      for(int j=0;j<n;j++)
      {
        if(s[j]=='B'&& j<(n-1) && s[j+1]!='B')
        {
            char temp;
            temp=s[j];
            s[j]=s[j+1];
            s[j+1]=temp;
            //cout<<s[j]<<s[j+1];
            j++;
            //cout<<j<<endl;
            
        }
        
      } 
       
    }
    cout<<s<<endl;
    return 0;
}
