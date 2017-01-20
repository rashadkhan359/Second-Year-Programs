#include<iostream>
using namespace std;

int gcd_r(int a,int b){
    if(a%b==0) return b;
    else return gcd_r(b,a%b);
}

int gcd_i(int a,int b){
    int temp;
    while(a%b!=0){
        temp = a;
        a = b;
        b = temp%b;
    }
    return b;
}

int main(){
    int n1,n2,choice;
    cout<<"Enter The Nos. : ";
    cin>>n1>>n2;
    cout<<"Choose : \n1. With Recursion\n2. Without Recursion"<<endl;
    cin>>choice;
    switch(choice){
    case 1 :
        cout<<"GCD is : "<<gcd_r(n1,n2);
    break;
    case 2 :
        cout<<"GCD is : "<<gcd_i(n1,n2);
    break;
    }
    return 0;
}
