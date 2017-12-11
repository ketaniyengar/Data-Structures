#include <iostream>
#include <climits>
#include <cstring>
using namespace std;

int point = 0;

struct node {
	int vert;
	int w;
	struct node *next;
};

struct heap {
	int v;
	int w;
};

void heap_swap (heap heap [], int i , int j) {
	int temp_vert = heap[j].v;
	heap[j].v = heap[i].v;
	heap[i].v = temp_vert;
	int weight = heap[j].w;
	heap[j].w = heap[i].w;
	heap[i].w = weight;
}

void heap_check (heap heap[]) {
	int i=point;
	while (heap[i/2].w > heap[i].w && i!=1) {
		heap_swap(heap,i/2,i);
		i = i/2;
	}
}

void insert_heap (heap heap[], int v,int m) {
	point++;
	heap[point].v= v;
	heap[point].w = m;
	heap_check(heap);
}

void delete_min (heap heap[]) {
	if (point==1) {
		point--;
		return;
	}
	int temp;
	heap[1] = heap[point];
	point--;
	int i = 1;
	while ((heap[2*i].w < heap[i].w || heap[2*i+1].w < heap[i].w)&& i<=point/2) {
		if (2*i+1<=point) {
			if (heap[2*i].w <heap[i].w) {
				if (heap[2*i].w > heap[2*i+1].w) {
					heap_swap(heap,2*i+1,i);
					temp = 2*i+1;
				}
				else {
					heap_swap(heap,2*i,i);
					temp = 2*i;
				}
			}
			else if (heap[2*i+1].w < heap[i].w){
				heap_swap(heap,2*i+1,i);
				temp = 2*i+1;
			}
			else {
				break;
			}
			i = temp;
		}
		else {
			if (heap[2*i].w < heap[i].w) {
				heap_swap(heap,2*i,i);
				i = 2*i;
			}
		}
	} 
}

void insert (node *head[],int u, int v,int w) {
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

int main () {
	int n,i,u,v,w;
	cout << "Enter the number of nodes in the graph (starting from node 0): ";
	cin >> n;
	int a[n];
	int visit[n] = {};
	for (i=0;i<n;i++) {
		a[i] = INT_MAX;
	}
	struct node *q = new node;
	struct node **head;
	head = new struct node*[n];
	cout << "Enter the vertices and their weights (vertex1 vertex2 weight)\n";
	cout << "NOTE : ENTER -1 TO STOP\n";
	while (1){
		cin>>u;
		if (u==-1){
			break;
		}
		cin >>v>>w;
		insert(head,u,v,w);
	}
	for (i=0;i<n;i++) {
		cout<<"\n"<<i<<"  "<<a[i];
	}
	struct heap heap[n];
	cout <<"\nEnter the vertex with respect to which the distance has to be minimised (0 to "<<n-1<<"): ";
	cin >>i;
	a[i] = 0;
	while (1) {
		if (visit[i]==0) {
			q = head[i];
			while (q!=NULL) {
				visit[i] = 1;
				w = a[i] + q->w;
				if (visit[q->vert]==0){
					insert_heap(heap,q->vert,w);
				}
				q = q->next;
			}
		}
		if (point == 0) {
			cout<<"p\n";
			break;
		}
		if (a[heap[1].v] > heap[1].w) {
			cout<< "hey\n";
			a[heap[1].v] = heap[1].w;
		}
		i = heap[1].v;
		delete_min(heap);
	}
	cout<<"\n";
	for (i=0;i<n;i++) {
		cout<<"\n"<<i<<"  "<<a[i];
	}
	delete []head;
	delete q;
}