#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
using namespace std;
# define MAX_SIZE 10
# define MAX_SEQ 3


struct packet{
	string data;
};

struct frame{
	packet info;
	int seq_no;
	int ack;
}gdata[MAX_SEQ+1],gdata1;

int i=0,j=0,k=0;
bool error=false;

enum event_type{frame_arrival,timeout,checksum,network_layer_ready};

void from_NL(packet*p){
	cout<<"Enter data  :  ";
	cin>>p->data;
}

void to_PL_A(frame*f){
	if(error==false){
		cout<<"Sending the data to Physical Layer(gdata)\n";
		gdata[i]=*f;
		i=(i+1)%(MAX_SEQ+1);
	}
	else{
		gdata[j]=*f;
	}
}

void from_PL_B(frame*f){
	*f=gdata[k];
	k=(k+1)%(MAX_SEQ+1);
}

void to_PL_B(frame *d){
	gdata1=*d;
}

void from_PL_A(frame*f){
	*f=gdata1;
}

void to_NL(packet*p){
	cout<<p->data<<endl;
}

void wait_for_event_reciever(event_type *e){
	int r=rand()%5;
	if(r==0)
		*e=checksum;
	else
		*e=frame_arrival;
}
void B(){
	frame r,d;
	event_type event;
	int frame_expected=0;
	packet buffer;
	wait_for_event_reciever(&event);
	if(event==frame_arrival){
		from_PL_B(&r);
		if(r.seq_no == frame_expected){
			to_NL(&r.info);
			frame_expected = (frame_expected+1)%(MAX_SEQ+1);;
			cout<<"Data "<<r.seq_no<<" sent by A ,Received at B is "<<endl;
		}
		cout<<"Enter piggybacked data to send at A"<<endl;
		from_NL(&buffer);
		d.info=buffer;
		d.ack=frame_expected-1;
		cout<<"sending piggybacked frame"<<endl;
		to_PL_B(&d);
	}
	else{         //checksum
		cout<<"\n\t\t#############CheckSum Occurred###############\n"<<endl;
		error=true;
	}
}

void enable_NL(event_type *e){
	*e=network_layer_ready;
}

void disable_NL(){
	B();
}

void A(){
	int ack_expected=0;
	frame f,s;
	packet buffer[MAX_SEQ+1];
	int nbuffered=0;
	event_type event;
	enable_NL(&event);
	int next_frame_to_send=0;
	while(true){
		switch(event){
		case frame_arrival:
			cout<<"piggybacked frame from b received "<<endl;
			from_PL_A(&f);
			if(f.ack==ack_expected){
				nbuffered--;
				ack_expected = (ack_expected+1)%(MAX_SEQ+1);;
			}
			cout<<"piggybacked data from b is : "<<endl;
			to_NL(&f.info);
		break;
		case network_layer_ready :
			from_NL(&buffer[next_frame_to_send]);
			cout<<"Buffer filled upto "<<nbuffered<<endl;
			nbuffered++;
			s.info=buffer[next_frame_to_send];
			s.seq_no=next_frame_to_send;
			to_PL_A(&s);
			next_frame_to_send=(next_frame_to_send+1)%(MAX_SEQ+1);
		break;
		case timeout :
			for(j=ack_expected;j<nbuffered;){
				frame s;
				s.info=buffer[j];
				s.seq_no=j;
				to_PL_A(&s);
				j=(j+1)%(MAX_SEQ+1);
			}
		}
		if(nbuffered<MAX_SEQ)
			enable_NL(&event);
		else{
			disable_NL();
			if(error==true)
				event=timeout;
			else
				event=frame_arrival;
		}
	}
}

int main(){
	srand(0);
	A();
	return 0;
}

