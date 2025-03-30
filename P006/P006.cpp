#include<iostream>
using namespace std;
int update(int*x, int*y)
{
int sum = *x+*y;
int diff = *x-*y;
*x = sum;
*y = abs(diff);
return *x,*y;
}


int main()
{
  int a,b;
  cin>>a>>b;
  update(&a,&b);
  
  cout<<a<<endl<<b<<endl;


}