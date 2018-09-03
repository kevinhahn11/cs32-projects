#ifndef COACHINGSTAFF_H
#define COACHINGSTAFF_H
#include <string>
#include <iostream>
typedef std::string IType;
class CoachingStaff
{
private:
	struct Node
	{
		std::string f_name;
		std::string l_name;
		IType val;
		Node* next;
		Node* prev;
	};
	Node* head;
	Node* tail;
	// Private helper functions:
	void swap(CoachingStaff& source);
	bool sameLastName(const std::string& lastName);
	void insertToTheEmptyList(const std::string& firstName, const std::string& lastName, const IType& value);

public:
	CoachingStaff(); // create an empty coaching staff list
	CoachingStaff(const CoachingStaff& source);
	~CoachingStaff();
	CoachingStaff& operator=(const CoachingStaff& source);
	bool noCoaches() const; // true if coaching staff list is empty
	int numberOfCoaches() const; // return number of elements in the list
	bool hireCoach(const std::string& firstName, const std::string& lastName, const IType& value);
	// if the full name (both first and last name) is not equal to any full name currently in the list, then
	// add it and return true. elements should be added according to their last name. 
	// elements with the same last name should be added according to their first names.
	// otherwise, make no change to the list and return false (indicating that the full name is already
	// in the list).

	bool renameCoach(const std::string& firstName, const std::string& lastName, const IType& value);
	// if the full name is equal to a full name currently in the list, then make that full name
	// no longer map to the value it currently maps to, but instead map to
	// the value of the third parameter; return true in this case. 
	// otherwise, make no change to the list and return false;

	bool hireOrRename(const std::string& firstName, const std::string& lastName, const IType& value);
	// if full name is equal to a name currently in the list, then make that full name no longer map to 
	// the value it currently maps to, but instead map to the value of the third parameter; return true
	// if the full name is not equal to any name currently in the list then add it and return true
	// this function always returns true

	bool fireCoach(const std::string& firstName, const std::string& lastName);
	// if the full name is equal to a full name currently in the list, then
	// remove the full name and value from the list and return true
	// otherwise, make no change to the list and return false

	bool coachOnStaff(const std::string& firstName, const std::string& lastName) const;
	// return true if the full name is equal to a full name currently in the list, otherwise return false

	bool findCoach(const std::string& firstName, const std::string& lastName, IType& value) const;
	// if the full name is equal to a full name currently in the list, set value to the value in
	// the list that that full name maps to, and return true.
	// otherwise, make no change to the value parameter of this function and return false

	bool whichCoach(int i, std::string& firstName, std::string& lastName, IType& value) const;
	// if 0 <= i < size(), copy into firstName, lastName, and value parameters the corresponding information of the element
	// at position i in the list and return true. 
	// otherwise leave the parameters unchanged and return false. see below for details
	void changeStaff(CoachingStaff& other);
	// exchange the contents of this list with the other one
	void dump() const;
};

// Public non-member functions below:

bool mergeStaffs(const CoachingStaff& csOne, const CoachingStaff& csTwo, CoachingStaff& csMerged);
void searchStaff(const std::string& fsearch,
	const std::string& lsearch,
	const CoachingStaff& csOne,
	CoachingStaff& csResult);
#endif