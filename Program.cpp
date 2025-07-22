

#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
#include <string>
using namespace std;
typedef unsigned int ui;
typedef signed int si;
typedef long long int lli;
typedef long double ld;

void rotate(ui n)
{
    ui cube[n][n];
    for(ui i=0; i<n; i++)
   {
    for(ui j=0; j<n; j++)
    {
        cin>>cube[i][j];
    }
   }
   
   
   for(ui i=0; i<n; i++)
   {
    for(ui j=0; j<n; j++)
    {
        cout<<cube[i][j]<<" ";  
    }
    cout<<endl;  
   }
     return;
   
    
    
}

int main()
{
    ui n;
    cin>>n;
    //int cube[n][n];
    rotate(n);

}