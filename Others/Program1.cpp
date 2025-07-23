//Find largest in the array

#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
typedef long long int  lli;

int main()
{
    int n;
    cin>>n;
    int arr[n],temp;
    
    
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];  
    }
    temp=arr[0];
    for(int i=1;i<n;i++)
    {
        if(arr[i]>temp)
        {
            temp=arr[i];
        }
    }
    cout<<temp<<endl;
    return 0;
}