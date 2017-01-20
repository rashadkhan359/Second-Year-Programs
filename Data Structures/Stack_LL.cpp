#include<iostream>
using namespace std;

template <typename T>
struct node{
    T data;
    node *next;
};


template <typename T>
class Stack_LL{
    	node<T> *top;
public :
    Stack_LL(){
        top=NULL;
    }
    void push(T ele);
    T pop();
    void printStack();
    bool isEmpty();
    int Stacktop();
};

template <typename T>
bool Stack_LL<T> :: isEmpty(){
    return (top==NULL);
}

template <typename U>
int Stack_LL<U> :: Stacktop(){
    if(isEmpty()) throw "Empty";
    return top->data;
}

template<typename U>
   void Stack_LL<U> :: push(U ele){
        node<U>* new_node = new node<U>;
        new_node->data = ele;

        if(top==NULL){
            new_node->next =NULL;
            top = new_node;
        }
        else{
            new_node->next = top;
            top = new_node;
        }
    }

template<typename U>
U Stack_LL<U> :: pop(){
    if(isEmpty()) throw "Stack Empty";
    U x;
        node<U> *temp;
        x = top->data;
        temp = top;
        if(top->next==NULL)
            top = NULL;
        else
            top = top->next;

        delete temp;
    return x;
}

template <typename T>
void Stack_LL<T> :: printStack(){
    if(top==NULL) throw "Empty";
    node<T> *temp = top;
    while(temp!=NULL){
        cout<<temp->data<<" ";
        temp=temp->next;
    }
}
int main(){
    try{
        Stack_LL<int> S;
        cout<<"POp : "<<S.Stacktop()<<endl;
        S.printStack();
    }
    catch(const char* msg){
        cout<<msg<<endl;
    }
    return 0;
}
