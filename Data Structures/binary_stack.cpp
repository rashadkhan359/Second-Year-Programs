#include<iostream>
#include<math.h>
using namespace std;

template <class T>
class Stack{
	int size;
	T *arr;
	int top;

public:
    Stack(int s=0){
        if(s<=0) throw "Invalid Size";
        size=s;
        arr=new T[size];
        top=-1;
    }

	void push(T);
	T pop();
	bool isEmpty();
	bool isFull();
};

template<typename T>
void Stack<T>::push(T ele){
	if(top==size-1)
	throw "Stack Full!!!";
	top++;
	arr[top]=ele;
}

template<typename T>
T Stack<T>::pop(){
	if(top==-1)
	throw "Stack Empty!!!";
	top--;
	return arr[top+1];
}

template<typename T>
bool Stack<T>::isEmpty(){
	return(top==-1);
}

template<typename T>
bool Stack<T>::isFull(){
	return(top==size-1);
}

int main(){
	int n;
	try{
        cout<<"\nEnter The Number : ";
        cin>>n;
        int size = ceil(log2(n)) ;
        if(n%2==0){
            size = size+1;
        }
        Stack<int> ob(size);
        while(n>0){
            ob.push(n%2);
            n=n/2;
        }
        cout<<"The Binary Is : ";
        while(!ob.isEmpty()){
            cout<<ob.pop();
        }
	}
	catch(const char* msg){
        cout<<msg<<endl;
	}
	return 0;
}



