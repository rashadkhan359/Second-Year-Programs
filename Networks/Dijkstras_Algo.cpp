#include<iostream>
using namespace std;
#define MAX 10000

int minDis(int dist[],bool dik[],int ver){
    int min = MAX,index;
    for(int i=0;i<ver;i++){
         if(dik[i]==false && dist[i]<=min){
            min = dist[i];
            index =  i;
         }
    }
    return index;
}

void printPath(int p[], int j)
{
    // Base Case : If j is source
    if (p[j]==-1)
        return;

    printPath(p, p[j]);
    cout<<j<<" ";
}

int print(int dist[], int ver, int p[],int src){
    cout<<"Vertex\t    Distance\t      Path"<<endl;
    for (int i = 0; i<ver; i++){
        if(i!=src){
            cout<<"\n"<<src<<" to "<<i<<"\t\t"<<dist[i]<<"\t\t"<<src<<" ";
            printPath(p,i);
        }
    }
}

void dijkstra(int start,int ver,int **G){
    int dist[ver],p[ver];
    bool dik[ver];

    for(int i=0;i<ver;i++){
        p[i] = -1;
        dist[i] = MAX;
        dik[i] = false;
    }

    dist[start] = 0;

    for(int a=0;a<ver-1;a++){
        int spt = minDis(dist,dik,ver);

        dik[spt] = true;

        for(int v=0;v<ver;v++){
            if(dik[v]==false && G[spt][v]  && (dist[spt]+G[spt][v]<dist[v])){
                p[v] = spt;
                cout<<"p["<<v<<"] = "<<p[v]<<endl;
                dist[v] = dist[spt] + G[spt][v];
                cout<<"dist["<<v<<"] = "<<dist[v]<<endl;
            }
        }
    }
    print(dist,ver,p,start);
}

int main(){
    int ver,**G,v1,v2,distance,src;
    char more,car;
    cout<<"Enter No. Of Vertices : ";
    cin>>ver;
    G = new int*[ver];

    for(int i=0;i<ver;i++)
        G[i] = new int[ver];

    for(int i=0;i<ver;i++){
        for(int j=0;j<ver;j++){
            G[i][j] = 0;
        }
    }

    cout<<"\tEnter Distances in the order as (vertex1,vertex2,distance) "<<endl;
label : do{
        cin>>v1>>v2>>distance;
        if(v1<0 || v1>ver-1 && v2<0 || v2>ver-1){
            cout<<"Dhyaan Se Bhai! Try Again"<<endl;
            goto label;
        }
        if(v1==v2){
            cout<<"Distance Can't be more than 0, coz Same!";
            goto label;
        }
        G[v1][v2] = distance;
        G[v2][v1] = distance;
        cout<<"Do You want to Enter More?(y,n) ";
        cin>>more;
    }while(more=='y' || more=='Y');

    for(int i=0;i<ver;i++){
        for(int j=0;j<ver;j++){
            cout<<G[i][j]<<" ";
        }
        cout<<endl;
    }

    do{
        cout<<"Enter Your Source : "<<endl;
        cin>>src;
        dijkstra(src,ver,G);
        cout<<"Do YOu Want More PAths?(y/n)";
        cin>>car;
    }while(car=='y' || car=='Y');
    return 0;
}
