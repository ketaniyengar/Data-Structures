#include <iostream>
using namespace std;

struct node {              //structure to store the nodes and weights data in an adjacency list
	int vert;
	int w;
	struct node *next;
};

int point = 0;            //denotes the current number of elements in the heap

struct heap {             //structure on which the heap is built
	int vert1;
	int vert2;
	int weight;
};

void heap_swap (heap heap [], int i , int j) {   //function to swap the elements in heap of structures
	int temp_vert1 = heap[j].vert1;
	heap[j].vert1 = heap[i].vert1;
	heap[i].vert1 = temp_vert1;
	int temp_vert2 = heap[j].vert2;
	heap[j].vert2 = heap[i].vert2;
	heap[i].vert2 = temp_vert2;
	int weight = heap[j].weight;
	heap[j].weight = heap[i].weight;
	heap[i].weight = weight;
}

void heap_check_inverse (heap heap[],int m) {   //checking the positions of the elements and performing swaps if necessary during heap sort   
	int i = 1,temp;
	temp = 2;
	while (temp<=m) {
		if ((temp+1<=m)&& (heap[temp+1].weight > heap[temp].weight)) {
			temp = temp+1;
		}
		if (heap[i].weight > heap[temp].weight){
			break;
		}
		else {
			heap_swap(heap,i,temp);
		}
		i = temp;
		temp =2*temp;
	}
}

void sort_it_up (heap heap[]) {     //sorting all the contents that has been inserted into the heap using heap sort
	int i = point;
	while (i!=1) {
		heap_swap(heap,1,i);
		i--;
		heap_check_inverse (heap,i);   //reforming the heap so that it retains its properties
	}
}

void heap_check (heap heap[]) {    //making the heap intact so that it retains its properties
	int m = point;
	while (heap[m/2].weight < heap[m].weight && m!=1) {
		heap_swap(heap,m/2,m);
		m = m/2;
	}
}

void insert_heap (heap heap[], node *p, int i) {    //inserting an element into the heap
	point++;
	heap[point].vert1=i;
	heap[point].vert2=p->vert;
	heap[point].weight = p->w;
	heap_check(heap);
}

void insert (node *head[],int u, int v,int w) {   //inserting the vertices and edges info into an adjacency list
	node *p = new node;
	p->vert=v;
	p->w=w;
	p->next=NULL;
	if (head[u] == NULL){
		head[u]=p;
	}
	else {
		p->next=head[u];
		head[u] = p;
	}
}

int union_find (heap heap[],int i, int parent[]) {   //function to find the parents of the nodes concerned and merging it if it doesn't form a circle
	int len=0,bred=0;
	int u = heap[i].vert1;
	int v = heap[i].vert2;
	while (parent[u]!=u) {
		u = parent[u];
		len++;
	}
	while (parent[v]!=v) {
		v = parent[v];
		bred++;
	}
	if (u==v) {
		return 1;
	}
	if (len>bred) {
		parent[v]=parent[u];
	}
	else if (bred>=len) {
		parent[u]=parent[v];
	}
	return 0;
}


int main (){
	int n,i,u,v,w,edge=0;
	cout << "\033[0m\033[37mEnter the number of nodes in the graph (starting from node 0): ";
	cin >> n;
	struct node *q;
	struct node **head;
	head = new struct node*[n];
	int parent[n];
	for (i=0;i<n;i++) {
		parent[i] = i;
	}
	struct node **answer;
	answer = new struct node*[n];         
	cout << "Enter the vertices and their weights (vertex1 vertex2 weight)\n";
	cout << "NOTE : ENTER -1 TO STOP\n";
	i=0;
	while (1){                      //getting input from the user
		cin>>u;
		if (u==-1){
			break;
		}
		cin >>v>>w;
		insert(head,u,v,w);
		i++;
	}
	int k =i;
	struct heap heap[i+1];
	for (i=0;i<n;i++) {
		q = head[i];
		while (q!=NULL) {
			insert_heap (heap,q,i);
			q = q->next;
		}
	}
	cout <<"\n";
	sort_it_up(heap);                   //sorting the heap using heapsort
	for (i=1;i<k+1;i++) {
		if (union_find (heap,i,parent)==0) {            //finding the parents of two nodes to check whether it is mergeable or not
			insert(answer,heap[i].vert1,heap[i].vert2,heap[i].weight);
			edge++;
		}
	}
	if (edge!=n-1) {
		cout<<"\n\033[4m\033[1m\033[31mInvalid input, check and try again!\n\n";    //printing invalid input if edges != no(vertices)-1 which is the condition for a tree
		delete q;
		delete []head;
		delete []answer;
		return 0;
	}	
	cout <<"\nThe answer is as follows: ";                   //printing the answer
	cout <<"\n\n Start    End     Weight\n";
	cout <<"vertex   vertex\n";
	for (i=0;i<n;i++){
		q=answer[i];
		while (q!=NULL){
			cout <<"  "<<i<<"        "<<q->vert<<"         "<<q->w<<" "<<"\n";
			q = q->next;
		}
	}
	delete []head;
	return 0;
}