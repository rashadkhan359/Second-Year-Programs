 #include<iostream>
using namespace std;

template <typename T>
void inser(T arr[],int size){
    for(int i=1,j;i<size;i++){
        T temp =  arr[i];
        for(j=i;j>0 && temp<arr[j-1];j--){
            arr[j]=arr[j-1];
        }
        arr[j] = temp;
    }
}

template <typename T>
void MergeSort(T *left,int nL ,T *right,int nR, T *array,int size){
    int i = 0, j = 0, k = 0;
    while(i<nL && j<nR){
        if(left[i]<=array[i]){
            array[k] = left[i];
            i = i+1;
        }
        else{
            array[k] = right[j];
            j = j+1;
        }
        k = k+1;
    }
    while(i<nL){
        array[k] = left[i];
        k = k+1;
        i = i+1;
    }
    while(j<nR){
        array[k] = left[j];
        k = k+1;
        j = j+1;
    }
}

template <typename T>
void Merge(T* array,int size){
    if(size<2)
        return;

    int mid = size/2;

    T *left = new T[mid], *right = new T[size - mid];

    for(int i=0;i<mid;i++)
        left[i] = array[i];
    for(int i=mid;i<size;i++)
        right[i-mid] = array[i];

    Merge(left,mid);
    Merge(right,size-mid);
    MergeSort(left,mid,right,size-mid,array,size);
}

template <typename T>
void selection(T arr[],int size){
    for(int j=0;j<size-1;j++){
        T min=arr[j];
        int index = j;
        for(int i=j+1;i<size;i++){
            if(arr[i]<min){
                index = i;
                min = arr[i];
            }
        }
        swap(arr[index],arr[j]);
    }
}

template <typename T>
void bubble(T arr[],int size){
    for(int i=0;i<size;i++){
        for(int j=0;j<size-1;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }
    }
}
template <typename T>
void Logic(T arr[],int size){
    bool flag = false;
    cout<<"Enter the elements : "<<endl;
    for(int i=0;i<size;i++){
        cin>>arr[i];
    }
    do{
        int s;
        cout<<"Select The Sorting Algo. : \n1.Insertion\n2.Selection\n3.Bubble\n4.Merge\n"<<endl;
        cin>>s;
        switch(s){
        case 1:
            inser(arr,size);
            cout<<"Sorted Array using Insertion Sort : ";
            for(int i=0;i<size;i++){
                cout<<arr[i]<<" ";
            }
            flag = false;
            break;
        case 2 :
            selection(arr,size);
            cout<<"Sorted Array using Selection Sort : ";
            for(int i=0;i<size;i++){
                cout<<arr[i]<<" ";
            }
            flag = false;
            break;
        case 3 :
            bubble(arr,size);
            cout<<"Sorted Array using Bubble Sort  : ";
            for(int i=0;i<size;i++){
                cout<<arr[i]<<" ";
            }
            flag = false;
            break;
        case 4:
            Merge(arr,size);
            cout<<"Sorted Array using Merge Sort  : ";
            for(int i=0;i<size;i++){
                cout<<arr[i]<<" ";
            }
            flag = false;
            break;
        default :
            cout<<"Please Choose From Above Algos Only !."<<endl;
            flag = true;
            break;
        }
    }while(flag == true);
}
int main(){
    int size,choice;
    bool flag=false;
    char x;
    do{
        cout<<"Enter the size of array : ";
        cin>>size;
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
        cout<<"\n\nDo You Want To continue?(y/n)"<<endl;
        cin>>x;
    }while(x=='y');

}
