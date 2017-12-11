#include <iostream>
using namespace std;

struct node {           //structure to store the information of the red black tree
	int d;
	char c;
	struct node *p;
	struct node *l;
	struct node *r;
}*head;

void search () {                     //function to search for a key in the red black
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
			if (q->d>=data) {
				if (q->d==data) {        //print of the key is found
					cout<< "Key found!\n";
					return;
				}
				q = q->l;
			}
			else {
				q = q->r;
			}
		}
		cout<< "Key is not there in the list!\n";          //if the function doesn't return it means that the key is not there in the tree
	}
}

void print (struct node *p,int space){       //printing the red black tree like a tree
    if (p == NULL) {   	
        return;
    }
    print(p->r, space+5);
    cout <<"\n";
    for (int i = 2; i < space; i++) {
        cout <<" ";
    }
    if (p->c == 'r')                       //printing red coloured node in red
    	cout<<"\033[31m"<<p->d;
    else
    	cout<<"\033[37m"<<p->d;
	print(p->l, space+5);
}

void rotate (struct node *c) {           //rotate function takes care of both left and right rotate
	struct node *p;
	p = c->p;
	if (p->p!=p) {
		c->p = p->p;
		if (p == p->p->l) {
			p->p->l = c;
		}
		else {
			p->p->r = c;
		}
	}
	else {
		c->p = c;
		head = c;
	}
	p->p = c;
	if (p->l == c) {
		p->l = c->r;
		c->r = p;
	}
	else {
		p->r = c->l;
		c->l = p;
	}
}

void colour_check (struct node *c) {           //check the colour of the parent and if it is red then take the necessary steps to maintain the tree
	struct node *p,*g,*u;
	p = c->p;
	g = p->p;
	if (p==g->l) {     //getting the uncle pointer of the target node
		u = g->r;
	}
	else {
		u = g->l;
	}
	if (p->c == 'b'){              //if parent is black then no change is required as a new node is entered as with red colour
		return;
	}
	else {
		if (g==p) {
			p->c = 'b';           //the case where the parent is the head node
		}
		else if (u!=NULL && u->c == 'r') {   //if uncle is red then the colours of uncle, parent and grandparent have to be changed
			u->c = 'b';
			p->c = 'b';
			g->c = 'r';
			colour_check(g);
		}
		else {
			if (g->l == p) {            //if uncle doesnt exist or the uncle is not red then rotation has to be performed
				if (p->l == c) {
					rotate(p);
					p->c = 'b';
					g->c = 'r';
				}
				else {
					rotate(c);
					colour_check(p);
				}
			}
			else {
				if (p->r == c) {
					rotate(p);
					p->c = 'b';
					g->c = 'r';
				}
				else {
					rotate(c);
					colour_check(p);
				}
			}
		}
	}
}

void insert () {                 //functon which inserts a node into the red black tree in similar fashion to a binary search tree
	int n;
	cout <<"\nEnter the number to be inserted: \n";
	cin >>n;
	node *p = new node;
	struct node *q;
	p->d = n;
	p->c = 'r';
	p->p = NULL;
	p->l = NULL;
	p->r = NULL;
	if (head==NULL) {
		head = p;
		p->p = p;
	}
	else {
		q = head;
		while (q!=NULL) {
			if (p->d > q->d) {
				if (q->r == NULL) {
					p->p = q;
					q->r = p;
					break;
				}
				q = q->r;
			}
			else {
				if (q->l == NULL) {
					p->p = q;
					q->l = p;
					break;
				}
				q = q->l;
			}
		}
		colour_check(p);
	}
}

int main () {
	int s;
	while (1) {
		cout <<"Press the button corresponding to the operation to be executed - \n";
		cout <<"1)Insert element\n2)Print the elements\n3)Search a node\n4)Exit\n";
		cin >>s;
		if (s==1) {
			insert();
		}
		else if (s==2) {
			cout <<"\n";
			print(head,0);
			cout <<"\n\n";
		}
		else if (s==3) {
			search();
		}
		else if (s==4) {
			cout<< "\n\n*********************************************\n|  THANKS FOR USING KETAN'S RED-BLACK TREE  |\n*********************************************\n";
			return 0;
		}
		else {
			cout <<"\nPlease enter the correct number from the list\n";
		}
	}
	return 0;
}