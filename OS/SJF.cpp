#include<iostream>
using namespace std;
int main(){
    int p;
    int *burst, *arrival,*position, *finish, *flag, *wait, *turnaround;
    cout<<"Enter the total no. of Processes : ";
    cin>>p;
    burst = new int[p];
    arrival = new int[p];
    finish = new int[p];
    flag = new int[p];
    wait = new int[p];
    turnaround = new int[p];
    position = new int[p];
    cout<<"Enter the burst times : "<<endl;
    for(int i=0;i<p;i++){
        cout<<"P"<<i+1<<" : ";
        cin>>burst[i];
        position[i] = i+1;
    }

    cout<<"Enter the Arrival Times : "<<endl;
    for(int i=0;i<p;i++){
        cout<<"P"<<i+1<<" : ";
        cin>>arrival[i];
    }

    //flag =0 ---> don't execute
    //flag = 1----> execute
    //flag = -1 ----> finished;
    for(int i=0;i<p;i++){
        flag[i]=0;
        finish[i]=0;
    }

    int min_index =0,temp = -1,temp_address = -100,temp1 = -1;
    int mint = arrival[min_index];
    for(int i=1;i<p;i++){
        if(arrival[i]<mint){
            mint = arrival[i];
            min_index = i;
        }
        if(arrival[i]==mint){
            if(burst[i]<burst[min_index]){
                swap(burst[i],burst[min_index]);
                swap(arrival[i],arrival[min_index]);
                swap(position[i],position[min_index]);
                mint = arrival[i];
                min_index = i;
            }
        }
    }
    cout<<"Minimum Arrival Time : "<<min_index<<endl;
    finish[min_index] = arrival[min_index] + burst[min_index];
    flag[min_index] = -1;
    temp = burst[min_index];
    temp1=temp;

    for(int i=0;i<p;i++){
        for(int j=0;j<p;j++){
            if(arrival[j]<=finish[min_index] && finish[j]==0 ){
                flag[j] = 1;
            }
        }
        for(int l=0;l<p;l++){
            if(flag[l]==1 && finish[l]==0){
                temp=burst[l];
                if(temp<=temp1){
                    temp_address=l;
                    temp1=temp;
                }
            }
        }
        if(flag[temp_address]==1 && finish[temp_address]==0){
            finish[temp_address]= finish[min_index]+burst[temp_address];
            min_index = temp_address;
            flag[temp_address] = -1;
            temp1=1000;
        }
    }

    for(int i=0;i<p;i++){
        wait[i]= finish[i]-(burst[i]+arrival[i]);
        turnaround[i]= wait[i]+burst[i];
    }
    cout<<"Processes      FINISH TIME     WAIT TIME    TurnAROUND TIME" <<endl;
    for(int i=0;i<p;i++){
        cout<<" P"<<position[i]<<" -             "<<finish[i]<<"               "<<wait[i]<<"              "<<turnaround[i]<<endl;
    }
    float avg_wait=0;
    float avg_turn=0;
    for(int i=0;i<p;i++){
        avg_wait+= wait[i];
        avg_turn+= turnaround[i];
    }
    cout<<"\n\nAverage Wait : "<<(avg_wait/p)<<endl;
    cout<<"\n\nAverage TurnAround : "<<(avg_turn/p)<<endl;
    return 0;
}
