#include<iostream>
#include<stdlib.h>
#include<fstream>
using namespace std;

void cpuinfo(){
    cout<<"\t\t-------------CPU InFo--------------\n\n"<<endl;
    string temp
	ofstream obj;
	obj.open("temp.txt");
    system("lscpu | grep MHz  > temp.txt");
	system("lscpu | grep Model >> temp.txt");
	system("uname -r >>temp.txt");
	obj.close();

	ifstream obj1;
	obj1.open("temp.txt");
	while(!obj1.eof()){
            getline(obj1,temp);
            cout<<temp<<"\n";
	}
	obj1.close();

}

void meminfo(){
    char data[10000];
    string temp;
	ofstream obj;
	obj.open("temp.txt");
	obj<<"\t\t-------------Memory InFo--------------\n\n"<<endl;
    	system("free -m  >> temp.txt");
	obj<<data<<endl;
	obj.close();

	ifstream obj1;
	obj1.open("temp.txt");
	while(!obj1.eof()){
        getline(obj1,temp);
        cout<<temp<<"\n";
	}
	obj1.close();
}

int main(){
	cpuinfo();
	cout<<endl;
	meminfo();
	return 0;
}
