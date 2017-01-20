#include<iostream>
#include "Queue_main.cpp"
#include "Stack_main.cpp"
using namespace std;

void reverse(Stack<int> *S,Queue<int> Q){
    for(int i=1;i<=S->size;i++)
		Q.enQueue(S->pop());
	for(int i=1;i<=Q.size;i++){
        int x=Q.DeQueue();
        S->push(x);
    }
}


int main()
{
    int size,X;
    cout<<"Enter The Size Of Stack : ";
    cin>>size;
	Stack<int> S(size);
	Queue<int> Q(size);

	cout<<"Enter The Data : "<<endl;
	for(int i=0;i<size;i++){
        cin>>X;
        S.push(X);
	}

    reverse(&S,Q);
	cout<<"After Reversing "<<endl;
	for(int i=1;i<=5;i++)
		cout<<S.pop()<<" ";
	return 0;
}

