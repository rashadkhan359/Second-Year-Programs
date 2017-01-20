#include<iostream>
#include "Stack_main.cpp"

using namespace std;

/*void func(Stack<int> *S1){
    if(S1->isEmpty())
        return;
    int ele = S1->pop();
    func(S1);
    S1->push(ele);
}*/
template <typename T>
void reverse(Stack<T> *S,Stack<T> S2){
    int temp,count=0;
    for(int i=0;i<S->size;i++){
        temp = S->pop();
        count++;
        for(int j=0;j<S->size-count;j++){
            S2.push(S->pop());
        }
        S->push(temp);
        while(!S2.isEmpty()){
            S->push(S2.pop());
        }
    }
}

int main(){

    try{
    Stack<int> S1(5);
    Stack<int> S2(5);
    S1.push(1);
    S1.push(2);
    S1.push(3);
    S1.push(4);
    S1.push(5);
    reverse(&S1,S2);
    for(int i=0;i<5;i++){
        cout<<S1.pop()<<endl;
    }
    }catch(const char* msg){
        cout<<msg<<endl;
    }
    return 0;
}
