#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <cassert>
using namespace std;
// Global constants:
const int MAXRESULTS = 20;    // Max matches that can be found (20)
const int MAXDICTWORDS = 30000; // Max words that can be read in
// Required:
int dictionaryReader(istream &dictfile, string dict[]);
int recurCombos(string word, const string dict[], int size, string results[]);
void recursiveDisp(const string results[], int size);
// Helper:
int binarySearch(const string A[], int top, int bot, string f);
void helperDictReader(int& k, istream &dictfile, string dict[]);

void permutationalLoop(int i, int max, string prefix, string rest, const string dict[], const int& size, string results[], int& count);
void generatePermutations(const string dict[], const int& size, string results[], string prefix, string rest, int& count);
int checkTheDictionary(const string& target, const string dict[], int size, string results[], int& count);
bool wordIsADup(const string& target, const string results[], int start, int max);

int main()
{
	string results[MAXRESULTS];
	string dict[MAXDICTWORDS];
	ifstream dictfile;         // file containing the list of words
	int nwords;                // number of words read from dictionary
	string word;

	dictfile.open("words.txt");
	if (!dictfile) {
		cout << "File not found!" << endl;
		return (1);
	}

	nwords = dictionaryReader(dictfile, dict);
	cout << "Please enter a string for an anagram: ";
	cin >> word;

	int numMatches = recurCombos(word, dict, nwords, results);
	
	if (!numMatches)
		cout << "No matches found" << endl;
	else
	{
		cout << "There are " << numMatches << " different permutations: " << endl;
		recursiveDisp(results, numMatches);
	}
	
}

///// recursiveDisp:
void recursiveDisp(const string results[], int size)
{
	if (size != 0)
	{
		// this is just like recursively printing the results of any ordinary array
		cout << "Matching word " << results[0] << endl;
		recursiveDisp(results + 1, size - 1);
	}

	return; // in this case, size is 0 so we can just return.

}
///// required function 3
int recurCombos(string word, const string dict[], int size, string results[])
{
	int count = 0;
	generatePermutations(dict, size, results, "", word, count);
	return count;
}
/// dictionaryReader:
int dictionaryReader(istream &dictfile, string dict[])
{
	int count = 0;
	helperDictReader(count, dictfile, dict);
	if (count > MAXDICTWORDS)
		return MAXDICTWORDS;
	else
		return count;
}
// dictionaryReader helper function:
void helperDictReader(int& k, istream &dictfile, string dict[])
{
	string word;
	if (dictfile >> word) 
	{
		// once our number of words goes past MAXDICTWORDS, we have to stop reading the file.
		if ((k + 1) <= MAXDICTWORDS)
		{
			k += 1;
			*dict = word;
			helperDictReader(k, dictfile, dict + 1);
		}
		else
			return;
		/*
		if ((k + 1) > MAXDICTWORDS) 
		{
			// keep k as it is
			return;
		}
		k += 1;
		*dict = word;
		helperDictReader(k, dictfile, dict + 1);
		*/
		
	}
}
// helper functions for recurCombos below:
void generatePermutations(const string dict[], const int& size, string results[], string prefix, string rest, int& count)
{
	if (rest.size() != 0)
	{
		int paramSize = rest.size();
		permutationalLoop(0, paramSize, prefix, rest, dict, size, results, count);
	}
	else
	{
		/*
		when rest's size becomes 0, call checkDict() to see if its in the file when we find a permutation
		checkDict() will return 1 if this word is found in the dictionary...
		otherwise it will return 0 if the word isn't found.
		*/
		count += checkTheDictionary(prefix, dict, size, results, count);
		// if the number of words found in the dictionary is greater than MAXRESULTS, stop adding words into results[].
		if (MAXRESULTS < count) // same as (!(count <= MAXRESULTS))
		{
			// reset the value to previous one.
			count -= 1;
			return;
		}
	}
}

/*
findPermutations and permutationalLoop -> we can obtain all of a word's possible permutations.
we have pass the variable count by reference so that wherever we go, the count will 
still be incremented regardless.

Making size to be const and passed by reference will help me save us space and there's no need for us to
modify size.
*/
// our de facto for loop :
void permutationalLoop(int i, int max, string prefix, string rest, const string dict[], const int& size, string results[], int& count)
{
	if (i < max)
	{
		string newPrefix = prefix + rest[i];
		string newRest = rest.substr(0, i) + rest.substr(i + 1);
		generatePermutations(dict, size, results, newPrefix, newRest, count);
		permutationalLoop(i + 1, max, prefix, rest, dict, size, results, count);
	}
	else
	{
		return;
	}
}

/*
This function checks if there's one word in results[] that's == to target.
since there's no reason to change the value of target and results[], pass them as const.
*/
bool wordIsADup(const string& target, const string results[], int start, int max)
{
	// binary search to find the word
	if (binarySearch(results, start, max, target) == -1)
		return false;
	else
		return true;
}
// Recursive search function:
int binarySearch(const string A[], int top, int bot, string f)
{
	if (top > bot)
		return -1;
	else
	{
		int mid = (top + bot) / 2;
		if (f == A[mid])
			return mid;
		else if (f < A[mid])
			return binarySearch(A, top, mid - 1, f);
		else
			return binarySearch(A, mid + 1, bot, f);
	}
}

/* 
 Since we do not change the value of target, mark target as passed by constant reference.
 It checks whether the target word is in the dictionary.
*/
int checkTheDictionary(const string& target, const string dict[], int size, string results[], int& count)
{
	// if we run through the whole dictionary, and there is no match, return 0.
	if (!(size != 0))
	{
		return 0;
	}

	// if we find a match in the dictionary, call isDuplicated() to check
	// whether there is already a duplicated one in the result[].
	else if ((target != *dict) == false)
	{
		// if we encounter a duplicate word, then we need
		// to exit
		if (count < MAXRESULTS && wordIsADup(target, results, 0, count) == false)
		{
			results[count] = target;
			return 1;
		}
		// if there isn't one, add target into result[] and return 1.
		else
		{
			return 0;
		}
	}
	// keep searching through the dictionary
	else
	{
		return checkTheDictionary(target, dict + 1, size - 1, results, count);
	}
}


