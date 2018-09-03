#ifndef TREE
#define TREE
#include <iostream>
#include <string>
typedef std::string IType;
struct WordNode
{
	WordNode(const IType &value)
		: m_data(value), m_left(nullptr), m_right(nullptr), occurence(1), uniqueOccurence(1)
	{ }
	void incrementOccurence() { occurence++; }
	int getOccurence() const { return occurence; }
	int getUniqueOccurence() const { return uniqueOccurence; }
	void setOccurence(WordNode*& source) {
		occurence = source->occurence;
	}
	void setUniqueOccurence(WordNode*& source) {
		uniqueOccurence = source->uniqueOccurence;
	}
	IType m_data;
	WordNode *m_left;
	WordNode *m_right;
	
private:
	int occurence;
	int uniqueOccurence;
};
class WordTree
{
private:
	WordNode * root;
	// private member functions: 
	bool search(const IType& v, WordNode* ptr);
	void swap(WordTree& source);
	void freeTree(WordNode* cur);
	void copyTreeHelper(WordNode*& source, WordNode*& dest);
	void inOrder(std::ostream& o, WordNode* cur) const;
	void uniqueWordCounter(WordNode* source, int& i) const;
	void totalWordCounter(WordNode* source, int& i) const;
public:
	// default constructor:
	WordTree();
	// copy constructor:
	WordTree(const WordTree& rhs);
	// destructor:
	~WordTree();
	// assignment operator:
	const WordTree& operator=(const WordTree& rhs);
	// Insert v into the word tree
	void add(IType v);
	// return the number of distinct words/nodes
	int distinctWords() const;
	// return the total number of words inserted, including duplicate values:
	int totalWords() const;
	
	// print the linkedlist
	friend std::ostream& operator<<(std::ostream &out, const WordTree& rhs);
};

#endif
