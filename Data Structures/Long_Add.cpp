#include<iostream>
#include<stdlib.h>
#include "Stack.cpp"
using namespace std;

int main(){
    string n1,n2;
    int carry = 0,temp,size;
    cout<<"Enter The First Number : "<<endl;
    cin>>n1;
    Stack<int> S1(n1.length());
    for(int i=0;i<n1.length();i++){
        S1.push(n1[i]);
    }
    cout<<"Enter The Second Number : "<<endl;
    cin>>n2;
    Stack<int> S2(n2.length());
    for(int i=0;i<n2.length();i++){
        S2.push(n2[i]);
    }

    if(n1.length()>n2.length()) size = n1.length()+1;
    else size = n2.length()+1;

    Stack<int> Sum(size);

    for(int i=0;i<size-1;i++){
        if(!S1.isEmpty() && !S2.isEmpty()){
            temp=carry+(S1.Stacktop()-'0')+(S2.Stacktop()-'0');
            Sum.push(temp%10);
            carry=(carry+(S1.pop()-'0')+(S2.pop()-'0'))/10;
            //continue;
        }
        else if(n1.length()>n2.length()){
            Sum.push((carry+(S1.Stacktop()-'0'))%10);
            carry=(carry+S1.pop()-'0')/10;
        }
        else{
            Sum.push((carry+(S2.Stacktop()-'0'))%10);
            carry=(carry+S2.pop()-'0')/10;
        }
    }

    if(carry!=0)
        Sum.push(carry);

    cout<<"\nSum  Is : ";
    while(!Sum.isEmpty())
         cout<<Sum.pop();

    return 0;
}

