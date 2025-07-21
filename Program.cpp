
/*

Right half pyramid
1 
2 3 
4 5 6 
7 8 9 10 
11 12 13 14 15 

*/


#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    cin>>n;
    
for(int i=1;i<=n;i++)
{
    for(int j=1;j<=((2*n)-1);j++)
    {
        // best for the if((j<=i)||(j>((2*n)-i)))
        if((j>=(n-i)&&(j<(((2*n)-1)-(n-i)))))
        {
            cout<<"*";
        }
        else
        {
            cout<<" ";
        }
    }
    cout<<endl;
}   
 return 0;
}