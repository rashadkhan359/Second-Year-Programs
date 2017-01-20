//  SELECTIVE REPEAT PROTOCOL

#include <iostream>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
using namespace std;
#define MAX_SEQ 3
#define NR_BUFS ((MAX_SEQ+1)/2)
#define TOT_PACKETS 5
#define inc(k) if(k<MAX_SEQ) k++; else k=0;

//typedef enum{true,false}bool;

bool no_nak=true;

typedef struct
{
 int data;
}packet;

typedef enum{ack,data,nak} frame_kind;

typedef struct
{
 int seq;
 int ack;
 frame_kind kind;
 packet info;
 }frame;

frame DATA,DATA1;

typedef enum{frame_arrival,timeout,error,network_layer_ready,ack_timeout} event_type;




class station
{
 public:
 int i;           //Data to be sent by sender
 int DISCONNECT;
 frame r,s;
 packet buffer[MAX_SEQ+1];
 int frame_to_send,frame_expected,ack_expected;
 int nbuffered,too_far;
 packet out_buf[NR_BUFS];
 packet in_buf[NR_BUFS];
 bool arrived[NR_BUFS];
 event_type event;
 station()
 {
  DISCONNECT=0;
  i=1;
  frame_to_send=0;
  frame_expected=0;
  ack_expected=0;
  nbuffered=0;
  enable_network_layer();
  too_far=NR_BUFS;
  }
  void protocol();
  void from_network_layer(packet *);
  void to_network_layer(packet *);
  void to_physical_layer(frame *);
  void from_physical_layer(frame *);
  void wait_for_event(event_type *);
  void enable_network_layer();
  void disable_network_layer();
  bool between(int a,int b,int c);
  void send_data(frame_kind fk,int frame_nr,int frame_expected,packet buffer[]);

 };




int main()
{
station s1;
 int x=0;
 while(x<NR_BUFS)
   {
	s1.arrived[x]=true;
	x++;
	}

 while(1)
 {
	 s1.protocol();
	 delay(400);
	 if((s1.DISCONNECT==1))
	 break;
	  }
 return 0;
}




void station::protocol()
{

 wait_for_event(&event);

	switch(event)
	{

	 case network_layer_ready:

	  from_network_layer(&out_buf[frame_to_send%NR_BUFS]);
	  nbuffered++;
	  //send_data(frame_to_send,frame_expected,buffer);
	  send_data(data,frame_to_send,frame_expected,out_buf);

	  cout<<"  frame send:"<<frame_to_send;
	  inc(frame_to_send);
	  break;

	  case frame_arrival:

		from_physical_layer(&r);
		if(r.kind==data)
		{
		 if((r.seq!=frame_expected)&& no_nak)
			send_data(nak,0,frame_expected,out_buf);
		 if(between(frame_expected,r.seq,too_far)&&(arrived[r.seq%NR_BUFS]==false))
		 {
		  arrived[r.seq%NR_BUFS]=true;
		  in_buf[r.seq%NR_BUFS]=r.info;
		  while(arrived[frame_expected%NR_BUFS])
		  {
		   to_network_layer(&in_buf[frame_expected%NR_BUFS]);
		   no_nak=true;
		   arrived[frame_expected%NR_BUFS]=false;
		   inc(frame_expected);
		   //start_timer();
		   }
		  }
		 }
		if((r.kind==nak) && between(ack_expected,((r.ack+1)%(MAX_SEQ+1)),frame_to_send))
		  send_data(data,(r.ack+1)%(MAX_SEQ+1),frame_expected,out_buf);


		  while(between(ack_expected,r.ack,frame_to_send));
		   {
			nbuffered--;
			//stop_timer(ack_expected%NR_BUFS);
			i++;
			inc(ack_expected);
			}

		  break;


		  case error:
			 if(no_nak)
			  send_data(nak,0,frame_expected,out_buf);

			 break;

	   /*	 case timeout:
			  send_data(data,oldest_frame,frame_expected,out_buf);
			 break;*/

		 case ack_timeout:
			  {
			   cout<<"\nacknowledgement timeout...";
			   send_data(ack,0,frame_expected,out_buf);
			   }
		}



		/*if(nbuffered<NR_BUFS)
		   enable_network_layer();
		 else
		   disable_network_layer();*/

/*		if(r.ack==frame_to_send)
		 {
		  cout<<"\nstation:"<<st_no<<"..ack received";
		  from_network_layer(&buffer);
		  inc(frame_to_send);
		  i++;

			}*/





   /*		 while(between(ack_expected,r.ack,frame_to_send))
		 {
		  nbuffered--;
		  i++;
		  cout<<"\nacknowledgement number:"<<ack_expected<<" received";
		  inc(ack_expected);
		  }
		  break;


		  case error:
			 break;

		 case timeout:
			 frame_to_send=ack_expected;
			 cout<<"\ntimeout...resending frames..\n";
			 for(i=1;i<=nbuffered;i++)
			 {
			  cout<<"  sending frame:"<<frame_to_send;
			  send_data(frame_to_send,frame_expected,buffer);
			  inc(frame_to_send);
			  }
		   }       */

		if(nbuffered<MAX_SEQ)
		   enable_network_layer();
		 else
		   disable_network_layer();


		 if(i>TOT_PACKETS)          //if all packets recieved then disconnect
		  {
			DISCONNECT = 1;
			 cout<<"\nDISCONNECTED:";
			  return;
			}

 }



