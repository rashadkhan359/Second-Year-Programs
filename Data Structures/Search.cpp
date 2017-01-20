#include<iostream>
using namespace std;

template <typename T>
bool check(T arr[],int size){
    for(int i=0;i<size;i++){
        for(int j=i+1;j<size;j++){
            if(arr[i]<=arr[j])
                return true;
            else
                return false;
        }
    }
}

template <typename T>
int l_search(T arr[],int size,T ele){
    int pos=-1;
    for(int i=0;i<size;i++)
        if(arr[i]==ele)
            pos = i;
    return pos;
}

template <typename T>
int b_search(T arr[],int size,T ele){
    int start = 0,end = size-1,mid=0,pos=-1;
    while(start<=end){
        mid = (start+end)/2;
        if(arr[mid]==ele){
            pos = mid;
            break;
        }
        else if(arr[mid]>ele){
            end = mid-1;
        }
        else if(arr[mid]<ele){
            start = mid+1;
        }
    }
    return pos;
}

template <typename T>
void Logic(T arr[],int size){
    T ele;
    cout<<"Enter the elements : ";
    for(int i=0;i<size;i++){
        cin>>arr[i];
    }
    cout<<"Enter the Element To be searched : ";
    cin>>ele;
    if(check(arr,size)==false){
        cout<<"\nARRAY is not sorted.\nPerforming LINEAR Search.!\n";
        if(l_search(arr,size,ele)==-1){
            cout<<"\nElement not Present in the provided array!"<<endl;
        }
        else{
            cout<<"\nThe element is at Index ["<<l_search(arr,size,ele)<<"]."<<endl;
        }
    }
    else{
        cout<<"\nARRAY is sorted.\nPerforming BINARY Search.!\n";
        if(b_search(arr,size,ele)==-1){
            cout<<"\nElement not Present in the provided array!"<<endl;
        }
        else{
            cout<<"\nThe element is at Index ["<<b_search(arr,size,ele)<<"]."<<endl;
        }
    }
}

int main(){
    int size,choice;
    char ch;
    bool flag = false;
    cout<<"Enter the size OF Array : ";
    cin>>size;
    do{
        cout<<"Select Input Data Type.\n1. Integer\n2. Character\n3. Float\n4. Double\n5. String\n";
        do{
            cout<<"Enter Your Choice : ";
            cin>>choice;
            switch(choice){
            case 1:{
                int* arr = new int[size];
                Logic(arr,size);
                flag = false;
                break;
            }
            case 2:{
                char* arr = new char[size];
                Logic(arr,size);
                 flag = false;
                break;
            }
            case 3:{
                float* arr = new float[size];
                Logic(arr,size);
                 flag = false;
                break;
            }
            case 4:{
                double* arr = new double[size];
                Logic(arr,size);
                 flag = false;
                break;
            }
            case 5:{
                string* arr = new string[size];
                Logic(arr,size);
                flag = false;
                break;
            }
            default:
                cout<<"Please Choose From Above Only!"<<endl;
                flag = true;
                break;
            }
        }while(flag==true);
        cout<<"Do You Want To Continue?(y/n)"<<endl;
        cin>>ch;
    }while(ch=='y' || ch=='Y');
    return 0;
}
