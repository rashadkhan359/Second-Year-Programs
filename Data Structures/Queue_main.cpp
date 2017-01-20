#include<iostream>

using namespace std;


template <typename T>
class Queue{

public :
    int size;
    T* arr;
    int front,rear;
    Queue(int s){
        if(s<=0) throw "Invalid Size";
        size = s;
        arr =  new T[size];
        front=rear=-1;
    }

    ~Queue(){ delete [] arr;}

    bool isFull();
    bool isEmpty();
    void enQueue(T data);
    T DeQueue();
    void enter();
    void print();
};


template <typename U>
 bool Queue<U> :: isFull(){
    return (front==0 && rear==size-1);
}



template <typename U>
bool Queue<U> :: isEmpty(){
    return (front==-1);
}


template <typename U>
void Queue<U> :: enQueue(U data){
    if(!isFull()){
        if(isEmpty()){
            front = 0;
            rear = 0;
        }
        else if(rear<size-1){
            rear = rear+1;
        }
        else if(front!=0 && rear==size-1){
            for(int i=front;i<=rear;i++){
                arr[i-front] = arr[i];
            }
            rear = rear - front + 1;
            front=0;
        }
        arr[rear]=data;
    }
    else throw "Queue is Full";
}


template <typename U>
U Queue<U> :: DeQueue(){
    U temp;
    if(isEmpty()) throw "Queue is Empty";
    else{
        temp = arr[front];
        if(front==rear){
            front=-1;
            rear=-1;
        }
        else{
            front++;
        }
        return temp;
    }
}


template <class R>
void Queue<R> :: enter(){
    R ele;
    for(int i=0;i<size;i++){
        cin>>ele;
        enQueue(ele);
    }
}


template <class R>
void Queue<R>:: print(){
    if(front==-1){
        cout<<"\nQueue Empty!";
    }
    else{
        cout<<"\nThe Queue Contains : \n";
        for(int i=front;i<size;i++)
            cout<<arr[i]<<" ";
    }
}


