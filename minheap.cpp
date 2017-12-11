#include <iostream>
using namespace std;

int heap[10000],point = 0;

void print () {                                            //function for printing the minheap
	cout<<"\nThe elements in the min heap are as follows: ";
	int i;
	for (i=1;i<=point;i++) {
		cout<<heap[i]<<" ";
	}
}

void heap_swap (int i , int j) {     //function for swapping the elements of the minheap
	int temp = heap[j];
	heap[j] = heap[i];
	heap[i] = temp;
}

void heap_check () {              //function to do necessary swaps after insertion of a node to preserve the heap property
	int i=point;
	while (i!=1 && heap[i/2] > heap[i]){     //if parent has more value than the child then it is swapped
		heap_swap(i/2,i);
		i = i/2;
	}
}

void insert_heap () {             //inserting a node into the heap
	int d;
	cout<<"\nEnter the number to be inserted: ";
	cin>>d;
	point++;
	heap[point]=d;
	heap_check();
}

void delete_min () {   //function which deletes the key with the minimum weight from the heap
	if (point==0) {
		cout<<"\nThere are no elements in the heap!\n\n";
		return;
	}
	int temp;
	heap[1] = heap[point];
	point--;
	int i = 1;
	while ((heap[2*i] < heap[i] || heap[2*i+1] < heap[i])&& i<=point/2) { //if parent has more value tham the child then its swapped
		if (2*i+1<=point) {
			if (heap[2*i] <heap[i]) {
				if (heap[2*i] > heap[2*i+1]) {
					heap_swap(2*i+1,i);
					temp = 2*i+1;
				}
				else {
					heap_swap(2*i,i);
					temp = 2*i;
				}
			}
			else if (heap[2*i+1] < heap[i]){
				heap_swap(2*i+1,i);
				temp = 2*i+1;
			}
			else {
				break;
			}
			i = temp;
		}
		else {
			if (heap[2*i] < heap[i]) {
				heap_swap(2*i,i);
				i = 2*i;
			}
		}
	}
}

int main () {
	int s;
	while (1) {
		cout<<"\n\nChoose the operation to be executed: \n1)Insert\n2)Print\n3)Print minimum key\n4)Delete minimum key\n5)Exit\n";
		cin>>s;
		switch (s) {
			case 1 : {
				insert_heap();
				break;
			}
			case 2 : {
				print();
				break;
			}
			case 3 : {
				if (point==0) {
					cout<<"\nThere are no elements in the heap\n\n";
					break;
				}
				cout<<"\nThe key with the minimum value is: "<<heap[1]<<"\n";
				break;
			}
			case 4 : {
				delete_min();
				break;
			}
			case 5 : {
				return 0;
			}
			default : {
				cout<<"\nEnter the correct number from the list\n";
			}
		}
	}
	return 0;
}