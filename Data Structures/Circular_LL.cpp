#include<iostream>
#include<stdlib.h>
using namespace std;

template <typename T>
struct node{
    T data;
    node *next;
};

template <typename T>
class CLL{
    node<T> *head = NULL;
    node<T> *tail = NULL;
public :
    void insert_head(T);
    void insert_tail(T);
    void insert_After(int, T);
    T delete_head();
    T delete_tail();
    T delete_element(T elem);
    void reverse();
    void printList();
};

template <typename U>
void CLL<U> :: insert_head(U new_data){
        //if(head==NULL) throw("Head already exists");
        node<U> *new_node = new node<U>;
        new_node->data = new_data;
        if(head==NULL && tail==NULL){
            head = new_node;
            tail = head;
            tail->next = head;
        }
        else{
            new_node->next = head;
            head = new_node;
            tail->next = head;
        }
}

template <typename T>
void CLL<T> :: insert_tail(T new_data){
        node<T> *new_node = new node<T>;
        new_node->data = new_data;
        if(head == NULL){
            new_node->next = NULL;
            head = new_node;
            tail = new_node;
            head = tail;
        }
        else{
            new_node->next = head;
            tail->next = new_node;
            tail = new_node;
        }
}

template <typename T>
void CLL<T> ::  insert_After(int position,T new_data){
    int count = 1;
    node<T> *new_node = new node<T>;
    node<T> *inc = head;
    new_node->data = new_data;
    while(count<position){
        inc = inc->next;
        if(inc==NULL) throw "OverFlowed";
        count++;
    }
    new_node->next = inc->next;
    inc->next = new_node;
}

template <typename T>
T CLL<T> :: delete_head(){
    if(head==NULL) throw "Empty";
    T ele = head->data;
    node<T> *ptr = head;
    if(head==tail){
        head = NULL;
        tail = NULL;
    }
    else{
        head = head->next;
        tail->next = head;
    }
    delete ptr;
    return ele;
}

template <typename T>
T CLL<T> :: delete_tail(){
    if(head==NULL) throw "Empty";
    T ele = tail->data;
    if(head==tail){
        delete head;
        head = tail = NULL;
    }
    else{
        node<T> *ptr = head;
        while(ptr->next!=tail)
            ptr = ptr->next;
        delete tail;
        tail = ptr;
        tail->next = head;
    }
    return ele;
}

template <typename T>
T CLL<T> :: delete_element(T elem){
    T X;
    if(head!=0){
        if( elem==head->data){
            X=delete_head();
        }
        else{
            node<T> *ptr = head;
            while(ptr->next->data!=elem){
                if(ptr->next==head){
                    cout<<"Element Not Found!"<<endl;
                }
                ptr = ptr->next;
            }
            node<T> *temp = ptr->next;
            X = temp->data;
            ptr->next = temp->next;
            delete temp;
        }
    }
    return X;
}

template <typename T>
void CLL<T> :: reverse(){
    node<T> *current,*temp,*prev;
    current = head;
    prev = NULL;
    do{
        temp=current->next;
        current->next = prev;
        prev = current;
        current = temp;
    }while(current!=head);
    swap(head,tail);
}


template <typename T>
void CLL<T> :: printList(){
    node<T>* temp = head;
    if(temp==NULL) throw "Empty";
    while (temp != tail){
        cout<<temp->data<<endl;
        temp = temp->next;
    }
    cout<<temp->data<<endl;
}


int main(){

    try{
	int choice,position,data;
	bool flag=true;
	cout<<"Choose From Below \n1. Insert Head\n2. Insert Tail\n3. Insert After\n4. Delete\n5. Reverse\n6. Print List\n7. Exit\n\n";
	CLL<int> L;
label :	while(flag==true){
            cout<<"Enter Your Choice : ";
            cin>>choice;
            switch(choice){
                case 1 :{
                    cout<<"Enter the Data : ";
                    cin>>data;
                    L.insert_head(data);
                }
                break;
                case 2 :{
                    cout<<"Enter the Data : ";
                    cin>>data;
                    L.insert_tail(data);
                }
                break;
                case 3 :{
                    cout<<"Enter the Positon After Which You Want To Insert Data : ";
                    cin>>position;
                    cout<<"Enter The Data : ";
                    cin>>data;
                    L.insert_After(position,data);
                }
                break;
                case 4 :{
                    int del;
                    cout<<"1. delete from head\n2. delete from tail\n3. delete element\n";
                    cin>>del;
                    switch(del){
                        case 1 :{
                            int x = L.delete_head();
                            cout<<"Element Deleted : "<<x<<endl;
                        }
                        break;
                        case 2 :{
                            int x = L.delete_tail();
                            cout<<"Element Deleted : "<<x<<endl;
                        }
                        break;
                        case 3 :{
                            int elem;
                            cout<<"Enter The Element : ";
                            cin>>elem;
                            int x = L.delete_element(elem);
                            cout<<"Element Deleted : "<<x<<endl;
                        }
                        break;
                    }
                    cout<<"After Deletion \n";
                    L.printList();
                }
                break;
                case 5 :{
                    L.reverse();
                    L.printList();
                }
                break;
                case 6 :{
                    L.printList();
                }break;
                case 7 :{
                    flag = false;
                            cout<<"Have A Good Day!"<<endl;
                }
                break;
                default : {
                    cout<<"Please Choose From Above Options Only!\n";
                    goto label;
                }
                break;
            }
        }
    }
    catch(const char *msg){
        cout<<msg<<endl;
    }

    return 0;
}


