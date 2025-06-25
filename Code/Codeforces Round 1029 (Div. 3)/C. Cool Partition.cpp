//https://codeforces.com/problemset/problem/808/A

#include <iostream>
#include <algorithm>
#include <string>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        int l;
        cin>>l;
        std::array<int,l> arr;
        for(int j=0;j<l;j++) cin>>arr[j];
        sort(arr, arr+l);
        for(int j=0;j<l;j++) cout<<arr[j];
        cout<<endl;
        int b=1,c=0;
        for(int j=1;j<l;j++)
        {
            if(arr[j-1]==arr[j])
            
            {
                
                if(c>b){b++;}
                else ;
            }
            else if(arr[j-1]!=arr[j]) c++;
        }
        cout<<b<<" "<<c<<"\n";
    }
    return 0;
}
//
 