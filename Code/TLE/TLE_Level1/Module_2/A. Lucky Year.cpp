//https://codeforces.com/problemset/problem/808/A

#include <iostream>
#include <algorithm>
#include <string>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    string s = to_string(n);
    int len = s.length();
    //cout<< len << endl;
    //int num=((int)pow(10, len-1)) - (n%(int)(pow(10, len-2)));
    //cout << num << endl;
    if(n < 10) {
        cout << 1 << endl; // If n is a single digit, the lucky year is always 1
    }
    else{
        int l=(pow(10, len-1));
    int r=n%l;
    //cout<<" "<<r<<endl;
    int luckyYear = l - r;
    cout<< luckyYear << endl;
    
    
    }
    
        return 0;

}