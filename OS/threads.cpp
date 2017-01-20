#include<iostream>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

using namespace std;

void *fib(void *param)
{
    int x = atoi((char*)param);
    cout<<x;
    pthread_exit(0) ;
}

int main(int argc, char *argv[]){
    pthread_t tid; /* the thread identifier */
    pthread_attr_t attr; /* set of thread attributes*/
int rc;
	if (argc != 2) {
        cout<<"Ainvyayi "<<endl;
        return -1;
    }
    if (atoi(argv[1]) < 0) {
        cout<<"Part 2"<<endl;
        return -1;
    }
    /* get the default attributes */
    pthread_attr_init(&attr);
    /* create the thread */
    rc=pthread_create(&tid,&attr,fib,argv[1]);
    /* wait for the thread to exit */
    pthread_join(tid,NULL);
    return 0;
}
    /* The thread will begin control*/

