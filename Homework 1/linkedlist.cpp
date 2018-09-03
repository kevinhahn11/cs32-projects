// LinkedList implementation
#include "linkedlist.h"
using namespace std;
// default constructor
LinkedList::LinkedList() : head(nullptr) {}
// copy constructor
LinkedList::LinkedList(const LinkedList& rhs)
{
	this->head = nullptr;
	Node* prev = nullptr;  // we need a pointer to the previous Node
						   // Iterate through each of the other Nodes
	Node* n = rhs.head;
	while (n != nullptr) {
		Node* newBranch = new Node;
		newBranch->value = n->value;
		if ((prev != nullptr))
			prev->next = newBranch;
		if (!(head != nullptr)) // head == nullptr
			head = newBranch;
		prev = newBranch;
		n = n->next;
	}
	prev->next = nullptr;
}
// destructor
LinkedList::~LinkedList()
{
	Node* p = head;
	while (p != nullptr)
	{
		Node* temp = p->next;
		delete p;
		p = temp;
	}
}
//assignment operator
const LinkedList& LinkedList::operator=(const LinkedList& rhs)
{
	if (&rhs == this)
		return (*this); // sanity check
	int size = this->size();
	int otherSize = rhs.size();
	if (size > otherSize)
	{
		int diff = size - otherSize;
		for (int i = 0; i < diff; i++)
			this->deleteAtEnd();
		// now both lists are of equal size
		Node* source = this->head;
		Node* dest = rhs.head;
		while (dest != nullptr)
		{
			source->value = dest->value;
			source = source->next;
			dest = dest->next;
		}
		return (*this);
	}
	else if (size < otherSize)
	{
		int diff = otherSize - size;
		for (int i = 0; i < diff; i++)
			this->insertAtEnd();
		// Lists are now of equal size
		Node* source = this->head;
		Node* dest = rhs.head;
		while (dest != nullptr)
		{
			source->value = dest->value;
			source = source->next;
			dest = dest->next;
		}
		return (*this);
	}
	else
	{
		// Lists are of equal size. Easiest case
		Node* source = this->head;
		Node* dest = rhs.head;
		while (dest != nullptr)
		{
			source->value = dest->value;
			source = source->next;
			dest = dest->next;
		}
		return (*this);
	}
}
// inserts val at front of the list
void LinkedList::insertToFront(const ItemType &val)
{
	Node* p;
	p = new Node;
	p->value = val;
	p->next = head;
	head = p;
}
// prints the linked list
void LinkedList::printList() const
{
	if (this->size() == 0)
		return; // professor said we do not need to print a newline if list is empty
	Node* p;
	p = head; // p points to 1st node
	while (p != nullptr) // p must point to valid location
	{
		cout << p->value << " ";
		p = p->next; // do not use p++ to move forward in linked list. you must use next
	} // using this condition, loop will process EVERY node in the list
	  // and only stop once its gone past the end of the list
	cout << endl;
}
// sets item to the value at position i in this LinkedList and return true, returns false if there is no element i:
bool LinkedList::get(int i, ItemType& item) const
{
	if (i >= this->size() || i < 0)
		return false; // make sure we're in a valid boundary
	Node* p = head;
	int k = 0;
	while (k != i && p != nullptr)
	{
		p = p->next;
		k++;
	}
	if (k == i)
	{
		item = p->value;
		return true;
	}
	return false;
}
// reverses the LinkedList:
void LinkedList::reverseList()
{
	if (this->size() <= 1)
		return;
	else
	{
		Node* prevNode = nullptr;
		Node* currentNode = head;
		Node* nextNode;
		while (currentNode != nullptr) // nullptr means no more nodes in list
		{
			nextNode = currentNode->next;
			currentNode->next = prevNode;
			prevNode = currentNode;
			currentNode = nextNode;
		}
		head = prevNode;
	}
	return;
}
// prints the linked list in reverse order:
void LinkedList::printReverse() const
{
	if (this->size() == 0)
		return; // professor said we do not need to print a newline if list is empty
	LinkedList deepCopy = (*this);
	deepCopy.reverseList();
	deepCopy.printList();

	return;
}
/*
// appends the values of other onto the end of this linked list:
void LinkedList::append(const LinkedList& other)
{
	Node* tracer = other.head;
	while (tracer != nullptr)
	{
		this->addToRear(tracer->value);
		tracer = tracer->next;
	}
}
*/
void LinkedList::append(const LinkedList &other)
{
	// Reach the last node of the linked list
	Node* iter = head;
	while (iter->next != nullptr)
		iter = iter->next;
	// Create a copy of the other linked list
	LinkedList other_ll(other);
	// Connect the end node of 'this' with the head of our copy
	// of other.
	iter->next = other_ll.head;
	other_ll.head = nullptr;
}
// exchange the contents of this LinkedList with the other one:
void LinkedList::swap(LinkedList& other)
{
	LinkedList temp = (*this);
	(*this) = other;
	other = temp;
	return;
}
// returns the number of items in the linked list:
int LinkedList::size() const
{
	int count = 0;
	Node* p = head;
	while (p != nullptr)
	{
		count++;
		p = p->next;
	}
	return count;
}

// Helper function for the append function
void LinkedList::addToRear(ItemType v)
{
	if (head == nullptr) // list is empty
	{
		head->value = v;
		insertToFront(v);
	}
	else
	{
		Node* p;
		p = head; // start at top node
		while (p->next != nullptr) // loop continues until p points at very last node of list
		{
			p = p->next;
		}
		// after this loop, p points at the last node
		Node* n = new Node;
		n->value = v;
		p->next = n;
		n->next = nullptr;
	}
}
// Additional Helper functions
void LinkedList::insertAtEnd()
{
	Node* ptr = new Node;
	ptr->value = "";
	ptr->next = nullptr;
	if (head == nullptr)
		head = ptr;
	// traverse the list
	else
	{
		Node* temp = head;
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		temp->next = ptr;
	}
}
void LinkedList::deleteAtEnd()
{
	Node* ptr = head;
	Node* prev = nullptr;
	if (head == nullptr)
		return; // empty list
	else if (head->next == nullptr)
	{
		ptr = head;
		head = nullptr;
		delete ptr;
		return;
	}
	else
	{
		while (ptr->next != nullptr)
		{
			prev = ptr;
			ptr = ptr->next;
		}
		prev->next = nullptr;
		delete ptr;
	}
	return;
}