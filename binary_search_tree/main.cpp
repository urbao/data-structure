// hw3-1: binary search tree implementation
// environment: Notepad++ 8.2.1(64bits X64)
// C++ type: C++ 14
// g++ type: g++ version 6.3.0
#include <iostream>
#include <string>

using namespace std;

// tree node initializtion
class Node{
public:
	int data=-1;
	Node* left=nullptr;
	Node* right=nullptr;
};

// check if data is invalid
bool invalid_data(string data){
	// check if non digit exist
	for(int i=0;i<data.size();i++){
		if(!isdigit(data[i]))return true;
		else;
	}
	// check if data overflow
	if(stoi(data)>100)return true;
	else return false;
}

// exist function (TRUE: exist)
bool node_exist(Node* root, string data){
	if(root==nullptr)return false; // impossible for data to store in the bst
	// start searching
	if(root->data==stoi(data))return true;
	if(root->data<stoi(data))return node_exist(root->right, data);
	if(root->data>stoi(data))return node_exist(root->left, data);
}

// print out specific level of data OR check how many level exist
// for: Print() & Height() function purpose
bool level_traversal(Node* root, int level, bool print){
    if (root==nullptr){
        return false;
    }
    if (level==1&&print){
        cout << root->data << " ";
        return true;
    }
	if(level==1&&!print){
		return true;
	}
    bool left=level_traversal(root->left, level-1, print);
    bool right=level_traversal(root->right, level-1, print);
    return left||right; // still exist node not print
}

// search by level & store data at string
// for: Search function purpose
bool level_search(Node* root, int level, string& result, string data){
    if (root==nullptr){
		result+='-';
        return false;
    }
    if (level==1){
		if(stoi(data)==root->data)result+='#';
		else result+='-';
        return true;
    }
    bool left=level_search(root->left, level-1, result, data);
    bool right=level_search(root->right, level-1, result, data);
    return left||right; // still exist node not print
}

// search for the delete node & its parent
void search_node(Node*& curr, int data, Node*& parent){
    // traverse the tree and search for the data
    while(curr!=nullptr&&curr->data!=data){
        // update the parent to the current node
        parent=curr;
        if (data<curr->data){
            curr=curr->left;
        }
        else{
            curr=curr->right;
        }
    }
}

/*-----------------MAIN WORKING FUNCTION BELOW---------------------------*/
// insert function
void Insert(Node*& root, string data){
	// prevent invalid insert options
	if(invalid_data(data)){
		cout<<"Insert wrong data\n";
		return;
	}
	// root is nullptr
	if(root==nullptr){
		root=new Node();
		root->data=stoi(data);
		return;
	}
	// root is NOT nullptr && same data already exist
	if(node_exist(root, data)){
		cout<<"This data is in BST\n";
		return;
	}
	// root is NOT nullptr && No same data exist in bst
	// insert node to its position
	else{
		Node* restore_root=root;
		// go right
		if(stoi(data)>root->data){
			if(root->right==nullptr){ // create new node
				Node* new_node=new Node();
				new_node->data=stoi(data);
				root->right=new_node;
				return;
			}
			else{
				Insert(root->right, data);
			}
		}
		// go left
		else{
			if(root->left==nullptr){
				Node* new_node=new Node();
				new_node->data=stoi(data);
				root->left=new_node;
				return;
			}
			else{
				Insert(root->left, data);
			}
		}
		root=restore_root;
	}
	return;
}

// delete function
void Delete(Node*& root, string data){ 
	// prevent invalid insert options
	if(invalid_data(data)){
		cout<<"Delete wrong data\n";
		return;
	}
	// root is nullptr
	if(root==nullptr){
		cout<<"BST is empty\n";
		return;
	}
	// root is NOT nullptr && data not exist
	if(!node_exist(root, data)){
		cout<<"This data is not in BST\n";
		return;
	}
	// root is NOT nullptr && data exist in bst
	// delete node
	else{
		Node* parent = nullptr;
		Node* curr = root;
		// search data in the BST and set its parent pointer
		search_node(curr, stoi(data), parent);
		// Case 1: del_node has NO children
		if(curr->left==nullptr&&curr->right==nullptr){
			if(curr!=root){ // del_node is NOT root
				if (parent->left==curr){
					parent->left=nullptr;
				}
				else {
					parent->right = nullptr;
				}
			}
			// Only one node
			else{
				root=nullptr;
			}
			delete curr;
		}
		// Case 2: Two children of del_node
		else if (curr->left&&curr->right){
			// find its inorder successor node
			Node* successor=curr->right;
			while(successor->left!=nullptr)successor=successor->left;
			// store successor value
			int val = successor->data;
			Delete(root, to_string(successor->data));
			// copy value of the successor to the current node
			curr->data=val;
		}
		// Case 3: Only one child of del_node
		else{
			// choose the exist child node
			Node* child;
			if(curr->left)child=curr->left;
			else child=curr->right;
			// curr NOT root, so set child to parent
			if (curr!=root){
				if(curr==parent->left){
					parent->left=child;
				}
				else{
					parent->right=child;
				}
			}
			// del_node is root, child become root
			else{
				root=child;
			}
			delete curr;
		}
	}
}
 
// height of tree
int Height(Node* root){
	if(root==nullptr)return 0;
	int level=1; 
	while (level_traversal(root, level, false)) {
        level++;
    }
	return level-1;
}

// Function to print level order traversal of a given binary tree
void Print(Node* root){
    // empty tree
	if(root==nullptr){
		cout<<"Empty tree";
		return;
	}
    int level = 1;
    // run till printLevel() returns false
    while (level_traversal(root, level, true)) {
        level++;
    }
	return;
}

// search given data
int Search(Node* root, string data){
	if(invalid_data(data)){
		cout<<"Search wrong data\n";
		return -1;
	}
	// root is nullptr
	if(root==nullptr){
		cout<<"BST is empty\n";
		return -1;
	}
	// root is NOT nullptr && data not exist
	if(!node_exist(root, data)){
		cout<<"This data is not in BST\n";
		return -1;
	}
	else{
		string result="";
		int level=1, idx=0;
		while(level_search(root, level, result, data)){
			level++;
		}
		for(int i=0;i<result.size();i++){
			if(result[i]=='#'){
				idx=i+1;
				break;
			}
		}
		return idx;
	}
}

// Number function
int Number(Node* root){
	int count=0;
	if(root==nullptr)return 0;
	count++;
	count+=Number(root->left);
	count+=Number(root->right);
	return count;
}

// combination of all instructions
void bst(){
	Node* root=nullptr;
	string action, data;
	while(cin>>action){
		if(action=="Insert"){
			cin>>data;
			Insert(root, data);
		}
		else if(action=="Delete"){
			cin>>data;
			Delete(root, data);
		}
		else if(action=="Height"){
			cout<<Height(root)<<endl;
		}
		else if(action=="Print"){
			Print(root);
			cout<<endl;
		}
		else if(action=="Search"){
			cin>>data;
			int result=Search(root, data);
			if(result!=-1)cout<<result<<endl;
		}
		else if(action=="Number"){
			cout<<Number(root)<<endl;
		}
		else{
			cout<<"Wrong instruction"<<endl;
		}
	}
	return;
}

int main(){
	
	bst();
	
	system("pause");
	return 0;
}
