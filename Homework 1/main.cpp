#include "linkedlist.h"
#include <string>
#include <cassert>
using namespace std;
int main()
{
	cout << "Testing the insertToFront function: " << endl;
	LinkedList ls;
	ls.insertToFront("Steve");
	ls.insertToFront("Judy");
	ls.insertToFront("Laura");
	ls.insertToFront("Eddie");
	ls.insertToFront("Hariette");
	ls.insertToFront("Carl");
	for (int k = 0; k < ls.size(); k++)
	{
		string x;
		ls.get(k, x);
		cout << x << endl;
	}
	cout << "------------------";
	//////////////////////////////////////
	cout << endl << "Here is an example of printing a list and its reverse: " << endl;
	LinkedList l;
	l.insertToFront("Eric");
	l.insertToFront("Shawn");
	l.insertToFront("Topanga");
	l.insertToFront("Cory");
	l.printList();
	l.printReverse();
	cout << "------------------";
	/////////////////////////////////////////////////////////
	cout << endl << "Here is an example of the append function: " << endl;
	LinkedList e12;
	e12.insertToFront("bell");
	e12.insertToFront("biv");
	e12.insertToFront("devoe");
	cout << "e12 before appending: ";
	e12.printList();
	LinkedList e22;
	e22.insertToFront("Andre");
	e22.insertToFront("Big Boi");

	e12.append(e22);
	cout << "e12 after: ";
	e12.printList();
	string word;
	assert(e12.size() == 5 && e12.get(3, word) && word == "Big Boi");
	assert(e22.size() == 2 && e22.get(1, word) && word == "Andre");
	cout << "------------------";
	///////////////////////////////////////
	cout << endl << "Here is an example of the reverseList function: " << endl;
	LinkedList e1;
	e1.insertToFront("Sam");
	e1.insertToFront("Carla");
	e1.insertToFront("Cliff");
	e1.insertToFront("Norm");
	e1.printList();
	e1.reverseList(); // reverses the contents of e1
	e1.printList();
	string str;
	assert(e1.size() == 4 && e1.get(0, str) && str == "Sam");
	cout << "------------------";
	///////////////////////////
	cout << endl << "Here's an example of the swap function: " << endl;
	LinkedList e11;
	e11.insertToFront("A");
	e11.insertToFront("B");
	e11.insertToFront("C");
	e11.insertToFront("D");
	cout << "e11 before swap: ";
	e11.printList();
	LinkedList e21;
	e21.insertToFront("X");
	e21.insertToFront("Y");
	e21.insertToFront("Z");
	cout << "e22 before swap: ";
	e21.printList();
	e21.swap(e11); // exchange contents of e1 and e2
	cout << "e11 after swap: ";
	e11.printList();
	cout << "e22 after swap: ";
	e21.printList();
	string s;
	assert(e11.size() == 3 && e11.get(0, s) && s == "Z");
	assert(e21.size() == 4 && e21.get(2, s) && s == "B");
	cout << "------------------";
	///////////////////
	cout << endl << "Now testing the copy constructor: " << endl;
	LinkedList a;
	a.insertToFront("Bellinger");
	a.insertToFront("Stripling");
	a.insertToFront("Seager");
	cout << "List A is: ";
	a.printList();
	LinkedList b = a;
	cout << "List B is a new copy of A: ";
	b.printList();
	cout << "------------------";
	/////////////////////////
	cout << endl << "Now testing the assignment operator: " << endl;
	LinkedList c;
	c.insertToFront("Bumgarner");
	cout << "LinkedList C before reassignment to A: ";
	c.printList();
	c = a;
	cout << "LinkedList C after reassignment to A: ";
	c.printList();

	LinkedList d;
	d.insertToFront("Correa");
	d.insertToFront("Altuve");
	d.insertToFront("Springer");
	cout << "List D is: ";
	d.printList();
	cout << "------------------";
	cout << endl << "All tests succeeded" << endl;

}