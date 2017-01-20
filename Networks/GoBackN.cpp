#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
using namespace std;
# define MAX_SIZE 10
# define MAX_SEQ 3
struct packet{
	char data[MAX_SIZE];
};
struct frame{
	packet info;
	int seq_no;
	int ack;
}gdata[MAX_SEQ+1],gdata1;
	int next_frame_to_send;
	int frame_expected=0;
	int i=0,j=0,k=0;
enum event_type{frame_arrival,timeout,checksum,network_layer_ready};
from_NL(packet*p)
{
	cout<<"Enter data";
	cin>>p->data;
}
to_PL_A(frame*f)
{   
	cout<<"A machine sending the data to physical layer(gdata)\n";
	gdata[i]=*f;
	i++;
	i=i%4;

}

from_PL_B(frame*f)
{   
*f=gdata[k];
 k++;
 k=k%4;
}
to_PL_B(frame *d)
{
//	gdata1[j]=*d; // errror
	gdata1=*d;
	//j++;
	//j=j%2;
}


from_PL_A(frame*f)
{   
//*f=gdata1[j-1];  //error
*f=gdata1       ;           

}

to_NL(packet*p)
{    for(int i=0;i<MAX_SIZE;i++)
    cout<<p->data[i];
    cout<<endl;
}
wait_for_event_reciever(event_type *e){
	
	*e=frame_arrival;
	
}
	B()
	{  cout<<"Entered B"<<endl;
		frame r,d;
		
		event_type event;
		packet buffer;
		wait_for_event_reciever(&event);
		if(event==frame_arrival)
		{
			from_PL_B(&r);
			if(r.seq_no==frame_expected)
			{    
				frame_expected++;
				frame_expected=frame_expected%3;     //% 3 than 4
				cout<<"Data "<<r.seq_no<<"sent by A ,recieved at B is"<<endl;
				to_NL(&r.info);	
			}
		cout<<"enter piggbacked data to send at A"<<endl;
		from_NL(&buffer);
		d.info=buffer;
		d.ack=frame_expected-1;
		cout<<"sending piggybacked frame"<<endl;
		to_PL_B(&d);
		
	}
}
	
enable_NL(event_type *e)
{
	*e=network_layer_ready;
}
disable_NL()         
{
	B(); 
}

A()
{

	int ack_expected;       //no use
	int frame_expected;        //no use
	frame f,s;
	packet buffer[MAX_SEQ+1];
	int nbuffered;
	event_type event;
	enable_NL(&event);
	ack_expected=0;
	next_frame_to_send=0;
//	frame_expected=0;    //no use
	nbuffered=0;
	while(true)
	{
		switch(event)
		{
			case frame_arrival:
				cout<<"piggybacked frame from b recieved"<<endl;
				from_PL_A(&f);
			//	if(f.ack==ack_expected)
			//	{
				nbuffered--;
				ack_expected++;
			//	}
				
				
				cout<<"piggybacked data from b is"<<endl;
				to_NL(&f.info);
				
				break;
			
			case network_layer_ready:
				from_NL(&buffer[next_frame_to_send]);
				cout<<"Buffered filled upto number"<<nbuffered<<endl;
				nbuffered++;
				cout<<endl;
				s.info=buffer[next_frame_to_send];
				s.seq_no=next_frame_to_send;
				to_PL_A(&s);
				next_frame_to_send++;
				next_frame_to_send=next_frame_to_send%3;  // %3 or 4?
				break; 
				 
			
		}
	
	
	if(nbuffered<MAX_SEQ)
		enable_NL(&event);
		
		else{
	
		disable_NL();
		       
		event=frame_arrival;        
	
			
			
	}
}

}

	
	
int main()
	{ 
	
		A();
	}
	
