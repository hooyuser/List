#include "List.h"
#include <iostream>

using namespace std;

void output(int &a)
{
	cout << a << " ";
}

int main()
{
	List<int> listA;
	listA.insertAsLast(1);
	listA.insertAsLast(2);

	listA.insertAsLast(3);

	listA.insertAsLast(6);

	listA.insertAsLast(7);

	List<int> listB;
	listB.insertAsLast(2);
	listB.insertAsLast(4);


	listA.traverse(output);
	cout << endl;
	listB.traverse(output);
	cout << endl;

	listA.merge(listB);

	listA.traverse(output);

	cin.get();
	return 0;
}


