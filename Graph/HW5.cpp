#include<iostream>
#include <queue>
#include <stack>
#include <cmath>
#include <map>
using namespace std;

struct Node {
    Node* leftchild;
    Node* rightchild;
    Node* parent;
    int value;
};

class BST{
private:
    Node* root;

public:
    BST() :root(nullptr) {};
    Node* GetRoot() { return root; }
    Node* Search(int value);
    void InsertNode(int value);
};


Node* BST::Search(int value) {
	Node* now = root;
	while(1){
		if(now==NULL) return now;
		if(value == now->value) return now;
		if(value < now->value) now = now->leftchild;
		else	now = now->rightchild;
	}
}

void BST::InsertNode(int value) {
	Node* new_node = new Node;
	new_node -> value = value;
	if(root == NULL){
		root = new_node;
		root->parent = nullptr;
		root->leftchild = nullptr;
		root->rightchild = nullptr;
		return;
	}
	Node* now = root;
	while(1){
		if(now->value >= new_node -> value){
			if(now->leftchild == nullptr){
				now->leftchild = new_node;
				new_node->parent = now;
				new_node->leftchild = nullptr;
				new_node->rightchild = nullptr;
				return;
			}else
				now = now->leftchild;
		}else if(now -> value < new_node -> value){
			if(now->rightchild == nullptr){
				now->rightchild = new_node;
				new_node->parent = now;
				new_node->leftchild = nullptr;
				new_node->rightchild = nullptr;
				return;
			}else
				now = now->rightchild;
		}
	}
}

int main(){
	int L, n;
	cin >> L >> n;
	BST arr;
	arr.InsertNode(0);
	arr.InsertNode(L);
	while(n--){
		int x;
		cin >> x;
		arr.InsertNode(x);
		Node* now = arr.Search(x);
		if(now->leftchild == nullptr && now->rightchild == nullptr){
			if( now->parent->parent == nullptr){
				if(now->parent->leftchild == now){
					cout << max(x - now->parent->value, now->parent->rightchild->value - x) << '\n';
				} else{
					cout << max(x - now->parent->value, now->parent->leftchild->value - x) << '\n';
				}
				
			}else{
				cout << max(x - now->parent->value, now->parent->parent->value - x) << '\n';
			}
			
		}else if(now->leftchild == nullptr){
			cout << max(x - now->parent->value, now->rightchild->value - x) << '\n';
		}else if(now->rightchild == nullptr){
			cout << max(x - now->leftchild->value, now->parent->value - x) << '\n';
		}else{
			cout << max(x - now->leftchild->value, now->rightchild->value - x) << '\n';
		}
	}
	return 0;
} 
