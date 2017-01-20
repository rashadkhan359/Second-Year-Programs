#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
using namespace std;

int main(int argc,char *args[])
{
    if(argc!=2){
       cout<<"No. of Arguments Are Not what expected!"<<endl;
    }
    struct stat F;

    if(stat(args[1],&F)<0)throw("Error\n");

    cout<<"\nInformation for file at "<<args[1]<<endl;
    cout<<"---------------------------\n";
    cout<<"File Size: \t"<<F.st_size<<endl;
    cout<<"Group ID :\t"<<F.st_gid<<endl;
    cout<<"Time of last access: \t"<<ctime(&F.st_atime)<<endl; //prec
    cout<<"Time of last data modification\t"<<ctime(&F.st_mtime)<<endl;
    cout<<"Time of last status Change\t"<<ctime(&F.st_ctime)<<endl;
    cout<<"File Permissions: \t";
    cout<<((F.st_mode & S_IRUSR) ? "r" : "-");
    cout<<((F.st_mode & S_IWUSR) ? "w" : "-");
    cout<<((F.st_mode & S_IXUSR) ? "x" : "-");
    cout<<((F.st_mode & S_IRGRP) ? "r" : "-");
    cout<<((F.st_mode & S_IWGRP) ? "w" : "-");
    cout<<((F.st_mode & S_IXGRP) ? "x" : "-");
    cout<<((F.st_mode & S_IROTH) ? "r" : "-");
    cout<<((F.st_mode & S_IWOTH) ? "w" : "-");
    cout<<((F.st_mode & S_IXOTH) ? "x" : "-");
    cout<<"\n\n";

    return 0;
}
