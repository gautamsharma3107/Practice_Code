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
            // best for the ----
            if((j<=i)||(j>((2*n)-i)))
            // best for pyramid ---if((j>(n-i)&&(j<=(((2*n)-1)-(n-i)))))
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