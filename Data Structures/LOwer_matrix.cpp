#include<iostream>
using namespace std;


template <typename T>
class Lower{
private :
    int row;
    int size=0;
    T *arr;
public :
    Lower(int n){
        row=n;
        for(int i=1;i<=row;i++){
            size += i;
        }
        arr=new T[size];
    }
    Lower(const Lower& L){
        row = L.row;
        for(int i=0;i<=row;i++){
            size += i;
        }
         arr=new T[size];
    }
     T getval(int i,int j) {
        if(i<1 || j<1 || i>row || j>row) throw "Out of Bounds";
        if(i>=j){
                return arr[(i*(i-1))/2+j-1];
        }
        if(i<j) {
            return 0;
        }
    }
     void setval(int i,int j,T el) {
        if(i<1 || j<1 || i>row || j>row) throw "Out of Bounds";
        if(i>=j){
            arr[(i*(i-1))/2+j-1] = el;
        }
        else if(el!=0) throw "elements must be 0 for i<j";

    }
    friend ostream& operator<<(ostream& out,Lower& l) {
        for(int i=0;i<l.size;i++) {
            out<<l.arr[i]<<"  ";
        }
        return out;
    }
    ~Lower() {
        delete arr;
    }

};
int main(){
    try{
        Lower<int> l(3);
        l.setval(1,1,9);
        l.setval(2,1,8);
        l.setval(2,2,10);
        l.setval(3,1,14);
        l.setval(3,2,6);
        l.setval(3,3,2);

        cout<<"GET VALUE : "<<l.getval(2,2)<<endl;
        cout<<l;
        l.setval(1,3,8);
    }
    catch (const char* msg) {
        cerr << msg << endl;
    }
return 0;
}
