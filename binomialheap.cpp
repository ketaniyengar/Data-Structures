#include <iostream>
using  namespace std;

struct node {                 //structure to store all the data needed in the node and the pointers associated with it
	int data;                 //key
	int degree;               //degree of the binomial tree
	struct node *parent;
	struct node *child;
	struct node *sibling;
}*head,*temp;                 //head is the primary pointer for accessing the root list and temp is used here for deleting minimum

void handle (struct node *p) {   //print and handle function together attempt to print the binomial heap in a recursive manner
	if (p==NULL) {
		return;
	}
	cout <<"\n"<<p->data;
	handle(p->child);
	handle(p->sibling);
}

void print_heap () {
	struct node *p=head;
	while (p!=NULL) {
		cout<<"\n"<<p->data<<"--"<<p->degree;        //printing the degree of the tree
		handle(p->child);
		p = p->sibling;
	}
}

struct node *insert_block (struct node *p) {        //function to insert the nodes in order into temp when delete minimum is called
	struct node *m;
	while (p!=NULL) {
		m =  p->sibling;
		p->sibling = temp;
		temp = p;
		p = m;
	}
}

void binomial_union () {                            //Function to convert the tree network into a valid binomial heap
	if (head == NULL || head->sibling==NULL) {
		return;
	}
	struct node *p,*q,*r; //p denotes the previous node q the current node and r is the next node
	p = NULL;
	q = head;
	r = q->sibling;
	while (r!=NULL) {     //the process ends when the next node is null
		if (q->degree != r->degree || (r->sibling!=NULL)&&(r->degree == r->sibling->degree)) {   //if degree is not same then they can't be merged and if the degree is same but if even the next node has the same degree then its advisable to merge the next node instead of present in order to maintain the degree order
			p = q;
			q = r;
			r = r->sibling;
		}
		else {                                  //if the degrees are same then they are merged according to the value on the top
			if (q->data > r->data) {
				q->parent = r;
				q->sibling = r->child;
				r->child = q;
				r->degree++;
				if (p==NULL) {
					head = r;
				}
				else {
					p->sibling = r;
				}
				q = r;
				r = q->sibling;
			}
			else {
				q->sibling = r->sibling;
				r->sibling = q->child;
				r->parent = q;
				q->child = r;
				q->degree++;
				if (p==NULL) {
					head = q;
				}
				else {
					p->sibling = q;
				}
				r = q->sibling;
			}
		}
	}
}

void binomial_merge () {                   //Function to merge the contents of temp and head into head
	struct node *p,*q,*pl,*pn,*r;
	p = head;
	q = temp;
	if (head==NULL) {                      //if head is NULL temp is made to be the main tree netwrok to be dealt with
		if (temp==NULL) {
			head = NULL;
			return;
		}
		head = temp;
		return;
	}
	else if (temp==NULL) {                //if only temp is null then head already contains a valid heap with the minimum key deleted
		return;
	}
	r = q->sibling;
	pn = p->sibling;
	while (p!=NULL && q!=NULL) {          //merging the two networks with p denoting the head tree network and q denoting the temp tree network
		if (p->degree == q->degree) {     //if both the nodes have the same degree they can be linked as siblings of each other
			r = q->sibling;
			q->sibling = p->sibling;
			p->sibling = q;
			pl = p;
			p = q;
			pn = q->sibling;
			q = r;			
		}
		else if (p->degree > q->degree) {  //if p's degree is more q is inserted behind p to maintain the degree balance
			r = q->sibling;
			if (pl==NULL) {
				head = q;
			}
			else {
				pl->sibling = q;
			}
			q->sibling = p;
			pl = q;
			q = r;
		}
		else {                            //if q's degree is more then p is increamented until p lands up into a node with expected degree
			if (p->sibling==NULL) {       //if p is null and q's degree is more then p is no longer able to cope up with the high degree of q thus q is directly inserted in the front
				p->sibling = q;
				return;
			}
			pl = p;
			p = pn;
			pn = pn->sibling;
		}
	}
}

void insert () {                                        //inserting a node at the begining of the heap root list and then traversing it to arrange it
	int a;
	cout<< "Enter the number you want to insert: ";
	cin>> a;
	struct node *p = new node;                         //creating a new node named 'p'
	p->data = a;
	p->degree = 0;
	p->parent = NULL;
	p->child = NULL;
	p->sibling = head;
	head = p;
	binomial_union();                                  //calling the union function to arrange the nodes to form a valid binomial heap
}

void print_min () {                                   //Function to print the key with minimum value
	if (head==NULL) {
		cout<<"\nThere is no element in the heap\n";
		return;
	}
	struct node *p;
	int min;
	p = head;
	min = p->data;
	while (p!=NULL) {                                 //traversing the root list alone and then printing the least among those keys
		if (min>p->data) {
			min = p->data;
		}
		p = p->sibling;
	}
	cout<<"\nThe element with the minimum value is: "<<min<<"\n";
}

void delete_min () {                                  //Function to delete the key with the minimum value
	if (head==NULL) {
		cout<<"\nThere are no elements in the list\n";
		return;
	}
	int min = head->data; 
	struct node *p,*q,*r;
	p = head;
	while (p!=NULL) {                                   //searching for the minimum key
		if (p->sibling!=NULL) { 
			if (p->sibling->data < min) {
				min = p->sibling->data;
				q = p;
				r = p->sibling;
			}
		}
		p = p->sibling;
	}                                                 
	if (r==NULL) {
		r = head;
	}
	if (q==NULL) {                                    //deleting the tree which contains the node with the minimum value 
		head = r->sibling;
		if (r->sibling==NULL) {
			head = NULL;
		}
	}
	else {
		q->sibling = r->sibling;
	}
	if (r->child) {
		r->child->parent = NULL;
	}
	insert_block(r->child);                          //travsersing the child linked list of the concerned tree with the minimum key and then inserting all of it into temp
	binomial_merge();                                //merging head and all of temp into temp to get a single tree network
	binomial_union();                                //converting the tree network into a valid heap by merging the tree with equal degree
}

int main () {
	int s;
	head = NULL;
	temp = NULL;
	while (1) {
		cout<< "\nEnter the desired operation from the list- \n";
		cout<< "1)Insert an element\n2)Print the whole list\n3)Print the minimum\n4)Delete minimum\n5)Exit\n";
		cin>> s;
		switch(s) {
			case 1 : {
				insert();
				break;
			}
			case 2 : {
				print_heap();
				break;
			}
			case 3 : {
				print_min();
				break;
			}
			case 4 : {
				delete_min();
				temp = NULL;
				break;
			}
			case 5 : {
				return 0;
			}
			default :  {
				cout<< "Select the correct option from the list";
			}
		}
	}
}