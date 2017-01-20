#include<iostream>
#include <sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
using namespace std;


int main(){
    int pipeshd[2];
    pid_t cpid;
    char buf[30];
    if (pipe(pipeshd) == -1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    cpid = fork();
    if (cpid <0) throw "Fork Failed!!!";
    if (cpid == 0){
        cout<<"Entering Child"<<endl;
        read(pipeshd[0], buf,10);
        cout<<"Read From Child  : "<<buf<<endl;
        exit(0);
    }
    else{
        char s[10]="RDK";
        write(pipeshd[1],s,10);
        close(pipeshd[1]);
        cout<<"Entering Parent"<<endl;
        wait(NULL);
        cout<<"Exiting !"<<endl;
    }
    return 0;
}

