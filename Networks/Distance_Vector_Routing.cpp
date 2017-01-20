#include<iostream>
using namespace std;
#define MAX_REL 50

struct related_router{
    int main_line;
    int index;
}related_router[MAX_REL];


void DVR(int **table,int t_router,int t_relation,int main_r){
    struct related_router *R;
    cout<<"Enter The Related Routers";
    for(R=&related_router[0];R<&related_router[t_relation];R++)
        cin>>R->main_line;
    cout<<"Enter The Distances of routers :";
     for(int i=0;i<t_router;i++){
        for(int j=0;j<t_relation;j++){
            cout<<"\n\nfrom "<<i<<" to "<<related_router[j].main_line<<endl;
            cin>>table[i][j];
        }
    }
    cout<<"Table : "<<endl;
    for(int i=0;i<t_router;i++){
        for(int j=0;j<t_relation;j++){
            cout<<table[i][j]<<"  ";
        }
        cout<<endl;
    }
    int min[t_router],line[t_router],delay[t_relation];
    cout<<"\n\nEnter The Delays : ";
    for(int i=0;i<t_relation;i++)
        cin>>delay[i];
//------------------Calculating--------//
    for(int i=0;i<t_router;i++){
        int temp = table[i][0];
        line[i] = related_router[0].main_line;
        related_router[i].index=0;
        for(int k=0;k<t_relation;k++){
            if(temp>table[i][k]){
                temp = table[i][k];
                line[i]=related_router[k].main_line;
                related_router[i].index=k;
            }
        }
        min[i] = temp;
    }
    cout<<"Pehle : "<<endl;
    for(int k=0;k<t_router;k++){
        cout<<min[k]<<"   "<<line[k]<<endl;
    }
    for(int i=0;i<t_router;i++){
        int x = related_router[i].index;
        min[i]+=delay[x];
    }

    cout<<"Finale : "<<endl;
    for(int i=0;i<t_router;i++){
        cout<<min[i]<<"   "<<line[i]<<endl;
    }
}


int main(){
    int **table,main_r,t_router,t_relation;
    cout<<"Enter The Total Number Of Routers : ";
    cin>>t_router;
    cout<<"Enter The Total Number Of relations : ";
    cin>>t_relation;
    table = new int*[t_router];
    for(int i=0;i<t_router;i++)
        table[i] = new int[t_relation];

    //table[t_router][t_relation] = {{0,},{},{}
    cout<<"Enter The Router whose table You want to update : ";
    cin>>main_r;
    DVR(table,t_router,t_relation,main_r);
    return 0;
}
