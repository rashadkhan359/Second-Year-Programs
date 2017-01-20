#include<iostream>
using namespace std;

template <class T>
struct node{
    T data;
    node* next;
    node* prev;
};

template <class T>
class Doubly{
    node<T> *head = NULL;
    node<T> *tail = NULL;
public :
    void insert_head(T new_data);
    void insert_tail(T new_data);
    void insert_after(int position,T new_data);
    void insert_before(int position,T new_data);
    void deletion();
    void printList();
    void reverse_print();
};

template <class T>
void Doubly<T> :: insert_head(T new_data){
    node<T> *new_node = new node<T>;
    new_node->data = new_data;
    new_node->next = head;
    new_node->prev = NULL;
    if(head==NULL && tail==NULL)
    {
        head = new_node;
        tail = new_node;
    }
    head->prev = new_node;
    head = new_node;
}

template<class T>
void Doubly<T> :: insert_tail(T new_data){
    node<T>* new_node = new node<T>;
    new_node->data = new_data;
    new_node->next = NULL;
    if(head==NULL){
        new_node->prev = NULL;
        head = new_node;
        tail = new_node;
        return;
    }
    tail->next = new_node;
    new_node->prev = tail;
    tail = new_node;
}

template <class T>
void Doubly<T> :: insert_after(int position,T new_data){
    node<T>* new_node = new node<T>;
    node<T>* traverse = head;
    int count=0;
    new_node->data = new_data;
    while(count<position-1){
        traverse = traverse->next;
        count++;
    }

    new_node->next = traverse->next;
    traverse->next = new_node;
    new_node->prev = traverse;

    if(new_node->next!=NULL){
        new_node->next->prev = new_node;
    }
}

template <class T>
void Doubly<T> :: insert_before(int position,T new_data){
    node<T>* new_node = new node<T>;
    node<T>* traverse = head;
    int count=0;
    new_node->data = new_data;
    while(count<position-1){
        traverse = traverse->next;
        count++;
    }

    new_node->next = traverse;
    new_node->prev = traverse->prev;
    traverse->prev = new_node;

    if(new_node->prev!=NULL){
        new_node->prev->next = new_node;
    }
}

template <class T>
void Doubly<T> :: deletion(){
    int count =1,position;
    node<T> *traverse = head;
    cout<<"Enter the Position Whose Element You want To Delete : ";
    cin>>position;
    cout<<"Position : "<<position<<endl;
    if(position==0){
        head = head->next;
        head->prev = NULL;
    }
    while(count<position){
        traverse =  traverse->next;
        if(traverse==NULL) throw "OverFlowed";
        count++;
    }
    traverse->prev->next = traverse->next;
    traverse->next->prev = traverse->prev;
    delete traverse;
}

template <class T>
void Doubly<T> :: printList(){
    node<T>* traverse = head;
    while(traverse!=NULL){
        cout<<traverse->data<<" ";
        traverse =  traverse->next;
    }
    cout<<endl;
}

template <class T>
void Doubly<T>:: reverse_print(){
    node<T>* last = head;
    while(last->next!=NULL){
        last = last->next;
    }
    while(last!=NULL){
        cout<<last->data<<" ";
        last = last->prev;
    }
    cout<<endl;
}

int main(){
    try{
	int choice,position,data;
	bool flag=true;
	cout<<"Choose From Below \n1. Insert Head\n2. Insert Tail\n3. Insert After\n4. Insert Before\n5. Delete\n6. Print List\n7. Exit\n\n";
	Doubly<int> D;
label :	while(flag==true){
            cout<<"Enter Your Choice : ";
            cin>>choice;
            switch(choice){
                case 1 :{
                    cout<<"Enter the Data : ";
                    cin>>data;
                    D.insert_head(data);
                }
                break;
                case 2 :{
                    cout<<"Enter the Data : ";
                    cin>>data;
                    D.insert_tail(data);
                }
                break;
                case 3 :{
                    cout<<"Enter the Positon After Which You Want To Insert Data : ";
                    cin>>position;
                    cout<<"Enter The Data : ";
                    cin>>data;
                    D.insert_after(position,data);
                }
                break;
                case 4 :{
                    cout<<"Enter the Positon Before Which You Want To Insert Data : ";
                    cin>>position;
                    cout<<"Enter The Data : ";
                    cin>>data;
                    D.insert_before(position,data);
                }
                break;
                case 5 :{
                    D.deletion();
                    cout<<"After Deletion \n";
                    D.printList();
                }
                break;
                case 6 :{
                    D.printList();
                }
                break;
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
