// hw2-3: garage of rich man
// environment: Notepad++ 8.2.1(64bits X64)
// C++ type: C++ 11
// g++ type: g++ version 6.3.0
#include <iostream>
#include <string>

using namespace std;

// car node
class Car{
public:
    Car* prev;
    Car* next;
    int code;
};

// insert at front (the end is the longest car haven't been driven)
void InsertHeadCar(Car*& head, const int& code){
       // no head
       if(head==nullptr){
           head=new Car();
           head->next=nullptr;
           head->prev=nullptr;
           head->code=code;
       }
       // head exist
       else{
           Car* new_node=new Car();
           new_node->code=code;
           new_node->next=head;
           new_node->prev=head->prev;
           head->prev=new_node;
           head=new_node;
       }
    return;
}

// delete the end of linked list (when garage is full)
void DeleteTailCar(Car*& head){
    if(head==nullptr){
        cout<<"Car garage is empty\n";
        return;
    }
    // 2 situation: only 1 car left v.s. more than 1 car
    Car* restore_head=head;
    while(head!=nullptr){
        if(head->prev==nullptr&&head->next==nullptr){ // only one car
            head=nullptr;
            return;
        }
        else if(head->next==nullptr){   // reach the last one car
            head=head->prev;               
            head->next=nullptr;
            delete head->next;
            head=restore_head;
            return;
        }   
        head=head->next;
    }
}

// delete specified code of car (when driving a car, need to reinsert to renew the time of cars not be droven)
void DeleteCodeCar(Car*& head, const int& code){
    if(head==nullptr)cout<<"Car garage is empty\n";
    Car* restore_head=head;
    while(head!=nullptr){
        if(head->code==code){  // find the car to delete
            if(head->next==nullptr&&head->prev==nullptr){  // special case: the last one car
                head=nullptr;
            }
            else if(head->next!=nullptr&&head->prev==nullptr){  // head case
                head=head->next;                
                head->prev=nullptr;
                delete head->prev;
            }
            else if(head->next==nullptr&&head->prev!=nullptr){   // tail case
                head=head->prev;               
                head->next=nullptr;
                delete head->next;
                head=restore_head;
            }
            else{    // middle car
                (head->prev)->next=head->next;
                (head->next)->prev=head->prev;               
                head=nullptr;
                delete head;
                head=restore_head;
            }
            return;
        } 
        head=head->next;
    }
}

// get car total count
int current_car_count(Car* head){
    int count=0;
    while(head!=nullptr){
        count++;
        head=head->next;
    }
    return count;
}

// search if specified code of car exist in garage
bool is_in_garage(Car* head, const int& code){
    while(head!=nullptr){
        if(head->code==code)return true;
        head=head->next;
    }
    return false;
} 

// print out garage (from the latest to oldest)
void print_garage(Car* head){
    if(head==nullptr)cout<<"Car garage is empty\n";
    else{
        while(head!=nullptr){
            cout<<head->code<<" ";
            head=head->next;
        }
        cout<<endl;
    }
    return;
}

// garage process
void rich_man_garage(){
    int garage_size=0;
    cin>>garage_size;
    cout<<"The size of garage is "<<garage_size<<endl;
    string action, car_code;
    int new_car_code=0;
    Car* head=nullptr;
    while(cin>>action){
        if(action=="buy"){ // need to consider if garage is full
            if(current_car_count(head)==garage_size)DeleteTailCar(head);            
            InsertHeadCar(head, new_car_code);
            new_car_code++;
            print_garage(head);
        }
        else if(action=="drive"){
            cin>>car_code;            
            if(!is_in_garage(head, stoi(car_code)))cout<<"This car is not in the garage"<<endl;
            else{   // car is in the garage (move it out and repark in the front)
                DeleteCodeCar(head, stoi(car_code)); // move it out
                InsertHeadCar(head, stoi(car_code)); // repark in the head
                print_garage(head);
            }             
        }
        else cout<<"> No corresponding function\n";
    }
    return;
}

int main(){
    
    rich_man_garage();
    
    system("pause");
    return 0;
}
