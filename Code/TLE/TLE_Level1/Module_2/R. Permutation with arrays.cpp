//https://codeforces.com/group/MWSDmqGsZm/contest/219774/problem/R
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
typedef long int li;
int main()
{
    int n;
    cin>>n;
    int a[n],b[n];

    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n;i++) cin>>b[i];

    sort(a,a+n);
    //for(int i=0;i<n;i++) cout<<a[i]<<" ";
    sort(b,b+n);
    //for(int i=0;i<n;i++) cout<<b[i]<<" ";

    for(int i=0;i<n;i++)
    {
        if(a[i] != b[i]) {
            cout<<"no";
            return 0;
         }
         
    }
    cout<<"yes";
    
}

// Another Approach suggested by copilot
// bool isPermutation = true;
// for(int i=0; i<n; i++) {
//     if(a[i] != b[i]) {
//         isPermutation = false;
//         break;
//     }
// }
// cout << (isPermutation ? "yes" : "no");