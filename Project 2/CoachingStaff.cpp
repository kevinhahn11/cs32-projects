#include "CoachingStaff.h"
using namespace std;
CoachingStaff::CoachingStaff(): head(nullptr), tail(nullptr) {}
CoachingStaff::CoachingStaff(const CoachingStaff& source)
{
	if (source.tail == nullptr)
	{
		head = nullptr; tail = nullptr;
	}
	else
	{
		Node* q = source.head;
		Node* p = new Node;
		p->val = q->val;
		p->f_name = q->f_name;
		p->l_name = q->l_name;
		head = p;
		tail = p;
		q = q->next;
		while (q != nullptr)
		{
			// copy the value to the new node
			p = new Node();
			p->val = q->val;
			p->f_name = q->f_name;
			p->l_name = q->l_name;
			// now append the new node to the tail of the new list
			// and modify tail
			tail->next = p;
			p->prev = tail;
			tail = tail->next;
			q = q->next;
		}
		head->prev = nullptr; tail->next = nullptr;
	}
}
CoachingStaff& CoachingStaff::operator=(const CoachingStaff& source)
{
	if (&source == this)
		return (*this);
	CoachingStaff deepCopy(source);
	this->swap(deepCopy);

	return (*this);
}
void CoachingStaff::changeStaff(CoachingStaff& other)
{
	// use the assignment operator
	CoachingStaff temp = (*this);
	(*this) = other;
	other = temp;
	return;
}
void CoachingStaff::swap(CoachingStaff& source)
{
	Node* temp = source.head;
	source.head = this->head;
	this->head = temp;
	Node* temp2 = source.tail;
	source.tail = this->tail;
	this->tail = temp2;
	return;
}
CoachingStaff::~CoachingStaff()
{
	Node* p = this->head;
	while (p != nullptr)
	{
		Node* temp = p->next;
		delete p;
		p = temp;
	}
}
bool CoachingStaff::hireCoach(const std::string& firstName, const std::string& lastName, const IType& value)
{
	if (head == nullptr && tail == nullptr)
	{
		// List is empty
		insertToTheEmptyList(firstName, lastName, value);
		return true;
	}
	if (coachOnStaff(firstName, lastName) == true)
	{
		return false;
	}
	Node* item = new Node;
	item->val = value; 
	item->f_name = firstName; 
	item->l_name = lastName;
	if (!sameLastName(lastName))
	{
		Node* p = this->head;
		while (p != nullptr && p->l_name <= lastName)
		{
			p = p->next;
		}
		// exit the while loop when p's last name is the first 
		// occurence of a last name greater than item's last name
		if (p == this->head)
		{
			// we didn't even enter the while loop
			head->prev = item;
			item->next = head;
			head = item;
			head->prev = nullptr;
		}
		else if (p == nullptr)
		{
			// insert after the tail
			tail->next = item;
			item->prev = tail;
			tail = item;
			tail->next = nullptr;
		}
		else
		{
			// insert in the middle of the list
			item->prev = p->prev;
			p->prev = item;
			item->next = p;
			if (item->prev != nullptr)
				item->prev->next = item;
			else
				head = item;
		}
		return true;
	}
	else
	{
		// there is a name already in the list with the same last name
		Node* p = this->head;
		while (p != nullptr && p->l_name <= lastName)
		{
			if (p->l_name == lastName && p->f_name > firstName)
			{
				break;
			}
			p = p->next;
		}
		// exit the while loop when p's last name is the first 
		// occurence of a last name greater than item's last name
		if (p == this->head)
		{
			// we didn't even enter the while loop, so insert before head
			head->prev = item;
			item->next = head;
			head = item;
			head->prev = nullptr;
		}
		else if (p == nullptr)
		{
			// insert after the tail of the list
			tail->next = item;
			item->prev = tail;
			tail = item;
			tail->next = nullptr;
		}
		else
		{
			// insert in the middle of the list
			item->prev = p->prev;
			p->prev = item;
			item->next = p;
			if (item->prev != nullptr)
				item->prev->next = item;
			else
				head = item;
		}
		return true;
	}
}
int CoachingStaff::numberOfCoaches() const
{
	Node * p = this->head;
	int count = 0;
	while (p != nullptr)
	{
		p = p->next;
		count++;
	}
	return count;
}
bool CoachingStaff::noCoaches() const
{
	if (head == nullptr)
		return true;
	else
		return false;
}
bool CoachingStaff::renameCoach(const string& firstName, const string& lastName, const IType& value)
{
	if (this->noCoaches() == true)
		return false;
	if (this->coachOnStaff(firstName, lastName) == false)
		return false;
	// we know the coach is on this staff if we've reached this point. now traverse the list
	Node* p = this->head;
	while (p != nullptr)
	{
		if (p->f_name == firstName && p->l_name == lastName)
		{
			p->val = value;
			return true;
		}
		p = p->next;
	}
	return false;
}
bool CoachingStaff::findCoach(const string& firstName, const string& lastName, IType& value) const
{
	// check if the list is empty or if the coach is even on this list
	if (this->noCoaches() == true || this->coachOnStaff(firstName, lastName) == false)
		return false;
	Node* p = this->head;
	while (p != nullptr)
	{
		if (p->f_name == firstName && p->l_name == lastName)
		{
			value = p->val;
			return true;
		}
		p = p->next;
	}
	return false;
}
bool CoachingStaff::coachOnStaff(const string& firstName, const string& lastName) const
{
	// first check if the list is empty
	if (this->noCoaches() == true || this->numberOfCoaches() == 0)
		return false;
	// now we know the list is not empty
	Node *p = this->head;
	while (p != nullptr)
	{
		if (p->f_name == firstName && p->l_name == lastName)
		{
			return true;
		}
		p = p->next;
	}
	return false;
}
bool CoachingStaff::whichCoach(int i, string& firstName, string& lastName, IType& value) const
{
	if (i < 0 || i >= this->numberOfCoaches() || this->noCoaches() == true)
		return false;
	
	// i is a valid index
	int dest = i;
	Node* p = head;
	bool found = false;
	int pos = 0;
	while (p != nullptr)
	{
		if (pos == dest)
		{
			found = true;
			break;
		}
		p = p->next;
		pos += 1;
	}
	if (found == true)
	{
		firstName = p->f_name;
		lastName = p->l_name;
		value = p->val;
		return true;
	}
	return false;
}
bool CoachingStaff::hireOrRename(const std::string& firstName, const std::string& lastName, const IType& value)
{
	// this function should always return true
	Node* p = this->head;
	if (this->noCoaches() == true) 
	{
		// list is empty
		this->hireCoach(firstName, lastName, value);
		return true;
	}

	if (this->coachOnStaff(firstName, lastName) == false)
	{
		// list does not already contain the name
		this->hireCoach(firstName, lastName, value);
		return true;
	}
	else
	{
		// the name is contained somewhere in this staff
		while (p != nullptr)
		{
			if (p->f_name == firstName && p->l_name == lastName)
			{
				p->val = value;
				return true;
			}
			p = p->next;
		}
	}
	return true;
}
bool CoachingStaff::fireCoach(const std::string& firstName, const std::string& lastName)
{
	if (this->noCoaches() == true)
		return false;
	if (coachOnStaff(firstName, lastName) == false)
		return false;
	// now we've checked whether the list was empty or if it even contained the name
	Node* p = this->head;
	bool foundCoach = false;
	while (p != nullptr)
	{
		if (p->f_name == firstName && p->l_name == lastName)
		{
			foundCoach = true;
			break;
		}
		p = p->next;
	}
	if (foundCoach == true)
	{
		if (p == head && p == tail)
		{
			head = nullptr;
			tail = nullptr;
			
		}
		else if (p == head)
		{
			head = head->next;
			head->prev = nullptr;
		}
		else if (p == tail)
		{
			tail = tail->prev;
			tail->next = nullptr;
		}
		else
		{
			p->next->prev = p->prev;
			p->prev->next = p->next;
		}
		delete p;
		return true;
	}
	return false;
}
void CoachingStaff::dump() const
{
	Node* p = head;
	while (p != nullptr)
	{
		std::cerr << p->f_name << " " << p->l_name << " " << p->val << endl;
		p = p->next;
	}
	return;
}
// Private helper functions:
bool CoachingStaff::sameLastName(const std::string& lastName)
{
	Node *p = head;
	while (p != nullptr)
	{
		if (p->l_name == lastName)
			return true;
		p = p->next;
	}
	return false;
}
void CoachingStaff::insertToTheEmptyList(const std::string& firstName, const std::string& lastName, const IType& value)
{
	Node* p = new Node;
	p->f_name = firstName;
	p->l_name = lastName;
	p->val = value;
	head = p;
	tail = p;
	p->prev = nullptr;
	p->next = nullptr;
}
///////////////////////////////////////////////////////////
// public non-member functions
bool mergeStaffs(const CoachingStaff& csOne, const CoachingStaff& csTwo, CoachingStaff& csMerged)
{
	if (csMerged.noCoaches() == false)
	{
		string first; string last; IType v;
		while (csMerged.numberOfCoaches() != 0)
		{
			csMerged.whichCoach(0, first, last, v);
			csMerged.fireCoach(first, last);
		}
	}
	// csMerged is now emptied
	if (csOne.noCoaches() == true && csTwo.noCoaches() == true)
	{
		// both lists are empty, and csMerged is an empty list so don't change anything
		return true;
	}
	else if (csOne.noCoaches() == false && csTwo.noCoaches() == true)
	{
		csMerged = csOne;
		return true;
	}
	else if (csOne.noCoaches() == true && csTwo.noCoaches() == false)
	{
		csMerged = csTwo;
		return true;
	}
	// if both lists are not empty, then we've reached this line
	bool repeatedNameButDiffValue = false;
	csMerged = csOne;
	CoachingStaff list1 = csOne;
	CoachingStaff list2 = csTwo;
	int i = 0;

	while (i != list1.numberOfCoaches())
	{
		string fName;
		string lName;
		IType value1;
		IType value2;
		if (list1.whichCoach(i, fName, lName, value1) == true)
		{
			if (list2.coachOnStaff(fName, lName) == true)
			{
				if (list2.findCoach(fName, lName, value2))
				{
					if (value1 == value2)
					{
						list2.fireCoach(fName, lName);
					}
					else
					{
						csMerged.fireCoach(fName, lName);
						list2.fireCoach(fName, lName);
						repeatedNameButDiffValue = true;
					}
				}
			}
		}
		i++;
	}

	while (list2.noCoaches() == false)
	{
		string firstName; string lastName; IType v;
		list2.whichCoach(0, firstName, lastName, v);
		csMerged.hireCoach(firstName, lastName, v);
		list2.fireCoach(firstName, lastName);
	}

	if (repeatedNameButDiffValue == true)
	{
		return false;
	}
	return true;
}

