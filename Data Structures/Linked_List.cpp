#include<iostream>
#include<stdlib.h>
using namespace std;

template <typename T>
struct node{
    T data;
    node *next;
};

template <typename T>
class List{
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
void List<U> :: insert_head(U new_data){
        //if(head==NULL) throw("Head already exists");
        node<U> *new_node = new node<U>;
        new_node->data = new_data;
        if(head==NULL && tail==NULL){
            new_node->next = NULL;
            head = new_node;
            tail = new_node;
        }
	else{
        new_node->next = head;
        head = new_node;
	}
}

template <typename T>
void List<T> :: insert_tail(T new_data){
        node<T> *new_node = new node<T>;
        new_node->data = new_data;
        new_node->next = NULL;
        if(head == NULL){
            head = new_node;
            tail = new_node;
        }
        else{
            tail->next = new_node;
            tail = new_node;
        }
}

template <typename T>
void List<T> ::  insert_After(int position,T new_data){
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
T List<T> :: delete_head(){
    if(head==NULL) throw "Empty";
    T ele = head->data;
    node<T> *ptr = head;
    if(head==tail){
        head = NULL;
        tail = NULL;
    }
    else{
        head = head->next;
    }
    delete ptr;
    return ele;

}

template <typename T>
T List<T> :: delete_tail(){
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
        tail->next = NULL;
    }
    return ele;
}

template <typename T>
T List<T> :: delete_element(T elem){
    T X;
    node<T> *temp = head,*prev;
    if(head!=0){
        while (temp != NULL && temp->data == elem){
            head = temp->next;
            delete temp;
            temp = head;
        }
        while(temp!=NULL){
            while(temp!=NULL && temp->data!=elem){
                prev = temp;
                temp = temp->next;
            }
            if(temp==NULL){
                cout<<"Element Not Found!"<<endl;
                return 0;
            }
        //node<T> *temp = ptr->next;
            X = temp->data;
            prev->next = temp->next;
            delete temp;
            temp = prev->next;
        }
    }
    return X;
}

template <typename T>
void List<T> :: reverse(){
    node<T> *current,*temp,*prev;
    current = head;
    prev = NULL;
    while(current!=0){
        temp=current->next;
        current->next = prev;
        prev = current;
        current = temp;
    }
    swap(head,tail);
}

template <typename T>
void List<T> :: printList(){
    node<T>* last = head;
    while (last != NULL)
    {
        cout<<last->data<<endl;
        last = last->next;
    }
}
int main(){

    try{
	int choice,position,data;
	bool flag=true;
	cout<<"Choose From Below \n1. Insert Head\n2. Insert Tail\n3. Insert After\n4. Delete\n5. Reverse\n6. Print List\n7. Exit\n\n";
	List<int> L;
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
                            if(x!=0)
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

