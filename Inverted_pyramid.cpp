
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
    for(int i=n;i>=1;i--)
    {
        for(int j=i;j>=1;j--)
        {
            cout<<"* ";
        }
        cout<<"\n";
    }
    return 0;
}