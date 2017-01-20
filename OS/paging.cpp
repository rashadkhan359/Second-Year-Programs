#include<iostream>

using namespace std;
	struct process{
		int pid;
		int size;
		int pages;
	};
	struct pageTable{
		int *pgNo,*offset;
	};
	struct mainMem{
		int *phyAdd;
		int *frames;
		bool *occupied=false;
	};
	int noFreeFramesCount(mainMem mm,int n){
		int frmCnt=0;
		for(int i=0;i<n;i++){				//counting no of free frames available{
		if(!mm.occupied[i])
			frmCnt+=1;
        }
	return frmCnt;
	}
int main(){
	int mm_size,f_size;
	int n,frmCnt=0;
	cout<<"Enter the size of main memory - "<<endl;
	cin>>mm_size;
	cout<<"Enter the frame size - "<<endl;
	cin>>f_size;
	mainMem mm;
	int nf=(int)mm_size/f_size;					// nf = no of frames
	mm.frames=new int[nf];
	mm.occupied=new bool[nf];
	cout<<"Enter no of processes you want to enter - "<<endl;
	cin>>n;
	process *p;
	p=new process[n];
	for(int i=0;i<n;i++){
			p[i].pid=i+1;
			cout<<"Enter the size of process "<<i+1<<endl;
			cin>>p[i].size;
			int temp=(int)p[i].size/f_size;			//no of pages required for this process
			temp=(temp>0)?temp:1;
			p[i].pages=temp;
			cout<<"This process requires "<<(p[i].pages)<<" pages !!"<<endl;
    }
	int i,j,track=0;			//track is a traversing variable for main memory
    pageTable pt;				//preparing page table
	pt.offset=new int[n];
	pt.pgNo=new int[n];
	for(i=0;i<n;i++){
		pt.pgNo[i]=i;
		frmCnt=noFreeFramesCount(mm,nf);   //counting no of free frames
		if(p[i].pages<frmCnt){
			cout<<"Frames available for process "<<(i+1)<<endl;
			mm.phyAdd=new int[p[i].pages];
			for(j=track;j<p[i].pages;j++){
					mm.phyAdd[j]=j;
					mm.frames[j]=j;
					mm.occupied[j]=true;
            }
			track=j-1;
			cout<<"track is "<< track<<endl;
			pt.offset[i]=track-1;
		}
		else{
			cout<<"Frames not available for process "<<(i+1)<<endl;
		}
	}
    cout<<"Enter process id and page no to obtain its frame no - "<<endl;
    int id,pno;
    cin>>id>>pno;
    int phyaddr=pt.pgNo[id]*pt.offset[id] + pno;
    cout<<"The allocated frame for process "<<id<<" is - "<<phyaddr;
    return 0;
}
