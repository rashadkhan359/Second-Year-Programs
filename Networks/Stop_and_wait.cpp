#include<iostream>
#include<stdlib.h>
//#include<unistd.h>
using namespace std;


struct packet{
	string data;
};


struct frame{
	packet info;
	int seq_no;
	bool ack;
	int error;
}ch;


bool turn;
string final_msg = "";
int TIMEOUT = 5,MAX = 1;


typedef enum{frame_arr,frame_ack,chk_err,timeout}event_type;


int increment(int k) {
    if(k<MAX) k++;
    else k=0;
    return k;
}

void wfe_sender(event_type *e){
    static int timer=0;
    if(turn==false){
        timer++;
        if(timer == TIMEOUT){
            *e = timeout;
            cout<<" \n Acknowledgement Not Received at Sender!"<<endl;
            timer = 0;
            return;
        }
        if(ch.error==0){
            *e = chk_err;
        }
        else{
            timer = 0;
            *e = frame_arr;
        }
    }// cout<<"Event set in sender is "<<(*e)<<endl;
}


event_type wfe_reciever(event_type e){
    if(turn == true){
        if(ch.error==0)
            e = chk_err;
        else
            e = frame_arr;
    }
    //cout<<"Event set in receiver is "<<e<<endl;
    return e;
}

packet from_Network_Layer(packet buffer){
    string msg;
    cin>>msg;
    buffer.data = msg;
    return buffer;
}

void to_Physical_Layer(frame s){
    int r = rand()%4;
    //cout<<"Error : "<<r<<endl;
    s.error = r;// probability of error 1/4
    ch = s;
}

frame from_Physical_Layer(){
    return ch;
}

void to_Network_Layer(packet r){
    cout<<"Received : "<<r.data<<endl;
    final_msg = final_msg.append(r.data+" ");
    //final_msg = final_msg.append(" ");
    cout<<"\nMessage till received :  "<<final_msg<<endl;
}

void sender(){
    frame s;
    packet buffer;
    static int frame_to_send = 0;
    event_type event;
    static int flag = 0;
    if(flag==0){
        s.info =  from_Network_Layer(buffer);
        s.seq_no = frame_to_send;
        cout<<"Sending :    DATA - "<<s.info.data <<"    Seq.No. - "<<s.seq_no<<endl;
        to_Physical_Layer(s);
        turn = true;
        flag=1;
        return;
    }
    wfe_sender(&event);
    if(turn == false){
        if(event == frame_arr){
            s.info=from_Network_Layer(buffer);
            frame_to_send=increment(frame_to_send);
            s.seq_no = frame_to_send;
            cout<<"\nSending :    DATA - "<<s.info.data<<"     Seq.No. - "<<s.seq_no<<endl;
            turn =  true;
            to_Physical_Layer(s);
        }
        if(event == timeout){
            cout<<"\n             TimeOUt!.. Resending Frame..."<<endl;
            turn = true;
            to_Physical_Layer(s);
        }
    }
}

void reciever() {
    frame r,x;
    event_type event;
    static int frame_exp = 0;
    event = wfe_reciever(event);
    if(turn==true){
        if(event == frame_arr){
            r = from_Physical_Layer();
            if(r.seq_no==frame_exp){
                to_Network_Layer(r.info);
                frame_exp=increment(frame_exp);
            }
            else{
                cout<<"\nAcknowledgment Resent !"<<endl;
            }
            turn = false;
            to_Physical_Layer(x);
        }
        else if(event == chk_err){
            cout<<"\nGarbled Frame!!!."<<endl;
            turn = false;
        }
    }
}
int main(){
    srand(0);
cout<<"Enter The Message : ";
    while(true){
        sender();
        //delay(1);
        reciever();
    }
	return 0;
}
