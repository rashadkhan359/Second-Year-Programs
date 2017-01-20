#include<iostream>
using namespace std;

struct packet{
	string msg;
};

struct frame{
	packet data;
	bool ack=0;
};

frame channel;
string final_msg="";

void to_PL(frame f){
	channel=f;
}

void to_NL(frame f){
	cout<<"Received : "<<f.data.msg<<endl;
	final_msg = final_msg.append(f.data.msg+" ");
	cout<<"Message Received till now : "<<final_msg;
}

frame from_PL(){
	return channel;
}

packet from_NL(){
	string msg;
	cin>>msg;
	packet data;
	data.msg=msg;
	return data;
}

void Sender_DLL(){
	if(from_PL().ack==1){
		cout<<"\nAcknowledgment Received at Sender.\n"<<endl;
	}
	frame f;
	f.data=from_NL();
	to_PL(f);
}

void Reciever_DLL(){
	frame f=from_PL();
	to_NL(f);
	frame ack;
	ack.ack=1;
	to_PL(ack);
}

int main(){
	cout<<"Enter Your Message : ";
	while(true){
		Sender_DLL();
		Reciever_DLL();
	}
	return 0;
}
