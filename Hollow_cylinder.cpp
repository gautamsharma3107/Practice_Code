
/*

Hollow_squre
* * * * * 
*       * 
*       * 
*       * 
* * * * * 


*/


#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

int main()
{
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=k;j++)
        {
            if((i==1)||(i==n))
            {
                cout<<"* ";
            }
            else{
                if((j==1)||(j==k))
                {
                    cout<<"* ";
                }
                else{cout<<"  ";}
            }
           
        }
         cout<<endl;
    }
    return 0;
}