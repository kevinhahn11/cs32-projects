#ifndef LINKEDLIST_HEADER
#define LINKEDLIST_HEADER
// Homework 1
#include <iostream>
#include <string>

typedef std::string ItemType;
struct Node
{
	ItemType value;
	Node *next;
};
class LinkedList
{
private:
	Node * head;
	void addToRear(ItemType v);
	void deleteAtEnd();
	void insertAtEnd();
public:
	// default constructor
	LinkedList();

	// copy constructor
	LinkedList(const LinkedList& rhs);

	// destructor
	~LinkedList();

	//assignment operator
	const LinkedList& operator=(const LinkedList& rhs);

	void insertToFront(const ItemType &val);

	// prints the linked list
	void printList() const;  // and only stop once its gone past the end of the list

							 // sets item to the value at position i in this LinkedList and return true, returns false if there is no element i
	bool get(int i, ItemType& item) const;

	// reverses the LinkedList
	void reverseList();

	// prints the linked list in reverse order
	void printReverse() const;

	// appends the values of other onto the end of this linked list.
	void append(const LinkedList& other);

	// exchange the contents of this LinkedList with the other one.
	void swap(LinkedList& other);

	// returns the number of items in the linked list
	int size() const;
};
#endif
