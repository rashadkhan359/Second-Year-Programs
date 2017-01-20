#include<iostream>
using namespace std;

class PSJF{
    int p;
    float avg_wait=0.0,avg_turn=0.0;
    int *burst, *arrival,*position, *finish, *flag, *wait, *turnaround, *remain;
    public :
    void entry(){
        cout<<"Enter the total no. of Processes : ";
        cin>>p;
        burst = new int[p];
        arrival = new int[p];
        finish = new int[p];
        flag = new int[p];
        wait = new int[p];
        remain = new int[p];
        position = new int[p];
        turnaround = new int[p];
        cout<<"Enter the burst times : "<<endl;
        for(int i=0;i<p;i++){
            cout<<"P"<<i+1<<" : ";
            cin>>burst[i];
        }

        cout<<"Enter the Arrival Times : "<<endl;
        for(int i=0;i<p;i++){
            cout<<"P"<<i+1<<" : ";
            cin>>arrival[i];
            position[i] = i+1;
        }
    }

    void sortt(){
        for(int i=0;i<p;i++){
            for(int j=0;j<p-1;j++){
                if(arrival[j+1]<arrival[j]){
                    swap(arrival[j],arrival[j+1]);
                    swap(burst[j],burst[j+1]);
                    swap(position[j], position[j+1]);
                }
                else if(arrival[j+1]==arrival[j]){
                    if(burst[j+1]<burst[j]){
                        swap(arrival[j],arrival[j+1]);
                        swap(burst[j+1],burst[j]);
                        swap(position[j],position[j+1]);
                    }
                }
                else continue;
            }
        }
    }
    void flags(){
        //flag =0 ---> don't execute
        //flag = 1----> execute
        //flag = -1 ----> finished
        for(int i=0;i<p;i++){
            flag[i]=0;
            finish[i]=0;
            wait[i]=0;
        }
        for(int i=0;i<p;i++){
            remain[i] = burst[i];
        }
    }
    int getnext(int time){
        int mint=0;
        for(int i=0;i<p;i++){
            if(flag[i]==0){
                mint = i;
                break;
            }
        }
        for(int j=0;j<p;j++){
            if(remain[j]<remain[mint] && flag[j]==0 &&  arrival[j]<=time){
                mint = j;
            }
        }
        return mint;
    }
    void base(){
        int tota=0,prev=0,next=0;
        for(int i=0;i<p;i++){
            tota = tota+burst[i];
        }
        for(int time=0;time<tota;time++){
            cout<<"Prev : "<<prev<<"    Next : "<<next<<endl;
            prev = next;
            next  = getnext(time);
            remain[next] = remain[next]-1;
            if(remain[next]==0){
                flag[next]=1;
            }
            for(int i=0;i<p;i++){
                if(i!=next && flag[i]==0 && arrival[i]<=time){
                    wait[i]++;
                }
            }
        }
    }
    void printchart(){
        cout<<"PROCESS\t TURNAROUND Time \tWAIT Time \t FINISH Time"<<endl;
        for(int i=0;i<p;i++){
            turnaround[i] = wait[i] + burst[i];
            finish[i] = turnaround[i] + arrival[i];
            cout<<" P"<<position[i]<<"\t\t"<<turnaround[i]<<"\t\t"<<wait[i]<<"\t\t"<<finish[i]<<endl;
        }
    }
    void printavg(){
        float sum1=0,sum2=0;
        for(int i=0;i<p;i++){
            sum1 = sum1+wait[i];
            sum2 = sum2+turnaround[i];
        }
        avg_wait =sum1/p;
        avg_turn = sum2/p;

        cout<<"\n\nAverage Wait : "<<avg_wait<<endl;
        cout<<"\n\nAverage Turn : "<<avg_turn<<endl;
    }
};

int main(){
    PSJF p;
    p.entry();
    p.sortt();
    p.flags();
    p.base();
    p.printchart();
    p.printavg();
    return 0;
}