bool station::between(int a,int b,int c)
{
  if( ((a<=b)&&(b<c)) || ((c<a)&&(a<=b)) || ((b<c)&&(c<a)) )
  return true;
 else
   return false;
  }



void station::enable_network_layer()
{
 event=network_layer_ready;
 }


void station::disable_network_layer()
{
  event=frame_arrival;
  }


void station::send_data(frame_kind fk,int frame_nr,int frame_expected,packet buffer[])
{
 frame s;
 s.kind=fk;
 if(fk==data)
 s.info=buffer[frame_nr%NR_BUFS];
 s.seq=frame_nr;
 s.ack=(frame_expected+MAX_SEQ)%(MAX_SEQ+1);
 if(fk==nak)
  no_nak=false;
 to_physical_layer(&s);

 //if(fk==data)
 //start_timer(frame_nr%NR_BUFFS);
 //stop_ack_timer();

 }


/*void station::send_data(int frame_nr,int frame_expected,packet buffer[])
{
 frame s;
 s.info=buffer[frame_nr];
 s.seq=frame_nr;
 s.ack=(frame_expected+MAX_SEQ)%(MAX_SEQ+1);
 to_physical_layer(&s);
 }*/


void station::from_network_layer(packet *buffer)
{
	(*buffer).data = i;
 }



void station::to_physical_layer(frame *s)
{
 DATA1=*s;
 }


void station::to_network_layer(packet *buffer)
{

  if((*buffer).data==0)
  cout<<" new packet received";
  else
  cout<<"  Packet "<<(*buffer).data<<" recieved , Ack Sent";

}


void station::from_physical_layer(frame *buffer)
{
  *buffer = DATA;
 (*buffer).seq=frame_expected;
  (*buffer).ack=ack_expected;//ack_expected;
}


void station::wait_for_event(event_type * e)
{
   int r;

   if(*e==network_layer_ready)
	return;
   else
   {

	int x=rand()%5;
	if(x%2==0)
	 *e=frame_arrival;
	else
	 *e=ack_timeout;

	}

}



/**********************OUTPUT****************************

  frame send:0  frame send:1  frame send:2  frame send:3  frame send:0
acknowledgement timeout...  frame send:1
acknowledgement timeout...
acknowledgement timeout...  frame send:2
DISCONNECTED:
***********************************************************/
