
/*

Right half pyramid
* 
* * 
* * * 
* * * * 
* * * * * 

*/


#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    cin>>n;
    int k=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=i;j++)
        {
            k++;
            cout<<k<<" ";
           
        }
        cout<<"\n";
    }
    return 0;
}