void searchStaff(const std::string& fsearch,
	const std::string& lsearch,
	const CoachingStaff& csOne,
	CoachingStaff& csResult)
{
	CoachingStaff list;
	string fName; string lName;
	if (&csOne == &csResult)
		return;
	if (csResult.noCoaches() == false)
	{
		string first; string last; IType v;
		while (csResult.numberOfCoaches() != 0)
		{
			csResult.whichCoach(0, first, last, v);
			csResult.fireCoach(first, last);
		}
	}
	IType value;
	// list is now empty
	if (fsearch == "*" && lsearch == "*")
	{
		csResult = csOne; // assignment operator
		return;
	}
	else if (fsearch != "*" && lsearch != "*")
	{
		int i = 0;
		while (i != csOne.numberOfCoaches())
		{
			IType value;
			if (csOne.whichCoach(i, fName, lName, value))
			{
				if (fName == fsearch && lName == lsearch)
				{
					csResult.hireCoach(fsearch, lsearch, value);
				}
			}
			i++;
		}
	}
	else if (fsearch != "*" && lsearch == "*")
	{
		int i = 0;
		while (i != csOne.numberOfCoaches())
		{
			IType value;
			if (csOne.whichCoach(i, fName, lName, value) == true)
			{
				if (fName == fsearch)
				{
					csResult.hireCoach(fsearch, lName, value);
				}
			}
			i++;
		}
	}
	else
	{
		// lsearch != "*" and fsearch == "*"
		int i = 0;
		while (i != csOne.numberOfCoaches())
		{
			IType value;
			if (csOne.whichCoach(i, fName, lName, value) == true)
			{
				if (lName == lsearch)
				{
					csResult.hireCoach(fName, lsearch, value);
				}
			}
			i++;
		}
	}
	return;
}