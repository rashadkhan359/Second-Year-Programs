#include<iostream>
using namespace std;

template <typename T>
class Stack{
        int size;
	int top;
    	T *arr;
public :

    Stack(int s){
        if(s<=0) throw "Invalid Size";
        else{
            size = s;
            arr = new T[size];
            top=-1;
        }
    }

    ~Stack(){
        delete [] arr;
    }

    void push(T ele);
    int pop();
    bool isEmpty();
    bool isFull();
    int Stacktop();
};

template<typename U>
bool Stack<U> :: isFull(){
    return (top==size-1);
}

template<typename U>
int Stack<U> :: Stacktop(){
    if(top==-1) throw "Stack Empty";
    else return arr[top];
}

template<typename U>
   void Stack<U> :: push(U ele){
        if(top==size-1) throw "Stack Overflow";
        ++top;
        arr[top]=ele;
    }

template<typename U>
int Stack<U> :: pop(){
    if(top==-1) throw  "Stack Empty";
    U x = arr[top];
    top--;
    return x;
}
template<typename U>
bool Stack<U> ::isEmpty(){
    return (top==-1);
}

