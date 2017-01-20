#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>


using namespace std;

int i=0;
void task(char *name){
    for(;i<5;i++){
        sleep(rand()%4);
        cout<<"Count for "<<name<<" : "<<i<<endl;
    }
}
int fact(int n){
    if(n==0)
        return 1;
    else return n*fact(n-1);
}
int fib(int n){
    if(n==0)
        return 0;
    if(n==1)
        return 1;
    else{
        return fib(n-1)+fib(n-2);
    }
}
int main()
{
    int opt;
    cout<<"Choose From Below : \n1. Same Program, Same Code\n2. Same Program, Different Code\n3. Different Programs\n4. Parent Waits For Child\n"<<endl;
    cin>>opt;
    pid_t pid = fork();
    srand(pid); // to make thins go a-bit more random ;)
    switch(opt)
    {
    case 1:
        if(pid==0){
            cout<<"I'm Child With Pid = "<<getpid()<<endl;
            task("child");
            cout<<"Child Exitting..."<<endl;
            exit(0);
        }
        else if(pid<0){
            cout<<"Fork() failed!"<<endl;
        }
        if(pid>0){
            cout<<"I'm Parent with Pid = "<<getpid()<<endl;
            task("parent");
            cout<<"Parent Exitting... having Pid = "<<getpid()<<endl;
        }
        break;
    case 2:{
        if(pid<0)
            cout<<"Fork Failed."<<endl;
        if(pid==0){
            cout<<"I'm Child\n";
            cout<<"Factorial in Child : "<<fact(5)<<endl;
        }
        else{
            cout<<"I'm parent\n";
            cout<<"Fibonacci in Parent "<<fib(5)<<endl;
        }
    }
        break;
    case 3:
        if(pid==0){
            cout<<pid<<endl;
            execlp("/home/rdk/Documents/child","",NULL);
            //cout<<"Child Process"<<endl;
        }
        if(pid>0)
            cout<<"I'm Parent Dude!"<<endl;

        break;
    case 4:
        if(pid==0){
            cout<<"Entering Child..."<<endl;
            task("Child");
            cout<<"Child Exitting..."<<endl;
            exit(0);
        }
        if(pid>0){
            cout<<"Entering Parent..."<<endl;
            task("Parent");
            wait(NULL);
            cout<<"Parent Exitted!"<<endl;
        }
        else{
            cout<<"Fork Failed!"<<endl;
        }
        break;
    }
    return 0;
}
