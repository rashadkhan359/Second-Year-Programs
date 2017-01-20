#include<iostream>
using namespace std;


struct Processes{
    int data;
    int hole;
    bool flag = true;
};

void sort(int *Hole,int size_H,int c){
    if(c==2){
        for(int i=0;i<size_H;i++){
            for(int j=i+1;j<size_H;j++){
                if(Hole[i]>Hole[j]){
                    swap(Hole[i],Hole[j]);
                }
            }
        }
    }
    else if(c==3){
        for(int i=0;i<size_H;i++){
            for(int j=i+1;j<size_H;j++){
                if(Hole[i]<Hole[j]){
                    swap(Hole[i],Hole[j]);
                }
            }
        }
    }
}

void Fit_Algo(int size_H,int size_P,int *Hole,Processes Pro[],int c){
    int z=0;
    while(z<size_P){
        sort(Hole,size_H,c);
        for(int j=0;j<size_H;j++){
            if(Pro[z].data<=Hole[j] && Pro[z].flag==true){
                Pro[z].hole = Hole[j];
                Hole[j] = Hole[j] - Pro[z].data;
                Pro[z].flag = false;
            }
        }
        z++;
    }
    for(int i=0;i<size_P;i++){
        if(Pro[i].flag==false){
            cout<<Pro[i].data<<"K is put in "<<Pro[i].hole<<" partition."<<endl;
        }
        else{
            cout<<Pro[i].data<<"K must wait"<<endl;
        }
    }
}

int main(){
    int size_H,size_P, *Hole;
    //Fit F;
    cout<<"Enter the no. of holes: ";
    cin>>size_H;
    Hole = new int[size_H];
    cout<<"Enter sizes of Holes : "<<endl;
    for(int i=0;i<size_H;i++){
        cin>>Hole[i];
    }
    cout<<"Enter the No. of processes : ";
    cin>>size_P;
    Processes Pro[size_P];
    cout<<"Enter size each of processes:"<<endl;
    for(int j=0;j<size_P;j++){
        cin>>Pro[j].data;
    }
        cout<<"Select Allocation Algorithm : \n 1. First Fit\n 2. Best Fit\n 3. Worse Fit\n";
        int c;
        cin>>c;
        switch(c){
        case 1:
            Fit_Algo(size_H,size_P,Hole,Pro,c);
        case 2:
            Fit_Algo(size_H,size_P,Hole,Pro,c);
        break;
        case 3:
            Fit_Algo(size_H,size_P,Hole,Pro,c);
        break;
        default :
            cout<<"Try Again with Above Input Int Values Only "<<endl;
        break;
        }

    return 0;
}
