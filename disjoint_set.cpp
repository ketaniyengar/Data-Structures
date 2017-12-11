#include <iostream>
using namespace std;

void union_make (int a[]) {                //makes the parent of the tree with the smaller height to point to the parent of the tree with the larger height
	int p,c,i,j,d=0,b=0;
	cout<<"\nEnter the first number: ";
	cin>>p;
	cout<<"\nEnter the second number: ";
	cin>>c;
	i = p;
	while(a[i]!=i) {
		i = a[i];
		d++;
	}
	j = c;
	while (a[j]!=j) {
		j = a[j];
		b++;
	}
	if (d>b){
		a[j] = i;
	}
	else {
		a[i] = j;
	}
}

void find (int a[]) {                   //finds the parent of the nodes enteres and prints accordingly
	int i,j,p,c;
	cout<<"\nEnter the first number: ";
	cin>>p;
	cout<<"\nEnter the second number: ";
	cin>>c;
	i=p;
	while(a[i]!=i) {
		i = a[i];
	}
	j = c;
	while (a[j]!=j) {
		j = a[j];
	}
	if (i==j) {
		cout<<"\nBoth have the same parent: "<<i<<"\n";
		return;
	}
	cout<<"\nThe given nodes have different parents :\n"<<p<<"'s parent is "<<a[i]<<"\n"<<c<<"'s parent is "<<a[j]<<"\n\n";
}

int main () {
	int v,i,s;
	cout<<"\nEnter the number of vertices: ";
	cin>>v;
	int parent[v];
	for (i=0;i<v;i++) {
		parent[i] = i;
	}
	while(1) {
		cout<<"\nEnter the option which is needed to be executed-\n1)Union\n2)Find\n3)Printing the current parents of each element\n4)Exit\n";
		cin>>s;
		if (s==1) {
			union_make(parent);
		}
		else if (s==2) {
			find(parent);
		}
		else if (s==3) {
			cout<<"\n\nNode   Parent";
			for (i=0;i<v;i++) {
				cout<<"\n"<<i<<"    -    "<<parent[i];
			}
			cout<<"\n";
		}
		else if (s==4) {
			return 0;
		}
		else {
			cout<<"\nView the above list and enter the correct option\n";
		}
	}
	return 0;
}