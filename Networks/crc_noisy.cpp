#include<iostream>
#include <stdlib.h>
using namespace std;

class crc{
    int n4;
public :

    char XOR(char a,char b){
        if(a==b){
            return '0';
        }
        else{
            return '1';
        }
    }

    void append(int size_data,int size_gen,char *dataword,char *codeword){
        for(int i=0;i<size_data;i++){
            codeword[i] = dataword[i];
        }
        for(int i=0;i<size_gen-1;i++){
            codeword[size_data+i] = '0';
        }
        cout<<"\n\nNew dividend : ";
        for(int i=0;i<(size_data+size_gen-1);i++){
            cout<<codeword[i];
        }
        n4 = size_data;
    }

    void error_intro(char* codeword,int size_data){
        int pos = rand()%(size_data-1);
        int pos1 = rand()%(size_data-1);
        char x;
        int start_i,end_i;
        if(pos==pos1){
            if(codeword[pos]=='1'){
                codeword[pos]= '0';
            }
            else{
                codeword[pos]='1';
            }
        }
        else{
            if(pos<pos1){
                start_i = pos;
                end_i = pos1;
            }
            else{
                start_i = pos1;
                end_i = pos;
            }
            if(codeword[start_i]=='1'){
                codeword[start_i] = '0';
            }
            else{
                codeword[start_i] = '1';
            }
            if(codeword[end_i]=='1'){
                codeword[end_i] = '0';
            }
            else{
                codeword[end_i] = '1';
            }

            for(int i=start_i+1;i<end_i;i++){
                if(rand()%2==0){
                    if(codeword[i]=='1'){
                        codeword[i] = '0';
                    }
                    else{
                        codeword[i] = '1';
                    }
                }
            }
        }
    }

    void div(int size_data,int size_gen,char *remainder,char *codeword,char *gen_poly){
        for(int i=0;i<size_gen;i++){
            remainder[i] = codeword[i];
        }
        for(int i=0;i<n4;i++){
            if(remainder[0]=='1'){
                for(int i=0;i<size_gen;i++){
                    remainder[i] = XOR(remainder[i],gen_poly[i]);
                }
            }
            else if(remainder[0]=='0'){
                for(int i=0;i<size_gen;i++){
                    remainder[i] = XOR(remainder[i],'0');
                }
            }
            if(i<n4-1){
                for(int i=0;i<size_gen-1;i++){
                    remainder[i]= remainder[i+1];
                }
                remainder[size_gen-1] = codeword[i+size_gen];
            }
        }
        cout<<endl;
        cout<<"\n\nRemainder : "<<endl;
        for(int i=0;i<size_gen;i++){
            cout<<remainder[i];
        }
    }
    void add_rem(int size_data,int size_gen,char *codeword,char *remainder){
        for(int i=size_data-1;i<(size_data+size_gen-1);i++){
            codeword[i]=XOR(codeword[i],remainder[i-(size_data-1)]);
        }
        cout<<"\n\nFinal Message : ";
        for(int i=0;i<(size_data+size_gen-1);i++){
            cout<<codeword[i];
        }
        cout<<endl;
    }
    bool validation(char *gen_poly,int size_gen){
        if(gen_poly[0]=='1' && gen_poly[size_gen-1]=='1' && size_gen>=2){
            return true;
        }
        else{
            return false;
        }
    }
    void reciever(int size_data,int size_gen,char *remainder,char *codeword,char *gen_poly){
        int flag = false;
        cout<<"\n\nIn Receiver "<<endl;
        div(size_data,size_gen,remainder,codeword,gen_poly);
        for(int i=0;i<size_gen;i++){
            if(remainder[i]=='0'){
                flag = true;
            }
            else{
                flag = false;
                break;
            }
        }
        if(flag==true){
            cout<<"\nMessage Received Correctly !"<<endl;
        }
        else{
            cout<<"\nMessage NOT  Received Correctly !"<<endl;
        }
    }

};
int main(){
    srand(NULL);
    int size_gen,size_data,n4;
    char *dataword ,*remainder ,*gen_poly, *codeword;
    bool flag = false;
    crc C;
    cout<<"Enter the size of Generator Polynomial : ";
    cin>>size_gen;
    gen_poly = new char[size_gen];
    cout<<"Enter the Generator Polynomial in Bits : "<<endl;
    for(int i=0;i<size_gen;i++){
        cin>>gen_poly[i];
    }
    do{
        cout<<"Enter the size of Message : ";
        cin>>size_data;
        if(size_data<size_gen){
            cout<<"Please Enter size Greater Than Generator Polynomial!"<<endl;
            flag = true;
        }
        else{
            flag = false;
        }
    }while(flag == true);
    dataword = new char[size_data];
    codeword = new char[size_data+size_gen-1];
    remainder = new char[size_gen];
    cout<<"Enter the Message in Bits : "<<endl;
    for(int i=0;i<size_data;i++){
        cin>>dataword[i];
    }
                /***********************************SENDER**********************************/
    C.append(size_data,size_gen,dataword,codeword);
    bool x = C.validation(gen_poly,size_gen);
    if(x==true){
        C.div(size_data,size_gen,remainder,codeword,gen_poly);
        C.add_rem(size_data,size_gen,codeword,remainder);
        C.error_intro(codeword,(size_data+size_gen-1));
    }
    else {
        cout<<"The Generator Polynomial Should Have Atleast 2 bits and The Most-Least Significant Bits should be 1."<<endl;
    }
                /**************************RECIEVER**************************/
    C.reciever(size_data,size_gen,remainder,codeword,gen_poly);

return 0;
}
