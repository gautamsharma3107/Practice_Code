//make possible sets of the array

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
    for(int i=0;i<n;i++)
    {
        for(int j=0;i<n;i++)
        {
            cout<<"("<<arr[i]<<", "<<arr[j]<<"), ";
        }
    }
    return 0;
}