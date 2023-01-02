// hw2-2: calculation of big number
// environment: Notepad++ 8.2.1(64bits X64)
// C++ type: C++ 11
// g++ type: g++ version 6.3.0
#include <iostream>
#include <string>

using namespace std;

// node class def
class Node{
public:
    Node* prev;
    Node* next;
    string data;
};

// print node list starting from tail
void print_list_from_head(Node* head){
    if(head==nullptr)cout<<"> Empty list(print list)";
    if(head->data=="-"){
        head=head->next;
        while(head->data=="0"&&head->next!=nullptr)head=head->next;  // find the first non-zero digit
        if(head->data!="0")cout<<"-";
        
    }
    else {
        while(head->data=="0"&&head->next!=nullptr)head=head->next;  // find the first non-zero digit        
    }
    while(head!=nullptr){
            cout<<head->data;
            head=head->next;
        }
    cout<<endl;
    return;
}

// insert node function (need to restore head address after operation)
// always insert at front position in this project
void InsertNode(Node*& head, string data){
       // no head
       if(head==nullptr){
           head=new Node();
           head->next=nullptr;
           head->prev=nullptr;
           head->data=data;
       }
       // head exist
       else{
           Node* new_node=new Node();
           new_node->data=data;
           new_node->next=head;
           new_node->prev=head->prev;
           head->prev=new_node;
           head=new_node;
       }
    return;
}

// delete negative sign'-', since calculation is no more needed
void remove_sign(Node*& head){
    Node* restore_head=head;
    if(head==nullptr)cout<<"> Empty list(rm sign)\n";
    while(head!=nullptr){
        if(head->data=="-"){            
            head=head->prev;
            head->next=nullptr;            
            delete head->next;
            head=restore_head;            
            return;
        }
        head=head->next;
    }
    head=restore_head;
    return;
}

// build big number list
void build_list(Node*& head, string num){
    string data;
    for(int i=0;i<num.size();i++){
        data=num[i];
        InsertNode(head, data);
    }
    return;
}

// check if the number is negative or positive
bool positive_or_not(Node* head){
    while(head!=nullptr){
        if(head->data=="-")return false; // it's negative
        head=head->next;
    }
    return true;
}

// get absolute value digit counts
int get_digit(Node* head){
    int digit=0;
    while(head!=nullptr&&head->data!="-"){
        digit++;
        head=head->next;
    }
    return digit;
}

// check if ABSOLUTE value of num1 is bigger than absolute value num2 
bool num1_bigger_or_equal_than_num2(Node* num1, Node* num2){
    if(get_digit(num1)>get_digit(num2))return true;
    else if(get_digit(num2)>get_digit(num1))return false;
    else{
        // digit of num1 == digit of num2
        while(num1->next!=nullptr){
            num1=num1->next;
            num2=num2->next;
        }              
        while(num1!=nullptr){
            if(stoi(num1->data)>stoi(num2->data))return true;
            else if(stoi(num2->data)>stoi(num1->data))return false;
            else{
                num1=num1->prev;
                num2=num2->prev;
            }
        }
        return true; // compare all digit, but no result --> both number equals to each other
    }
}

// add two number and store in result
void add(Node* head1, Node* head2, Node*& result){
    int carry=0, digit1=0, digit2=0, sum=0;
    while(head1!=nullptr||head2!=nullptr){
        if(head1==nullptr)digit1=0;
        else digit1=stoi(head1->data);
        if(head2==nullptr)digit2=0;
        else digit2=stoi(head2->data);
        sum=digit1+digit2+carry;
        InsertNode(result, to_string(sum%10));
        carry=sum/10;
        if(head1!=nullptr)head1=head1->next;
        if(head2!=nullptr)head2=head2->next;
    }
    if(carry==1)InsertNode(result, "1"); // prevent carry is 1
    return;
}

// num1 substract num2 and store in result (WARNING: num1 MUST BIGGER than num2)
void substract(Node* head1, Node* head2, Node*& result){
    int digit1=0, digit2=0, sum=0;
    while(head1!=nullptr){ // since num1 is bigger than num2
        if(head1==nullptr)digit1=0;
        else digit1=stoi(head1->data);
        if(head2==nullptr)digit2=0;
        else digit2=stoi(head2->data);
        if(digit1>=digit2)sum=digit1-digit2;       
        else{ // need to borrow from the closest non-zero terms
            sum=10+digit1-digit2;
            Node* restore_head=head1; // change borrowed digit status
            while(head1!=nullptr){ // borrow
                if(head1->next->data=="0")head1->next->data=to_string(stoi(head1->next->data)+9);
                else {
                    head1->next->data=to_string(stoi(head1->next->data)-1);
                    break;
                }
                head1=head1->next;
            }
            head1=restore_head;
        }
        InsertNode(result, to_string(sum));
        if(head1!=nullptr)head1=head1->next;
        if(head2!=nullptr)head2=head2->next;
    }
}


void big_number_calculator(){
    // data process
    string num1, sign, num2;
    Node* head1=nullptr; Node* head2=nullptr; Node* result=nullptr;
    cin>>num1; cin>>sign; cin>>num2;
    build_list(head1, num1);
    build_list(head2, num2);
    bool num1_positive=positive_or_not(head1);
    bool num2_positive=positive_or_not(head2);
    remove_sign(head1); 
    remove_sign(head2);
    // absolute value comparison
    bool num1_bigger_or_equal=num1_bigger_or_equal_than_num2(head1, head2); // true: >=  /  false: <
    // start calculation
    if(num1_bigger_or_equal){ // num1 > num2 && num1 == num2
        if(num1_positive){
            if(sign=="+"){
                if(num2_positive)add(head1, head2, result); // +++
                else substract(head1, head2, result);  // ++-
            }
            else{
                if(num2_positive)substract(head1, head2, result); // +-+
                else add(head1, head2, result);// +--
            }
        }
        else{
            if(sign=="+"){
                if(num2_positive)substract(head1, head2, result); // -++
                else add(head1, head2, result);  // -+-
            }
            else{
                if(num2_positive)add(head1, head2, result); // --+
                else substract(head1, head2, result);// ---
            }
            InsertNode(result, "-"); // result is negative
        }
    }
    else{ // num1 < num2
        if(num1_positive){
            if(sign=="+"){ 
                if(num2_positive)add(head1, head2, result);  // +++
                else{               // ++-
                    substract(head2, head1, result);
                    InsertNode(result, "-");
                } 
            }
            else{
                if(num2_positive){  // +-+
                    substract(head2, head1, result);
                    InsertNode(result, "-");
                }
                else add(head1, head2, result); // +--
            }
        }
        else{
            if(sign=="+"){
                if(num2_positive)substract(head2, head1, result);   //  -++
                else{           // -+-
                    add(head1, head2, result);
                    InsertNode(result, "-");
                } 
            }
            else{
                if(num2_positive){  // --+
                    add(head1, head2, result);
                    InsertNode(result, "-");
                }
                else substract(head2, head1, result);// ---
            }
        }
    }
    // print out result
    print_list_from_head(result);
    return;
}



int main(){
      
    big_number_calculator();
    
    system("pause");
    return 0;
}
