#include<iostream>
using namespace std;
class Sym_matrix
{
    int *a;
    int size;
public :
      Sym_matrix(int s)
      {
          if(s<=0)
            throw " Invalid Size....Aborting!!!!! \n";
          size=s;
          int temp=size*(size+1)/2;
          a=new int[temp];
      }
      Sym_matrix(const Sym_matrix &B)
      {
          size=B.size;
          int temp=size*(size+1)/2;
          a=new int[temp];
          for(int i=0;i<temp;i++)
            a[i]=B.a[i];
      }
      int get_value(int i,int j)
      {
          if(i<0 || i>=size || j<0 || j>=size)
            throw " Array Index Out Of Bounds !!!!!!! \n";
          if(i>j)
            get_value(j,i);
          else
          {
              int k=i*(2*size-i-1)/2 + j;
              return a[k];
          }
      }
      void set_value(int i,int j,int val)
      {
          if(i<0 || i>=size || j<0 || j>=size)
            throw " Array Index Out Of Bounds !!!!!!! \n ";
          if(i>j && val!=get_value(j,i))
                throw " Invalid Value !!!!!!!\n ";
          if(i<=j)
          {
            int k=i*(2*size-i-1)/2 + j;
            a[k]=val;
          }
      }
      ~Sym_matrix()
      {
          delete []a;
      }
};
int main()
{
    int m,n,value;
    cout<<"-------Symmetric Matrix--------\n";
    try
    {
          cout<<"\nEnter The Rows Of Matrix : ";
          cin>>m;
          cout<<"\nEnter The Columns Of Matrix : ";
          cin>>n;
          if(m!=n)
            throw " Should Be a Square Matrix \n";
          Sym_matrix A(m);
          cout<<"\nEnter The Elements Of The Matrix \n";
          for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
            {
              cin>>value;
              A.set_value(i,j,value);
            }
          cout<<"\nThe Entered Matrix Is As Follows \n";
          for(int i=0;i<m;i++)
           {
               cout<<endl;
             for(int j=0;j<n;j++)
               cout<<A.get_value(i,j)<<" ";
           }
           cout<<endl;
      }
      catch(const char* message)
      {
          cout<<"\nException Caught : "<<message<<endl;
      }
    return 0;
}

