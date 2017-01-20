#include<iostream>
using namespace std;

class schedule{
    int p;
    int *Bt, *At, *Wt, *Tt, *Ft;

public :
    void Entry(){
        cout<<"Enter no. of Total Programs : ";
        cin>>p;
        Bt = new int[p];
        At = new int[p];
        Wt = new int[p];
        Tt = new int[p];
        Ft = new int[p];
        for(int i=0;i<p; i++){
        cout<<"Enter Burst time for P"<<i+1<<" : ";
        cin>>Bt[i];
        cout<<"Enter Arrival time for P"<<i+1<<" : ";
        cin>>At[i];
        }
    }

    void display(){
    cout<<"\n\n Burst Time\t\t\t\t ARRIVAL Time\n"<<endl;
        for(int i=0;i<p;i++){
                cout<<" P"<<i+1<<" = "<<Bt[i]<<"\t\t\t\t\t   P"<<i+1<<" = "<<At[i]<<endl;
        }
    }

    void sortt(){
        int min_index=0;
        for(int i=1;i<p;i++){
            if(At[i]<At[min_index]){
                swap(At[i],At[min_index]);
                min_index = i;
            }
        }
    }
    void finish(){
        int O=0;
        cout<<"\n\n FINISH Time\n"<<endl;
        for(int i=0;i<p;i++){
            Ft[i] = O + Bt[i];
            cout<<"P"<<i+1<<" = "<<Ft[i]<<endl;
            O = Ft[i];
        }
    }

    void waiting(){
        float sum = 0;
        cout<<"\n\n Waiting Time\n"<<endl;
        for(int i=0;i<p;i++){
                Wt[i] = Ft[i] - Bt[i] - At[i];
            cout<<" P"<<i+1<<" : "<<Wt[i]<<endl;
            sum = sum + Wt[i];
        }
        float av = sum/p;
        cout<<"\nAverage Waiting Time = "<<av<<endl;
    }

    void turnaround(){
    float sum =0;
    cout<<"\n\n TurnAround Time\n"<<endl;
        for(int i=0;i<p;i++){
                Tt[i] = Ft[i] - At[i];
            cout<<" P"<<i+1<<" : "<<Tt[i]<<endl;
            sum = sum + Tt[i];
        }
        float av = sum/p;
        cout<<"\nAverage Waiting Time = "<<av<<endl;
    }
};
int main(){
    schedule S;
    S.Entry();
    S.display();
    S.sortt();
    S.finish();
    S.waiting();
    S.turnaround();
 return 0;
}
