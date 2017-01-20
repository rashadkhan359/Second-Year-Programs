#include<iostream>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<sys/wait.h>

using namespace std;


int main(){
    pid_t pid;
    key_t key;
    int segment_id;
    char* arr = new char[10];
    char *shared_memory,*data,*data1;
    const int size = 4096;
    segment_id = shmget(key, size, S_IRUSR | S_IWUSR);
    if((shared_memory = (char*)shmat(segment_id, NULL, 0)) == (char *)-1) {
        perror("shmat");
        exit(1);
    }
    data = shared_memory;
    pid = fork();
    if(pid<0) throw "Fork Failed!";
    if(pid==0){
        cout<<"Entering Child"<<endl;
        for (int i=0; i <= 10; i++)
            *data++ = 'R';

        cout<<"Exiting Child"<<endl;
        exit(0);
    }
    else {
        cout<<"Entering Parent."<<endl;
        wait(NULL);
        cout<<"Harambe! "<<shared_memory<<endl;
        shmdt(shared_memory);
        shmctl(segment_id, IPC_RMID, NULL);
        cout<<"Exiting..."<<endl;
    }
    return 0;
}
