=#include<iostream>
using namespace std;


template <typename T>
class Upper{
private :
    int row;
    int size=0;
    T *arr;
public :
    Upper(int n){
        row=n;
        for(int i=0;i<=row;i++){
            size += i;
        }
        arr=new T[size];
    }
    Upper(const Upper& L){
        row = L.row;
        for(int i=0;i<=row;i++){
            size += i;
        }
         arr=new T[size];
    }
     T getval(int i,int j) {
        if(i<1 || j<1 || i>row || j>row) throw "Out of Bounds";
        else if(i>j) return 0;
        else return arr[(j*(j-1))/2+i-1];
     }

     void setval(int i,int j,T el) {
        if(i<1 || j<1 || i>row || j>row) throw "Out of Bounds";
        if(i<=j){
            arr[(j*(j-1))/2+i-1] = el;
        }
        else if(el!=0) throw "elements must be 0 for i>j";
    }
    friend ostream& operator<<(ostream& out,Upper& l) {
        for(int i=0;i<l.size;i++) {
            out<<l.arr[i]<<"  ";
        }
        return out;
    }
    ~Upper() {
        delete arr;
    }

};
int main(){
    try{
        Upper<int> l(3);
        l.setval(1,1,9);
        l.setval(2,2,8);
        l.setval(2,3,10);
        l.setval(1,2,14);
        l.setval(1,3,6);
        l.setval(3,3,2);

        cout<<"GET VALUE : "<<l.getval(2,2)<<endl;
        cout<<"Printing Column-wise : \n"<<l<<endl;;
        l.setval(3,2,0);
        l.setval(3,1,8);

    }
    catch (const char* msg) {
        cerr << msg << endl;
    }
return 0;
}

