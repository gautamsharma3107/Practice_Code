#include <iostream>
#include <vector>
using namespace std;


int main() {
    vector <int> num = {1,2,3}; //vector initialization 1st way;
    for(int i: num) cout<<i<<" "; // Here, i is the increamnting variable which will give the value store and indexes in a sequence.
    cout<<endl;

    vector <int> vec(5,0);  // Second way to initializa the vector where the 5 is the size of the vectror and 0 is the value that will be stored in the element space.
    for(int j: vec) cout<<j<<" ";
    cout<<endl; 
    
    
    vector <char> abc = {'a', 'b' };
    for(char val: abc) cout<<val<<" ";
    cout<<endl; 


    // size() function
    //to take the size of the vector
    int sz = abc.size();
    cout<<sz<<endl;

    sz = num.size();
    cout<<sz<<endl;
   
    sz = vec.size();
    cout<<sz<<endl;


    //push_back() function
    // if there is an empty vector or the vector is having the element then if we add the element in the vector then push_back(val) will add val at the end or at the last of the vector 
     
    vector <int> pussh_back = {}; //currently it is an empty vector
    pussh_back.push_back(56);
    pussh_back.push_back(6);
    pussh_back.push_back(5);
    for(int val: pussh_back) cout<<val<<" ";
    cout<<endl;

    // for pop_back function
    // it removes the last elment from the array.

    vector <int> poop_back = {56, 6, 5,8}; 
    poop_back.pop_back();
    poop_back.pop_back();
    //poop_back.push_back(5);
    for(int val: poop_back) cout<<val<<" ";
    cout<<endl;

    //front() and back() fucnction 
    // it returns the first value of the vector
    vector <int> nums = {56, 6, 5,8}; 

    cout<<nums.front();
    cout<<endl;
    cout<<nums.back();
    cout<<endl;

    //at() function
    cout<<nums.at(2);
    cout<<endl;

    //capacity functio

    vector <int> num1;
    cout<<num1.size()<<endl;
    num1.push_back(3);
    cout<<"Size when vector is empty = "<<num1.size()<<endl;
    cout<<"Capacity when vector is empty = "<<num1.capacity()<<endl;
    
    num1.push_back(54);
    cout<<"Size when vector is having 1 element = "<<num1.size()<<endl;
    cout<<"Capacity when vector is 1 element = "<<num1.capacity()<<endl;
    num1.push_back(54);
    num1.push_back(54);
    num1.push_back(54);
    cout<<"Size when vector is having 5 element = "<<num1.size()<<endl;
    cout<<"Capacity when vector is 5 element = "<<num1.capacity()<<endl; 







    
    return 0;
}