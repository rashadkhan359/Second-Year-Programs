#include<iostream>
using namespace std;
#define MAX_NODES 10 /* maximum number of nodes */
#define INFINITY 1000000000 /* a number larger than every maximum path */

int x;
typedef enum {permanent, tentative} active;/* label state */
struct state{ /* the path being worked on */
    int predecessor; /* previous node */
    int length; /* length from source to this node */
    active label ;
}state[MAX_NODES];
//int n, dist[MAX NODES][MAX NODES]; /* dist[i][j] is the distance from i to j */
void dijkstra(int dest, int src,int n, int **dist,int *path,int *final_dist){

    int i, k, min;
    struct state *p;
    for (p=&state[0];p<&state[n];p++) { /* initialize state */
        p->predecessor = -1 ;
        p->length = INFINITY;
        p->label = tentative;
    }

    state[src].length = 0;
    //state[src].label = permanent;
    k = src;                                                          /* k is the initial working node */
    do {                                                            /* Is there a better path from k? */
        for (i=0;i<n;i++){                                          /* this graph has n nodes */
            if(dist[k][i] != -1 && state[i].label == tentative) {
                if (state[k].length + dist[k][i] < state[i].length) {
                    state[i].predecessor = k;
                    state[i].length = state[k].length + dist[k][i];
                }
            }
        }
        /*Find the tentatively labeled node with the smallest label. */
        //k=0;
        min=INFINITY;
        for(i=0;i<n;i++){
            if(state[i].label == tentative && state[i].length < min) {
                min=state[i].length;
                k=i;
            }
        }
        state[k].label = permanent;        /*and make it permanent*/
    }while(k != dest);
    /* Copy the path into the output array. */
    x = 0;
    k = dest;
    *final_dist = state[k].length;
    do{
        path[x++] = k;
        k = state[k].predecessor;
    }while(k>=0);
}


int main(){
    int ver,**G,v1,v2,distance,src,dest,*path,final_dist;
    char more,car;
    cout<<"Enter No. Of Vertices : ";
    cin>>ver;

    path = new int[ver];

    G = new int*[ver];
    for(int i=0;i<ver;i++)
        G[i] = new int[ver];

    for(int i=0;i<ver;i++){
        for(int j=0;j<ver;j++){
            if(i==j)
                G[i][j] = 0;
            else
                G[i][j] = -1;
        }
    }
    G[0][1] = 10;
    G[1][0] = 10;
    G[0][4] = 30;
    G[4][0] = 30;
    G[0][5] = 100;
    G[5][0] = 100;
    G[1][2] = 10;
    G[1][2] = 10;
    G[2][3] = 25;
    G[3][2] = 25;
    G[2][5] = 15;
    G[5][2] = 15;
    G[3][4] = 20;
    G[4][3] = 20;
    G[4][5] = 60;
    G[5][4] = 60;

    for(int i=0;i<ver;i++){
        for(int j=0;j<ver;j++){
            cout<<G[i][j]<<" ";
        }
        cout<<endl;
    }

    do{
        cout<<"Enter Source : ";
        cin>>src;
        cout<<"Enter Destination : ";
        cin>>dest;
        dijkstra(dest,src,ver,G,path,&final_dist);

        cout<<"\n\n\t\t\tDistance is : "<<final_dist<<endl;
        cout<<"\t\t\tPath is :  ";
        for(int i=0;i<x;i++){
            cout<<path[i];
            if(i<(x-1))
                cout<<"<-";
        }
        cout<<"\n\nDo YOu Want More PAths?(y/n)   ";
        cin>>car;
    }while(car=='y' || car=='Y');
    return 0;
}
