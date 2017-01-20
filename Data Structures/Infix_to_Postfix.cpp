#include<iostream>
#include<string>
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
    int stackTop();
};

template<typename U>
bool Stack<U> :: isFull(){
    return (top==size-1);
}

template<typename U>
   void Stack<U> :: push(U ele){
        if(top==size-1) throw "Stack Overflow";
        ++top;
        arr[top]=ele;
    }

template<typename U>
int Stack<U> :: pop(){
    if(top==-1) throw  "Can't Pop, Stack Empty";
    U x = arr[top];
    --top;
    return x;
}
template<typename U>
bool Stack<U> ::isEmpty(){
    return (top==-1);
}
template<typename U>
int Stack<U> :: stackTop(){
    if(isEmpty()) throw "Stack bcEmpty";
    return arr[top];
}

int compare(char x){
    if(x=='-' || x=='+') return 0;
    if(x=='*' || x=='/') return 1;
}

bool Precedence(char s_top,char in){
    if(s_top=='(' || in=='(') return false;
    else if(in==')') return true;
    //else if
    else if(compare(s_top)==compare(in)) return true;
    else return (compare(s_top)>compare(in));
}

int main(){
    try{
        string infix;
        cout<<"Enter : ";
        cin>>infix;
        char postfix[infix.length()];
        int j=0;
        Stack<char> S(infix.length());
        for(int i=0;infix[i]!='\0';i++){
            if(isdigit(infix[i])){
                postfix[j++] = infix[i];
            }
            else{
                while(!S.isEmpty() && S.stackTop()!='(' && Precedence(S.stackTop(),infix[i])){
                    postfix[j++] = S.pop();
                    //if(!S.isEmpty() && S.stackTop()=='(')
                      //  S.pop();
                }

                if(infix[i]!=')')
                    S.push(infix[i]);

            }
        }

        while(!S.isEmpty()){
            if(S.stackTop()=='(')
                S.pop();
            else
                postfix[j++] = S.pop();
        }

        cout<<"The Postfix is : ";
        for(int k=0;k<j;k++){
            cout<<postfix[k];
        }
        cout<<endl;

        //----------------------------EVALUATION------------------------------//

        Stack<int> E(j);
        int a,b,f=0;
        for(int i=0;i<j;i++){
            if(isdigit(postfix[i])){
                E.push((postfix[i]-'0'));
            }
            else{
                a = E.pop();
                b = E.pop();
                if(postfix[i]=='+'){
                    f = a+b;
                    E.push(f);
                }
                else if(postfix[i]=='-'){
                    f = b-a;
                    E.push(f);
                }
                else if(postfix[i]=='/'){
                    f = b/a;
                    E.push(f);
                }
                else if(postfix[i]=='*'){
                    f= a*b;
                    E.push(f);
                }
            }
        }
        cout<<"Evaluated as : "<<E.pop()<<endl;
    }catch (const char* msg){
        cout<<msg<<endl;
    }
    return 0;
}
