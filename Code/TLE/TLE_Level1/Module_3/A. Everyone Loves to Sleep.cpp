#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin>>t;
    for(int i=0;i<t;i++)
    {
        int n,H,M;
        int dh=0,dm=0,new1,temp=1440,min1;
        cin>>n>>H>>M;
        int minutes=24*60;
        for(int j=0;j<n;j++)
        {
            int hi,mi;
            cin>>hi>>mi;
            
             min1 =(hi*60)+mi;
            //if(min1<minutes) minutes =min1;
            int s= (H*60)+M;
        if(s<=min1) new1 = min1-s;
        else new1 = (1440-s)+min1;
        if(new1<temp) temp=new1;
            
        }
        
        dh=temp/60;
        dm=temp%60;
        cout<<dh<<" "<<dm<<"\n";
    }
}