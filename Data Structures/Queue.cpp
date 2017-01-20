#include<iostream>
using namespace std;


template <typename T>
class Queue{
    int size;
    T* arr;
    int front,rear;
public :
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
    char ch;
    int choice;
    cout<<"1. Insert\n2. Delete"<<endl;
 label : cout<<"\nEnter Your Choice : ";
    cin>>choice;
    switch(choice){
    case 1 :{
        do{
            cout<<"Enter data : ";
            cin>>ele;
            enQueue(ele);
            cout<<"Do You Want to Insert more?(y/n)  ";
            cin>>ch;
        }while(ch=='y');
        goto label;
    }
    break;
    case 2 : {
        DeQueue();
        cout<<"\nAfter Deletion : ";
        print();
        goto label;
    }
    break;
    default : {
        cout<<"Please choose from above only! Try Again"<<endl;
        goto label;
    }
    }
}


template <class R>
void Queue<R>:: print(){
    if(front==-1){
        cout<<"\nQueue Empty!";
    }
    else{
        cout<<"\nThe Queue Contains : \n";
        for(int i=front;i<rear+1;i++)
            cout<<arr[i]<<" ";
    }
}


int main(){
    int size,choice;
    char del_opt;
    try{
        cout<<"Enter the Size Of Queue : ";
        cin>>size;
        cout<<"Choose enQueue type From Below : \n1. Integer\n2. Character\n3. Float\n4. Double\n5. String\n6. Exit"<<endl;
        cin>>choice;

        switch(choice){
        case 1:{
            Queue<int> Q(size);
            Q.enter();
            break;
        }
        case 2:{

            Queue<char> Q(size);
            Q.enter();
            break;
        }
        case 3:{
            Queue<float> Q(size);
            Q.enter();
            break;
        }
        case 4:{
            Queue<double> Q(size);
            Q.enter();
            break;
        }
        case 5:{
            Queue<string> Q(size);
            Q.enter();
            break;
        }
        case 6 :{
            return 0;
        }
        default:
            cout<<"Please Select Choices From above Only !"<<endl;
            break;
        }
    }catch(const char* msg){
        cout<<msg<<endl;
    }
    return 0;
}
