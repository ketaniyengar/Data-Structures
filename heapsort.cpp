#include <iostream>
using namespace std;

int p=0;

void heap_swap (int A[], int i, int j) {
	int temp = A[i];
	A[i]=A[j];
	A[j]=temp;
}

void heap_check (int A[]) {
	int i = p;
	while (A[i/2]<A[i] && i/2>=1) {
		heap_swap(A,i/2,i);
		i = i/2;
	}
}

void insert_heap (int k,int A[]) {
	p++;
	A[p] = k;
	heap_check(A);
}

void heap_check_inverse (int heap[],int m) {
	int i = 1,temp;
	temp = 2;
	while (temp<=m) {
		if ((temp+1<=m)&& (heap[temp+1] > heap[temp])) {
			temp = temp+1;
		}
		if (heap[i] > heap[temp]){
			break;
		}
		else {
			heap_swap(heap,i,temp);
		}
		i = temp;
		temp =2*temp;
	}
}

void heap_sort (int heap[]) {
	int i = p;
	while (i!=1) {
		heap_swap(heap,1,i);
		i--;
		heap_check_inverse (heap,i);
	}
}

int main () {
	int n,k,i;
	cout <<"Enter the number of elements in the array: ";
	cin >>n;
	int B[n+1];
	cout <<"Enter the elements of the array: \n";
	for (i=0;i<n;i++) {
		cin >>k;
		insert_heap(k,B);
	}
	heap_sort(B);
	for (i=1;i<n+1;i++) {
		cout <<" "<<B[i];
	}
}