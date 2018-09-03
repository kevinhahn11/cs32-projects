#include "tree.h"
#include <iostream>
#include <string>
using namespace std;
// constructor
WordTree::WordTree() : root(nullptr) {}
// copy constructor:
WordTree::WordTree(const WordTree& rhs) 
{
	if (rhs.root == nullptr)
		root = nullptr;
	WordNode* ptr = rhs.root;
	copyTreeHelper(ptr, root);
}
// destructor:
WordTree::~WordTree() 
{
	freeTree(root);
}
// assignment operator:
const WordTree& WordTree::operator=(const WordTree& rhs) 
{
	if (this == &rhs)
		return (*this);
	WordTree copy = rhs;
	this->swap(copy);
	return (*this);
}
// Insert v into the word tree
void WordTree::add(IType v) 
{
	if (root == nullptr)
	{
		root = new WordNode(v);
		return;
	}
	WordNode* cur = root;
	for (;;)
	{
		if (v == cur->m_data)
		{
			cur->incrementOccurence();
			return;
		}
		if (v < cur->m_data)
		{
			if (cur->m_left != nullptr)
				cur = cur->m_left;
			else
			{
				cur->m_left = new WordNode(v);
				return;
			}
		}
		else 
		{
			if (cur->m_right != nullptr)
				cur = cur->m_right;
			else
			{
				cur->m_right = new WordNode(v);
				return;
			}
		}
	}
}

// return the number of distinct words/nodes
int WordTree::distinctWords() const 
{
	int i = 0; 
	uniqueWordCounter(root, i);
	return i;
}
// return the total number of words inserted, including duplicate values:
int WordTree::totalWords() const 
{
	int i = 0;
	totalWordCounter(root, i);
	return i;
}
// print the linkedlist
std::ostream& operator<<(std::ostream &out, const WordTree& rhs)
{
	rhs.inOrder(out, rhs.root);
	return out;
}
// private member function
bool WordTree::search(const IType& v, WordNode* ptr)
{
	if (ptr == nullptr)
		return false;
	else if (v == ptr->m_data)
		return true;
	else if (v < ptr->m_data)
		return search(v, ptr->m_left);
	else
		return search(v, ptr->m_right);
}
void WordTree::swap(WordTree& source)
{
	WordNode* temp = source.root;
	source.root = this->root;
	this->root = temp;
	return;
}
void WordTree::freeTree(WordNode* cur)
{
	if (cur == nullptr)
		return;
	freeTree(cur->m_left);
	freeTree(cur->m_right);
	delete cur;
}
void WordTree::copyTreeHelper(WordNode*& source, WordNode*& dest)
{
	if (source == nullptr)
	{
		dest = nullptr;
		return;
	}
	dest = new WordNode(source->m_data);
	dest->setOccurence(source);
	dest->setUniqueOccurence(source);
	copyTreeHelper(source->m_left, dest->m_left);
	copyTreeHelper(source->m_right, dest->m_right);
	return;
}
void WordTree::inOrder(std::ostream& o, WordNode* cur) const
{
	if (cur == nullptr)
		return;
	inOrder(o, cur->m_left);
	o << cur->m_data << " " << cur->getOccurence() << endl;
	inOrder(o, cur->m_right);
}
void WordTree::uniqueWordCounter(WordNode* source, int& i) const
{
	if (source == nullptr)
		return;
	i += source->getUniqueOccurence();
	uniqueWordCounter(source->m_left, i);
	uniqueWordCounter(source->m_right, i);
}
void WordTree::totalWordCounter(WordNode* source, int& i) const
{
	if (source == nullptr)
		return;
	i += source->getOccurence();
	totalWordCounter(source->m_left, i);
	totalWordCounter(source->m_right, i);
}