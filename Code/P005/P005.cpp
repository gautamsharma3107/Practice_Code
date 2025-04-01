#include <iostream>
using namespace std;

int max_of_four(int x, int y)
{
 if (x < y) 
 {
   return y; 
 } 
 else
 {
   return x; 
 } 
 
}

int main()
{
    int a,b,c,d;
    cin >>a>>b>>c>>d;
    int left = max_of_four(a,b);
    int right = max_of_four(c,d);
    int result = max_of_four(left,right);
    cout << result << endl;
    return 0;
}