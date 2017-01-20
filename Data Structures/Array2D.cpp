#include<iostream>
using namespace std;

template <class T>
class Array1D{
private :
    int size;
    T *arr;
public :
    Array1D(int s=0){
        if(s<0) throw "Invalid Size";
        if(s==0){
            size =0;
            arr= NULL;
        }
        else{
            arr = new T[s];
            size = s;
        }
    }

    Array1D(const Array1D& A){
        if(A.size<=0) throw "Invalid Size2";
        size = A.size;
        arr = new T[size];
        for(int i=0;i<size;i++){
            arr[i] = A[i];
        }
    }

    T& operator[](int index){
            if(index<0 || index>size) throw "Index Out Of Bound.";
            return arr[index];
    }
    void resize(int t){
        if(t<=0) throw "Invalid Size";
        delete []arr;
        size = t;
        arr = new T[t];
    }
    ~Array1D(){
        delete []arr;
    }

};

template <class T>
class Array2D {
    int row;
    int col;
    Array1D<T>* arr2;
public :
    Array2D(int r=0,int c=0){
        if(r<0 && c<0) throw "Row And Column Size Must Be Greater Than 0";
        if(r==0 || c==0){
            row=col=0;
            arr2=NULL;
        }
        row = r;
        col = c;
        arr2 = new Array1D<T>[row];
        for(int i=0;i<row;i++){
            arr2[i].resize(col);
        }
    }
    Array2D(const Array2D& A){

        if(A.row<=0 && A.col<=0) throw "Row And Column Size Must Be Greater Than 0";
        row = A.row;
        col = A.col;
        arr2 = new Array1D<T>[row];
        for(int i=0;i<row;i++){
            arr2[i].resize(col);
        }
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                this->arr2[i][j] = A.arr2[i][j];
            }
        }
    }
    ~Array2D(){
        delete [] arr2;
    }

    Array1D<T>& operator[](int index) const{
        if(index<0 || index>=row) throw "Index Out Of Bound.\n";
        return arr2[index];
    }

    Array2D<T> operator=(const Array2D<T> &B){
        if(row!=B.row || col!=B.col){
            delete [] arr2;
            row=B.row;
            col=B.col;
            arr2=new Array1D<T>[row];
            for(int i=0;i<row;i++)
                arr2[i].resize(col);
             }
             for(int i=0;i<row;i++)
                for(int j=0;j<col;j++)
                  this->arr2[i][j]=B.arr2[i][j];
             return (*this);
    }

    Array2D operator+(const Array2D &B){
        if(row!=B.row || col!=B.col) throw " Can't Add\n";
             Array2D temp(B);
             for(int i=0;i<row;i++)
                for(int j=0;j<col;j++)
                       temp.arr2[i][j]=this->arr2[i][j] + B.arr2[i][j];
             return temp;
    }

    Array2D operator-(const Array2D &B){
        if(row!=B.row || col!=B.col) throw "Can't Subtract\n";
        Array2D temp(B);
        for(int i=0;i<row;i++)
            for(int j=0;j<col;j++)
                temp.arr2[i][j]=this->arr2[i][j] - B.arr2[i][j];
             return temp;
         }
         Array2D operator*(const Array2D &B)
         {
             if(col!=B.row)
                throw " Multiply Operation Not ApplicaBle !!!!!!\n";
             Array2D temp(row,B.col);
             for(int i=0;i<row;i++)
                for(int j=0;j<B.col;j++)
                  {
                      temp.arr2[i][j]=0;
                      for(int k=0;k<col;k++)
                      temp.arr2[i][j]+=this->arr2[i][k] * B.arr2[k][j];
                  }
             return temp;
         }

    friend istream& operator>>(istream& in, Array2D& a){
        for(int i=0;i<a.row;i++){
            for(int j=0;j<a.col;j++){
                in>>a.arr2[i][j];
            }
        }
        return in;
    }


    friend ostream& operator<<(ostream& out, Array2D& a){
        for(int i=0;i<a.row;i++){
            for(int j=0;j<a.col;j++){
                out<<a.arr2[i][j]<<" ";
            }
            cout<<endl;
        }
        return out;
    }

};

int main(){
    int rows,cols,c;
    char ch;
    bool flago = false;
    try{
        cout<<"Enter the Rows Of First Matrix : ";
        cin>>rows;
        cout<<"Enter the Columns Of First Matrix : ";
        cin>>cols;
        Array2D<int> A(rows,cols);
        cout<<"Enter The Elements of First Matrix : "<<endl;
        cin>>A;
        cout<<"Enter the Rows Of Second Matrix : ";
        cin>>rows;
        cout<<"Enter the Columns Of Second Matrix : ";
        cin>>cols;
        Array2D<int> B(rows,cols);
        cout<<"Enter The Elements of Second Matrix : "<<endl;
        cin>>B;
        Array2D<int> C;
        do{
            cout<<"\n\nChoose From Below : \n1.Addition.\n2.Subtraction.\n3.Multiplication.\n";
            do{
                cout<<"Enter : ";
                cin>>c;
                switch(c){
                case 1: C =A+B;
                    cout<<"THe Sum Is : "<<endl;
                    cout<<C;
                    flago=false;
                    break;
                case 2:{
                    int x;
                    bool flagi=false;
                    cout<<"Select : \n1. A-B\n2. B-A"<<endl;
                    do{
                        cout<<"Enter Choice : ";
                        cin>>x;
                        switch(x){
                        case 1: C =A-B;
                            cout<<"THe Subtracted Matrix Is : "<<endl;
                            cout<<C;
                            flagi = false;
                            break;
                        case 2: C =B-A;
                            cout<<"THe Subtracted Matrix Is : "<<endl;
                            cout<<C;
                            flagi = false;
                            break;
                        default :
                            cout<<"------------Please Enter '1' or '2' !-------------"<<endl;
                            flagi = true;
                            break;
                        }
                    }while(flagi==true);
                }
                    flago=false;
                    break;
                case 3: C =A*B;
                    cout<<"THe Multiplication Is : "<<endl;
                    cout<<C;
                    flago = false;
                    break;
                default : cout<<"------------Please Choose From Above Options Only!-------------"<<endl;
                        flago = true;
                    break;

                }
            }while(flago==true);
            cout<<"Do You Want To Continue?(y/n)"<<endl;
            cin>>ch;
        }while(ch=='y');
    }
    catch(const char* msg){
        cout<<msg<<endl;
    }
}
