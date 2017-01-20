#include<iostream>
#include<cstdio>
#include <fcntl.h>
#include<unistd.h>
using namespace std;
#define BUF_SIZE 10000


int main(int argc,char *args[]){
    char str[BUF_SIZE];
    bool flag = true;
    if(argc!=3){
    	cout<<"No. of Arguments Are Not what expected!"<<endl;
    }
    ssize_t ret_in;

    //source file
    int fd_i = open(args[2],O_RDONLY);
     if (fd_i == -1) {
            perror("open");
            return 0;
    }

    //destination file
    int fd_o = open(args[1],O_WRONLY | O_CREAT);
     if (fd_o == -1) {
            perror("open");
            return 0;
    }

    cout<<"Copying contents........"<<endl;
    do{
	ret_in = read(fd_i,&str,BUF_SIZE);
	if(ret_in>0)
        	write(fd_o,&str,ret_in);
	else
		flag=false;
    }while(flag==true);
    sleep(2);
    cout<<"Copied"<<endl;
    close(fd_i);
    close(fd_o);
    return 0;
}
