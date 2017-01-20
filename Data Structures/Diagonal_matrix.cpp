#include<iostream>
using namespace std;

template <class T>
class Diagonal{
    int size=0;
    T* arr;
public :
    Diagonal(int s=0){
        if(s<=0) throw "Invalid Size";
        size = s;
        arr = new T[size];
    }
    ~Diagonal(){
        delete [] arr;
    }
    Diagonal(const Diagonal &D){
        if(D.size<=0) throw "Invalid Size";
        size = D.size;
        arr = new T[size];
    }
    T get_value(int a,int b){
        if(a<1 || a>size || b<1 || b>size) throw "Out Of Bound.!\n";
        if(a!=b) return 0;
        return arr[a-1];
    }
    void set_value(int a,int b,T ele){
        if(a<1 || a>size || b<1 || b>size) throw "Out Of Bound.!\n";
        if(a!=b && ele!=0) throw "Invalid Value!";
        arr[a-1] = ele;
    }

    friend ostream& operator<<(ostream& out,Diagonal& d) {
        for(int i=0;i<d.size;i++) {
            out<<d.arr[i]<<"  ";
        }
        return out;
    }
};

int main(){
    try{
        Diagonal<int> D(3);
        D.set_value(1,1,3);
        D.set_value(2,2,4);
        D.set_value(3,3,5);
        cout<<D<<endl;
        D.set_value(1,3,0);
        cout<<"Get Value : "<<D.get_value(2,2)<<endl;
        D.set_value(1,2,5);
    }catch(const char* msg){
        cout<<msg<<endl;
    }
    return 0;
}
