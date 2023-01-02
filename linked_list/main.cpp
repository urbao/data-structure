// hw2-1: implementation of doubly linked list
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
    char data;
};

// get current node count (single element is counted by 1)
int GetNodeCount(Node* head){
    int node_count=0;
    Node* current=head;
    while(current!=nullptr){ 
        node_count++;
        current=current->next;
    }
    return node_count;
}

// insert node function (need to restore head address after operation)
void InsertNode(Node*& head, string data_str, int pos){
    for(int i=0;i<data_str.size();i++){
        if(data_str[i]<32||data_str[i]>126||data_str.size()>1){
            cout<<"Insert wrong data\n";  
            return;
        }
    }
    if(head==nullptr&&pos!=0)cout<<"Insert wrong position\n";
    else if(pos<0||pos>GetNodeCount(head))cout<<"Insert wrong position\n"; 
    else{
        char data=data_str[0];
        // no head
        if(head==nullptr&&pos==0){
            head=new Node();
            head->next=nullptr;
            head->prev=nullptr;
            head->data=data;
        }
        // head exist (front middle end)
        else{
            Node* restore_head=head;   // for head restore address   
            //front
            if(pos==0){                
                Node* new_node=new Node();
                new_node->data=data;
                new_node->next=head;
                new_node->prev=head->prev;
                head->prev=new_node;
                head=new_node;
            }            
            //end
            else if(pos==GetNodeCount(head)){
                while(head->next!=nullptr)head=head->next;
                Node* new_node=new Node();
                new_node->data=data;
                new_node->next=head->next;
                new_node->prev=head;
                head->next=new_node;
                head=restore_head;
            }
            //middle
            else{
                for(int i=0;i<pos;i++)head=head->next;
                Node* new_node=new Node();
                new_node->data=data;
                new_node->next=head;
                new_node->prev=head->prev;
                (head->prev)->next=new_node;                
                head->prev=new_node;        
                head=restore_head;
            }            
        }
    }
    return;
}

// delete node in specified position
void DeleteNode(Node*& head, int pos){
    if(head==nullptr)cout<<"Linked list is empty\n";
    else if(pos<0||pos>=GetNodeCount(head))cout<<"Delete wrong position\n";
    else{
        Node* restore_head=head;
        // front
        if(pos==0){
            if(head->next==nullptr&&head->prev==nullptr){ // prevent the node is the last one node
                head=nullptr;
                return;
            }                 
            head=head->next;
            head->prev=nullptr; 
            delete head->prev;
        }
        // tail
        else if(pos==GetNodeCount(head)-1){
            while(head->next!=nullptr)head=head->next;
            head=head->prev;
            head->next=nullptr;
            delete head->next;
            head=restore_head;
        }
        // middle
        else{
            for(int i=0;i<pos;i++)head=head->next;
            (head->prev)->next=head->next;
            (head->next)->prev=head->prev;
            head=nullptr;
            delete head;
            head=restore_head;
        }
    }
    return;
}

// delete all nodes with same data
void DeleteData(Node*& head, string data_str){
    for(int i=0;i<data_str.size();i++){
        if(data_str[i]<32||data_str[i]>126||data_str.size()>1){
            cout<<"Delete wrong data\n";  
            return;
        }
    }
	if(head==nullptr)cout<<"Linked list is empty\n";
    else{
        Node* current=head;
        int pos=0;
        char data=data_str[0];
        while(current!=nullptr){
            if(current->data==data){
                DeleteNode(head, pos);
                pos--;
            }
            pos++;
            current=current->next;
        }
    }
    return;
}

// print all nodes data in list
void PrintList(Node* head){
    if(head==nullptr){
        cout<<"Linked list is empty\n";
        return;
    }
    Node* current=head;
    while(current!=nullptr){
        cout<<current->data<<" ";
        current=current->next;
    }
    cout<<endl;
    return;
}

// find node counts with specified data with return count result
int NumOfOccur(Node* head, string data_str){
    // prevent invalid condition
    for(int i=0;i<data_str.size();i++){
        if(data_str[i]<32||data_str[i]>126||data_str.size()>1){
            cout<<"Search wrong data\n";  
            return -1;
        }
    }
    if(head==nullptr){
        cout<<"Linked list is empty\n";
        return -1;
    }
    int count=0;
    Node* current=head;
    char data=data_str[0];
    while(current!=nullptr){
        if(current->data==data)count++;
        current=current->next;
    }
    return count;
}

// find most nodes with same type
void MaxNumOfOccur(Node* head){
    if(head==nullptr){
        cout<<"Linked list is empty\n";
        return;
    }
    int node_count=GetNodeCount(head);
    int max_occur=0, idx=0;
    char* arr=new char[node_count]{0}; // initialize an array(prevent all elements're max occur)
    Node* current=head;
    while(current!=nullptr){
        string current_data;
        current_data=current->data;
        int current_node_occur=NumOfOccur(current, current_data);
        if(current_node_occur>max_occur){  // refresh arr since max occur appear
            max_occur=current_node_occur;  // update max count
            for(int i=0;i<node_count;i++){
                arr[i]=0;
            }
            idx=0;
            arr[idx]=current->data;
            idx++;
        }
        else if(current_node_occur==max_occur){ // check if data already in result arr(if not, add it to arr)
            for(int i=0;i<node_count;i++){
                if(arr[i]==current->data)break; // already exist
                else if(arr[i]==0){
                    arr[idx]=current->data;
                    idx++;
                    break;
                }
            }
        }
        else;
        current=current->next;
    }
    // print out result
    for(int i=0;i<node_count;i++){
        if(arr[i]==0);
        else cout<<arr[i]<<" ";
    }
    cout<<endl;
    delete[] arr;
    return;
}

// search if the given word exist in list
void SearchWord(Node* head, char* word){
    if(head==nullptr){
        cout<<"Linked list is empty\n";
        return;
    }
    Node* current=head;
    while(current!=nullptr){
        if(*word==0||!(*word)){
            cout<<"found\n";
            return;
        }
        if(*word>126||*word<32){
            cout<<"Search wrong word\n";
            return;
        }        
        if(current->data==(*word))word++;
        current=current->next;
    }
    if(*word)cout<<"not found\n";
    else cout<<"found \n";
    return;
}

// read file & combine all function together(only allowed for string reading file)
void execute(){
    string action, data, pos; 
    Node* head=nullptr;
    while(cin>>action){        
        // start doing things based on its action
        if(action=="InsertNode"){
            cin>>data;
            cin>>pos;
            InsertNode(head, data, stoi(pos));
        }
        else if(action=="DeleteNode"){
            cin>>pos;
            DeleteNode(head, stoi(pos));
        }
        else if(action=="DeleteData"){
            cin>>data;
            DeleteData(head, data);
        }
        else if(action=="PrintList"){
            PrintList(head);
        }
        else if(action=="NumOfOccur"){
            cin>>data;
            int count=NumOfOccur(head, data);
            if(count!=-1)cout<<count<<endl; // no error then output return value
        }
        else if(action=="MaxNumOfOccur"){
            MaxNumOfOccur(head);           
        }
        else if(action=="SearchWord"){
            cin>>data;
            SearchWord(head, &data[0]);
        }
        else cout<<"> No corresponding function\n";                        
    }
    return;
}

int main(){
        
    execute();
    
    system("pause");
    return 0;
}
