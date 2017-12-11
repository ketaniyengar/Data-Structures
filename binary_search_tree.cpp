#include <iostream>
#include <cstring>
#include <string>
using namespace std;

struct node {                       //struct to store the data
	int data;
	struct node *left;
	struct node *right;
}*head;

void search () {                     //function to search for a key in the BST
	if (head==NULL) {
		cout<< "The list is empty!\n\n";
		return;
	}
	else {
		cout <<"\nEnter the number: ";
		int data;
		cin>>data;
		struct node *q = head;
		while (q!=NULL) {                   //traversing the tree to find the key
			if (q->data>=data) {
				if (q->data==data) {        //print of the key is found
					cout<< "Key found!\n";
					return;
				}
				q = q->left;
			}
			else {
				q = q->right;
			}
		}
		cout<< "Key is not there in the list!\n";          //if the function doesn't return it means that the key is not there in the tree
	}
}

void del_node () {                   //function to delete a node from the BST
	if (head == NULL) {
		cout<< "The list is empty\n";
		return;
	}
	else {
		cout <<"\nEnter the number: ";
		int data;
		int t = 0;
		cin>>data;
		struct node *q = head,*p=NULL,*k=NULL,*g=NULL;
		while (q!=NULL) {
			if (q->data>=data) {       //exchanging the to be deleted key with the key which has a value nearest to the key and then rearranging the tree
				if (q->data == data) {
					g = q;
					if (q->right != NULL) {
						k = q;
						q = q->right;
						while (q->left!=NULL) {     //taking one right and then going to the extreme left of the tree to exchange it with the element to be deleted
							k = q;
							q = q->left;
						}
						q->left = g->left;
						if (p==NULL) {
							head = q;
						}
						else {
							if (p->left == g) {
								p->left = q;
							}
							else {
								p->right = q;
							}
						}
						if (g==k) {
							return;
						}
						k->left = q->right;
						q->right = g->right;
						return;
					}
					else {
						if (p==NULL) {             //taking care of the head case
							head = q->left;
							return;
						}
						else {
							if (p->left == q) {
								p->left = q->left;
								return;
							}
							p->right = q->left;
							return;
						}
					}
				}
				p = q;
				q = q->left;
			}
			else {
				p = q;
				q = q->right;
			}
		}
	}
	cout<< "The given key is not present in the list!\n";
}

void insert () {               //function which inserts a key into the BST by tranversing into it to find the perfect position to be inserted
	struct node *p = new node;
	struct node *q = head;
	cout<< "Enter the number: ";
	cin>>p->data;
	p->left = NULL;
	p->right = NULL;
	if (head==NULL) {
		head = p;
	}
	else {
		while (q!=NULL) {
			if (q->data > p->data) {
				if (q->left == NULL) {
					q->left = p;
					break;
				}
				q = q->left;
			}
			else {
				if (q->right == NULL) {
					q->right = p;
					break;
				}
				q = q->right;
			}
		}
	}
}

void display (struct node *p,int space) {   //function to print the whole BST
	if (p) {
		display(p->right,space+5);
		for (int i =0;i<space;i++) {
			cout<<" ";
		}
		cout<<p->data<<"\n";
		display(p->left,space+5);
	}
}

int main () {
	head = NULL;
	int a;
	while (1){
		cout<< "\nSelect the desired operation from the menu: \n";
		cout<< "===========================================";
		cout<< "\n1)Inserting a node\n";
		cout<< "2)Deleting a node with specific value\n3)Searching for a given element in the list\n";
		cout<< "4)Display the existing entries in the list\n";
		cout<< "5)Exit\n\n";
		cin>> a;
		switch (a) {
			case 1: {
				insert();
				break;
			}
			case 2: {
				del_node();
				break;
			}
			case 3: {
				search();
				break;
			}
			case 4: {
				display(head,0);
				break;
			}
			case 5: {
				cout<< "\n\n*************************************************\n|  THANKS FOR USING KETAN'S BINARY SEARCH TREE  |\n*************************************************\n";
				return 0;
			}
			default: {
				cout<<"Enter the correct number from the list!\n";
			}
		}
	}
	return 0;
}