#include <iostream>
using namespace std;

struct node {  //structure to store the nodes and weights data in an adjacency list
	int vert;
	int w;
	node *next;
};

struct heap {   //structure on which the heap is built
	int vert1;
	int vert2;
	int weight;
};

int point=0;    //denotes the current number of elements in the heap

void heap_swap (heap heap [], int i , int j) {  //function to swap the elements in heap of structures
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

void heap_check (heap heap[]) {      //function which ensures that the heap property is retained
	int i=point;
	while (heap[i/2].weight > heap[i].weight && i!=1) {  //if parent has higher value than the child then both are swapped
		heap_swap(heap,i/2,i);
		i = i/2;
	}
}

void insert_heap (heap heap[], node *p, int i) {   //function which inserts element in the heap
	point++;
	heap[point].vert1=i;
	heap[point].vert2=p->vert;
	heap[point].weight = p->w;
	heap_check(heap);
}

void delete_min (heap heap[]) {   //function which deletes the key with the minimum weight from the heap
	int temp;
	heap[1] = heap[point];
	point--;
	int i = 1;
	while ((heap[2*i].weight < heap[i].weight || heap[2*i+1].weight < heap[i].weight)&& i<=point/2) { //if parent has more value tham the child then its swapped
		if (2*i+1<=point) {
			if (heap[2*i].weight <heap[i].weight) {
				if (heap[2*i].weight > heap[2*i+1].weight) {
					heap_swap(heap,2*i+1,i);
					temp = 2*i+1;
				}
				else {
					heap_swap(heap,2*i,i);
					temp = 2*i;
				}
			}
			else if (heap[2*i+1].weight < heap[i].weight){
				heap_swap(heap,2*i+1,i);
				temp = 2*i+1;
			}
			else {
				break;
			}
			i = temp;
		}
		else {
			if (heap[2*i].weight < heap[i].weight) {
				heap_swap(heap,2*i,i);
				i = 2*i;
			}
		}
	}
}

void insert (node *head[],int u, int v,int w) {  //inserting the vertices and the weights data in an adjacency list
	node *p = new node;
	node *q = new node;
	p->vert=v;
	p->w=w;
	p->next=NULL;
	q->vert=u;
	q->w=w;
	q->next=NULL;
	if (head[u] == NULL){
		head[u]=p;
	}
	else {
		p->next=head[u];
		head[u] = p;
	}
	if (head[v] == NULL){
		head[v]=q;
	}
	else {
		q->next=head[v];
		head[v] = q;
	}
}

void insertans (node *head[],int u, int v,int w) {   //inserts node into the answer adjacency list
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

int main () {
	int n,i,u,v,w,edge = 0;
	cout << "\033[0m\033[37mEnter the number of nodes in the graph (starting from node 0): ";
	cin >> n;
	int visit[n] = {0};
	int visitans[n] = {0};
	struct node *q = new node;
	struct node **head;
	head = new struct node*[n];
	struct node **answer;
	answer = new struct node*[n];
	cout << "Enter the vertices and their weights (vertex1 vertex2 weight)\n";
	cout << "NOTE : ENTER -1 TO STOP\n";
	while (1){                                                                            //getting the input from the user
		cin>>u;
		if (u==-1){
			break;
		}
		cin >>v>>w;
		insert(head,u,v,w);
		edge++;
	}
	struct heap heap[edge+1];
	edge = 0;
	i=0;
	while (1) {
		if (visit[i]==0) {                                                         //preventing duplicates from enetering the heap
			q = head[i];
			visit[i]=1;
			while (q!=NULL) {
				if (visit[q->vert]==0) {
					insert_heap(heap,q,i);
				}
				q = q->next;
			}
		}
		if (point==0) {                                                            //exits if heap is empty
			break;
		}
		if (visit[heap[1].vert1]==0 || visit[heap[1].vert2]==0) {                 //adds new elements to answer adjacency list
			insertans(answer,heap[1].vert1,heap[1].vert2,heap[1].weight);
			edge++;
		}
		i=heap[1].vert2;
		delete_min(heap);                                                           //deleting the minimum element from the heap
	}
	if (edge!=n-1) {                                                              //prints an error message if edges != no(vertices)-1 which is the condition for a tree
		cout<<"\n\033[4m\033[1m\033[31mInvalid input, check and try again!\n\n";
		delete q;
		delete []head;
		main();
		return 0;
	}
	cout <<"\nThe answer is as follows: ";                                        //prints the final answer
	cout <<"\n\n Start    End     Weight\n";
	cout <<"vertex   vertex\n";
	for (i=0;i<n;i++){
		q=answer[i];
		while (q!=NULL){
			cout <<"  "<<i<<"        "<<q->vert<<"         "<<q->w<<" "<<"\n";
			q = q->next;
		}
	}
	delete q;
	delete []head;
	return 0;
}