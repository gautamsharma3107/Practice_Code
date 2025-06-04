//https://www.hackerearth.com/problem/golf/print-the-pattern/?purpose=login&source=problem-page&update=google
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    cin>>n;
    int a=0,b;
    for(int i=1;i<=n;i++)
    {
        b=a+i;
        if(i%2==0)
        {
            for(int j=1;j<=i;j++) 
            {
                a++;
                cout<<a<<" ";
            }
        }
        else
        {
            a=b;
            for(int j=1;j<=i;j++) 
            {
                cout<<b<<" ";
                b--;
            }
        }
        cout<<endl;
    }
    return 0;
}