#include<iostream>
using namespace std;


int fib_r(int n){
    if(n==1) return 0;
    if(n==2) return 1;
    else return (fib_r(n-1)+fib_r(n-2));
}

void fib_i(int n){
    int first =0,second=1,next;
    for(int i=0;i<n;i++){
        if(i<=1) next=i;
        else{
            next = first + second;
            first = second;
            second = next;
        }
        cout<<next<<endl;
    }
}

int main(){
    int n,choice;
    cout<<"Enter The No. : ";
    cin>>n;
    cout<<"Choose : \n1. With Recursion\n2. Without Recursion"<<endl;
    cin>>choice;
    cout<<endl;
    switch(choice){
    case 1 :
        for(int i=1;i<=n;i++){
            cout<<fib_r(i)<<endl;
        }
        break;
    case 2 : fib_i(n);
        break;
    default :
        cout<<"Please Choose From Above Only ";
        break;
    }
    return 0;
}
