#include <iostream>
using namespace std;
int main() {
    string arr[10] = {"zero","one","two","three","four","five","six","seven","eight","nine"};
    string* ptr;
    ptr = &arr[0];
    int m,n;
    cin >>m>> n;

    for(int i = m; i <=n; i++)
    {
        if(i>=1&&i<=9)
        {
            cout<<ptr[i]<<endl;
        }
        else if(i>9)
        {
            if(i%2==0)
            {
                cout<<"even"<<endl;

            }
            else
            {
                cout<<"odd"<<endl;
            }
        }
    }
    return 0;
} 