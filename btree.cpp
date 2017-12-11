#include <iostream>
using namespace std;

#define A 3

struct node {                          //structure which contains the data in the node of the btree
	int key[2*A-1];                    //array of keys
	int number;                        //number of keys
	struct node *child[2*A];           //child pointers from a node
	struct node *parent;               //parent pointer of a node
}*head;                                //pointer which always points to the head node

void print (struct node*p, int space) {  //print function of the btree which uses recursion
	int i;
	if (p) {
		print(p->child[p->number],space+5);
		for (i=p->number-1;i>=0;i--) {
			for(int j=0;j<space;j++) {
				cout<<" ";
			}
			cout<<p->key[i]<<"\n";
			print(p->child[i],space+5);
		}
	}
}

void give_it_to (struct node *q,struct node *r,int d) {   //adding a key to the existing node and giving the newly formed child to the node when split is called
	int i = q->number-1;
	while (i!=-1 && q->key[i]>=d) {
		q->key[i+1] = q->key[i];
		q->child[i+2] = q->child[i+1];
		i--;
	}
	q->key[i+1] = d;
	q->child[i+2] = r;
	q->number++;
}

void donate (struct node *p,int i,int j) { //i is the acceptor and j is the donor index
	struct node *c1,*c2;
	int k;
	c1 = p->child[i], c2 = p->child[j]; 
	if (j>i) {
		c1->key[A-1] = p->key[i];
		c1->child[A] = c2->child[0];
		if (c2->child[0]) {
			c2->child[0]->parent = c1;
		}
		p->key[i] = c2->key[0];
		c1->number++;
		for (k=0;k<c2->number-1;k++) {
			c2->key[k] = c2->key[k+1];
			c2->child[k] = c2->child[k+1];
		}
		c2->child[k] = c2->child[k+1];
		c2->number--;
	}
	else {
		c1->child[A+1] = c1->child[A];
		for (k=A;k>=0;k--) {
			c1->key[k] = c1->key[k-1];
			c1->child[k] = c1->child[k-1]; 
		}
		c1->key[0] = p->key[i-1];
		p->key[i-1] = c2->key[c2->number-1];
		c1->child[0] = c2->child[c2->number];
		if (c1->child[0]) {
			c1->child[0]->parent = c1;
		}
		c1->number++;
		c2->child[c2->number] = NULL;
		c2->number--;
	}
}

struct node *merge (struct node *p,int i) {     //merges two childs into one
	int t = i-1,j;
	if (i==0) {
		t = 0;
		i = 1;
	}
	p->child[t]->key[A-1] = p->key[t];
	p->child[t]->number++;
	for (j=0;j<A-1;j++) {                         //copies all the node data of the sibling into one child and then deletes the sibling
		p->child[t]->key[j+A] = p->child[i]->key[j];
		p->child[t]->child[j+A] = p->child[i]->child[j];
		if (p->child[t]->child[j+A]) {
			p->child[t]->child[j+A]->parent = p->child[t];
			p->child[i]->child[j] = NULL;
		}
		p->child[t]->number++;
	}
	p->child[t]->child[2*A-1] = p->child[i]->child[A-1];
	if (p->child[t]->child[2*A-1]) {
		p->child[t]->child[2*A-1]->parent = p->child[t];
		p->child[i]->child[A-1] = NULL; 
	}
	if (p->parent ==NULL && p->number == 1) {
		head = p->child[t];
		head->parent = NULL;
		return head;
		delete(p);
		delete(p->child[i]);
	}
	else {
		delete(p->child[i]);
		for (j=t;j<p->number-1;j++) {
			p->key[j] = p->key[j+1];
			p->child[j+1] = p->child[j+2]; 
		}
		p->child[p->number] = NULL;
		p->number--;
	}
	return p->child[t];
}

struct node *split_it (struct node *p) {    //function which splits a overloaded node into two 
	int i;
	struct node *l = NULL;
	if (p!=head && p->parent->number==2*A-1) {
		l = split_it(p->parent);
	}
	struct node *r = new node;
	for (i=A;i<2*A-1;i++) {
		r->key[i-A] = p->key[i];
		r->child[i-A] = p->child[i];
		if (p->child[i]!=NULL) {
			p->child[i]->parent = r;
		}
		p->child[i] = NULL;
		p->number--;
		r->number++;
	}
	p->number--;
	r->child[A-1] = p->child[2*A-1];
	if (p->child[2*A-1]) {
		p->child[2*A-1]->parent = r;
	}
	p->child[2*A-1] = NULL;
	r->parent=p->parent;
	if (p==head) {
		struct node *q = new node;
		head = q;
		q->key[0] = p->key[A-1];
		q->number = 1;
		q->child[0] = p;
		q->child[1] = r;
		r->parent = q;
		p->parent = q;
		return r;
	}
	if (l==NULL) {
		give_it_to(p->parent,r,p->key[A-1]);
	}
	else {
		if (p->key[A-1]>=l->key[0]) {
			give_it_to(l,r,p->key[A-1]);
			return r;
		}
		give_it_to(p->parent,r,p->key[A-1]);
	}
	return r;
}

