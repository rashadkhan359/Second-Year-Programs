#include<iostream>
using namespace std;


template <class T>
class Array1D
{
    T *arr;
    int size;
public:
        Array1D(int s=0)
        {
            if(s<=0)
                throw " Invalid Size \n";
            arr=new T[s];
            size=s;
        }
        ~Array1D()
        {
            delete []arr;
        }
        Array1D(const Array1D &b)
        {
            size=b.size;
            arr=new T[size];
            for(int i=0;i<size;i++)
              arr[i]=b[i];
        }
        int& operator[](int i) const
        {
            if(i<0 || i>=this->size)
                throw "Out Of Bounds\n";
            return arr[i];
        }


        Array1D operator-(){
            Array1D temp(size);
            for(int i=0;i<size;i++)
                temp[i]=-(*this)[i];
            return temp;
        }

        Array1D operator=(const Array1D &b){
            if(size!=b.size){
                delete []arr;
                size=b.size;
                arr=new T[size];
            }
            for(int i=0;i<size;i++)
                arr[i]=b[i];
            return *this;
        }
        bool operator==(const Array1D &b)
        {
           bool res=true;
           if(size!=b.size)
                res=false;
           for(int i=0;i<size;i++)
            if(arr[i]!=b[i])
              {
                  res=false;
                  break;
              }
           return res;
        }
        Array1D operator+(const Array1D &b)
        {
            if(this->size!=b.size)
                throw " Add Operation Not Applicable\n";
            Array1D temp(b.size);
            for(int i=0;i<size;i++)
                temp[i]= (*this)[i] + b[i];
            return temp;
        }

        Array1D operator-(const Array1D &b)
        {
            if(this->size!=b.size)
                throw " Subtract Operation Not Applicable \n";
            Array1D temp(b.size);
            for(int i=0;i<size;i++)
                temp[i]= (*this)[i] - b[i];
            return temp;
        }

        Array1D operator*(const Array1D &b){
          if(this->size!=b.size)
                throw " Multiply Operation Not Applicable\n";
          Array1D temp(b.size);
          for(int i=0;i<size;i++)
                temp[i]= (*this)[i]*b[i];
          return temp;
        }

    friend istream& operator>>(istream &in, Array1D<T> &b){
        for(int i=0;i<b.size;i++)
            in>>b[i];
        return in;
    }
    friend ostream& operator<<(ostream &out, Array1D<T> &b){
        for(int i=0;i<b.size;i++)
            out<<b[i]<<" ";
        return out;
    }
};


int main()
{
    int n;
    char ch;
    try{
    do{
        cout<<"\nEnter the size of first array : ";
        cin>>n;
        Array1D<int> A(n);
        cout<<"\nEnter the elements of first array \n";
        cin>>A;
        cout<<"\nEnter the size of second array : ";
        cin>>n;
        Array1D<int> B(n);
        cout<<"\nEnter the elements of second array \n";
        cin>>B;
        Array1D<int> C(n);
        cout<<"\nArithmetic Operations Available Are \n1. Addtion \n2. Subtraction \n3. Multiply\n4. Assignment\n5. Equality\n6. Negation \n\nEnter Your Choice : ";
        cin>>n;
        switch(n)
        {
            case 1: {
                      C=A+B;
                      cout<<"\nThe Sum Is : ";
                      cout<<C;
                      break;
                    }
            case 2: {
                      C=A-B;
                      cout<<"\nDifference Is : ";
                      cout<<C;
                      break;
                    }
            case 3: {
                      C=A*B;
                      cout<<"\n Product Is : ";
                      cout<<C;
                      break;
                    }
            case 4: {
                      A=B;
                      cout<<"\nThe First Array After Assignment Is : ";
                      cout<<A;
                      break;
                    }
            case 5: {
                      if(A==B)
                        cout<<"\nThe Arrays Are Equal......\n";
                      else
                        cout<<"\nThe Arrays Are Not Equal !!!!!!\n";
                      break;
                    }
            case 6: {
                      Array1D<int> C=-A;
                      cout<<"\nThe Negation Of First Array Is : ";
                      cout<<C;
                      C=-B;
                      cout<<"\n\nThe Negation Of Second Array Is : ";
                      cout<<C;
                      break;
                    }
            default : cout<<"\nYou Entered A Wrong Choice !!!!!";
                        break;
        }
        cout<<"\n\nDo You Want To Continue 'y' or 'Y' for yes and 'n' or 'N' for no : ";
        cin>>ch;
    }while(ch=='y' || ch=='Y');
    }
    catch(const char* msg)
    {
        cout<<msg<<endl;
    }
    return 0;
}
