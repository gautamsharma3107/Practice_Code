#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

 int main()
{
    char s;
    
    cin>>s;
    if(s=='z')
    {
        cout<<"a"<<endl;
    }
    else{
        char n = char(int(s)+1);
        cout<<n<<endl;
    } 
    
    return 0;
}