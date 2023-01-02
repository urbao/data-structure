// hw3-2: Huffman encoding implementation
// environment: Notepad++ 8.2.1(64bits X64)
// C++ type: C++ 14
// g++ type: g++ version 6.3.0
#include <iostream>
#include <string>

using namespace std;

// Node class
class Node{
public:
	char data='#';
	int freq=100000;
	Node* left=nullptr;
	Node* right=nullptr;
};

// differnet letters' counts of input string analyze 
int diff_char_count(string str, int*& alphabet){
	// from 'a' to 'z' check freq
	int char_count=0;
	for(int i=0;i<26;i++){
		alphabet[i]=0;
		for(int jj=0;jj<str.size();jj++){
			if(str[jj]==char(i+97))alphabet[i]++;
		}
	}
	// calculate how many different char exist in string
	for(int i=0;i<26;i++){
		if(alphabet[i]!=0)char_count++;
	}
	return char_count;
}

// build non-zero char arr (place symbols & data to array)
void build_node_arr(Node*& arr, int* alphabet){
	int idx=0;
	for(int i=0;i<26;i++){
		if(alphabet[i]!=0){
			arr[idx].data=char(i+97);
			arr[idx].freq=alphabet[i];
			idx++;
		}
	}
	return;
}

// print input string result
void str_result(int symbol_count, Node* arr){
	// print input array in format way
	cout<<"Symbol: ";
	for(int i=0;i<symbol_count;i++){
		cout<<arr[i].data<<" ";
	}
	cout<<"\nFrequency: ";
	for(int i=0;i<symbol_count;i++){
		cout<<arr[i].freq<<" ";
	}
	cout<<endl;
	return;
}

// rebuild array to normal form (move element with data '~' to last)
void refactor_arr(int symbol_count, Node*& arr){
	for(int i=0;i<symbol_count-1;i++){
		if(arr[i].data=='~'){
			swap(arr[i], arr[i+1]);
		}
	}
	return;
}

// get minimum frequency node out of array (TRUE: end / FALSE: not end)
bool min_freq_node(int symbol_count, Node*& arr, Node*& min_node){
	int counter=0;
	for(int i=0;i<symbol_count;i++){
		if(arr[i].freq!=100000)counter++;
	}
	// if the node is only left one
	int idx=0;
	for(int i=0;i<symbol_count;i++){
		if(arr[i].freq<min_node->freq&&arr[i].data!='~'){
			*min_node=arr[i];
			idx=i; // reset array item index
		}
	}
	arr[idx].data='~'; // reset arr[i]
	arr[idx].freq=100000;
	// refactor array
	refactor_arr(symbol_count, arr);
	if(counter==1)return true; // end
	else return false;
}

// insert node back to array (for the parent node)
void insert_node_arr(int symbol_count, Node*& arr, Node*& insert_node){
	for(int i=0;i<symbol_count;i++){
		if(arr[i].data=='~'&&arr[i].freq==100000){
			arr[i]=*insert_node;
			return;
		}
	}
	cout<<"Insert error"<<endl; // for some unexpected error
	return;
}

// build huffman tree
Node* build_huffman_tree(int symbol_count, Node*& arr){
	bool huffman_done=false;
	while(!huffman_done){
		Node* left_n=new Node();  // smallest 
		Node* right_n=new Node(); // second smallest
		Node* insert_n=new Node();// the parent
		// get the two smallest node
		huffman_done=min_freq_node(symbol_count, arr, left_n);
		if(huffman_done){
			// release array memory
			Node* result=left_n;
			delete arr;
			arr=nullptr;
			return result;
		}
		min_freq_node(symbol_count, arr, right_n); // left_n must have something
		// insert and update tree
		insert_n->freq=left_n->freq+right_n->freq;
		insert_n->left=left_n;
		insert_n->right=right_n;
		insert_node_arr(symbol_count, arr, insert_n);
		delete insert_n;  // release memory
		insert_n=nullptr;
	}
}

// levelorder traversal
bool level_order_traversal(Node* root, int level){
	if (root==nullptr){
        return false;
    }
    if (level==1){
        return true;
    }
    bool left=level_order_traversal(root->left, level-1);
    bool right=level_order_traversal(root->right, level-1);
    return left||right; // still exist node not print
}

// preorder traversal (Root->Left->Right)
void preorder_traversal(Node* root){
	if(root==nullptr)return;
	cout<<root->freq<<" ";
	preorder_traversal(root->left);
	preorder_traversal(root->right);
}

// inorder traversal (Left->Root->Right)
void inorder_traversal(Node* root){
	if(root==nullptr)return;
	inorder_traversal(root->left);
	cout<<root->freq<<" ";
	inorder_traversal(root->right);
}

// tree level counter
int level_counter(Node* root){
	int level=1;
	while(level_order_traversal(root, level)){
		level++;
	}
	return level-1;
}

// encode (use to find code)
void encode(Node* root, string& str){
	if(root==nullptr){
		str.pop_back();
		return;
	}
	if(root->left==nullptr&&root->right==nullptr){ // encounter leaf
		cout<<root->data<<": "<<str<<endl;
		str.pop_back();
		return;
	}
	encode(root->left, str+='0');
	encode(root->right, str+='1');
	str.pop_back();
}

// decode 
void decode(Node* root, string code){
	Node* reset=root;
	for(int i=0;i<=code.size();i++){
		if(i==code.size()){
			cout<<root->data<<endl; // reach string last char
			return;
		}
		if(code[i]=='0'){ // go left
			if(root->left==nullptr){
				cout<<root->data;
				root=reset;
				root=root->left;
			}
			else root=root->left;
		}
		else{ // go right
			if(root->right==nullptr){
				cout<<root->data;
				root=reset;
				root=root->right;
			}
			else root=root->right;
		}
	}
	return;
}

// print huffman tree result
void huffman_result(Node* root, string code, int* alphabet){
	cout<<"Huffman Tree:\n";
	cout<<"Preorder: ";
	preorder_traversal(root);
	cout<<"\nInorder: ";
	inorder_traversal(root);
	cout<<"\nLevel: "<<level_counter(root)<<endl;
	cout<<"Huffman Code: \n";
	string str="";
	encode(root, str);
	cout<<"Decoded Result: \n";
	decode(root, code);
	cout<<endl;
	return;
}

// all function combination
void huffman_coding(){
	/*--------------------Prepararion---------------------*/
	string str, code; // str: input string / code: huffman code
	cin>>str;
	cin>>code;
	int* alphabet=new int[26]; // store letters' appearance counts
	int symbol_count=diff_char_count(str, alphabet); // different letters' counts
	Node* arr=new Node[symbol_count]; // create Node array
	build_node_arr(arr, alphabet);
	str_result(symbol_count, arr);
	Node* root=build_huffman_tree(symbol_count, arr);
	huffman_result(root, code, alphabet);
	delete[] alphabet; // release memory
	return;
}

int main(){
	
	huffman_coding();
	
	system("pause");
	return 0;
}