void insert (struct node *p,int d) {            //insert function of the btree
	if (head == NULL) {
		struct node *m = new node;
		m->key[0] = d;
		m->number = 1;
		m->parent = NULL;
		head = m;
		return;
	}
	int j;
	if (p->child[p->number] == NULL) {          //if the node is a leaf node
		if (p->number==2*A-1) {                 //if the node is overloaded then the node is split into two 
			j = p->key[A-1];
			struct node *r = split_it(p);
			if (d>=j) {
				insert(r,d);
				return;
			}
			else {
				insert(p,d);
				return;
			}	 
		}
		else {
			for (j=p->number-1; j!=-1&&p->key[j]>d ;j--) {
				p->key[j+1] = p->key[j];
			}
			p->number++;
			p->key[j+1] = d;
		}
	}
	else {
		for (j=p->number-1; j!=-1&&p->key[j]>d ;j--) {
		}
		insert(p->child[j+1],d);
	}
}

void search (int d) {                         //function to search a key in the btree which uses similar method to a binary search tree
	if (head==NULL) {
		cout<<"\nThere are no elements in the tree\n";
		return;
	}
	int i;
	struct node *p = head;
	while(p) {
		for (i=0;i<p->number;i++) {
			if (p->key[i] == d) {
				cout<<"\nKey found!\n";
				return;
			}
			else if (p->key[i]>d) {
				p = p->child[i];
				break;
			}
			else if (i == p->number-1) {
				p = p->child[i+1];
				break;
			}
		}
	}
	cout<<"\nThe given key is not there in the list\n";
	return;
}

void del_ele (struct node *p,int d) { //function which deletes a key from the btree00
	int i,t;
	struct node *q;
	if (p->number==A-1 && p->parent!=NULL) {        //if the node has minimum number of keys then the node is sent a key from the sibline or merged with the sibling
		q = p->parent;
		for (i=0;i<q->number;i++) {
			if (q->key[i]>p->key[0]) {
				break;
			}
		}
		if (i!=q->number && q->child[i+1]->number>A-1) {
			donate(q,i,i+1);
		}
		else if (i!=0 && q->child[i-1]->number>A-1) {
			donate(q,i,i-1);
		}
		else {
			p = merge(q,i);
		}
	}
	if (p->child[0]==NULL) {                               //if the key is in a leaf node then it is directly deleted
		if (p->key[0]>d || p->key[p->number-1]<d) {
			cout<<"\nSorry, but the given key is not present in the B tree\n";
			return;
		}
		for (i=0;i<p->number-1;i++) {
			if (p->key[i]<d && p->key[i+1]>d) {
				cout<<"\nSorry, but the given key is not present in the B tree\n";
				return;
			}
			if (p->key[i]>=d)
				p->key[i] = p->key[i+1];
		}
		p->number--;
	}
	else {                                     //if the present node is not an internal node then the presence of the key is checked first
		for (i=0;i<p->number;i++) {
			if (p->key[i]==d) {
				break;
			}
			else if (p->key[i]>d) {
				del_ele(p->child[i],d);             //if the key is not there in the node then then child pointer is passed to the delete function where the key can be present
				return;
			}
		}
		if (i==p->number) {
			del_ele(p->child[p->number],d);
			return;
		}
		q = p->child[i];
		while (q->child[q->number]) {             //if the key is present in the node then the key with the nearest value is exchanged with the key to deleted and the delete function is called on the concerned child
			q = q->child[q->number];
		}
		p->key[i] = q->key[q->number-1];
		del_ele(p->child[i],q->key[q->number-1]); 
	}
}

int main () {
	int s,p,d;
	head = NULL;
	while (1) {
		cout <<"Press the button corresponding to the operation to be executed - \n";
		cout <<"1)Insert element\n2)Print the elements\n3)Search for a key\n4)Delete an element\n5)Exit\n";
		cin >>s;
		if (s==1) {
			cout<<"\nEnter the number you want to insert: ";
			cin>> p;
			insert(head,p);
		}
		else if (s==2) {
			cout<<"\nThe elements in the B-Tree is as follows: \n\n";
			print(head,0);
			cout<<"\n";
		}
		else if (s==3) {
			cout<<"\nEnter the element you want to search for: ";
			cin>> d;
			search(d);
		}
		else if (s==4) {
			cout<< "\nEnter the element you want to delete: ";
			cin>> d;
			del_ele(head,d);
			if (head->number == 0) {
				head=NULL;
			}
			print(head,0);
		}
		else if (s==5) {
			cout << "\nThanks for using Ketan's B-tree\n";
			return 0;
		}
		else {
			cout <<"\nPlease enter the correct number from the list\n";
		}
	}
	return 0;
}