#include "CoachingStaff.h"
#include <cassert>
#include <string>
using namespace std;

int main()
{
	/*
	CoachingStaff dbacks;
	CoachingStaff rockies;
	dbacks = rockies;
	
	assert(dbacks.numberOfCoaches() == 0 && dbacks.noCoaches());
	dbacks.hireCoach("Chip", "Hale", "50");
	//dbacks.dump();
	rockies.hireCoach("Walt", "Weiss", "68");
	rockies.hireCoach("Bucky", "Barnes", "77");
	CoachingStaff* p = new CoachingStaff();
	CoachingStaff* pp = new CoachingStaff();
	delete p; delete pp;
	CoachingStaff r(rockies);
	r.hireCoach("Dusty", "Baker", "80");
	r.dump();
	cerr << r.numberOfCoaches();
	

/*
	// default constructor
	CoachingStaff dodgers;
	// For an empty list:
	assert(dodgers.numberOfCoaches() == 0); // an empty list
	assert(dodgers.noCoaches() == true); // empty list
	assert(!dodgers.fireCoach("Bob", "Geren")); // nothing to erase
	CoachingStaff padres;
	// swap two empty lists
	padres.changeStaff(dodgers);
	assert(padres.noCoaches() && dodgers.noCoaches() && padres.numberOfCoaches() == 0 && dodgers.numberOfCoaches() == 0);
	assert(dodgers.renameCoach("Bob", "Geren", "8") == false);
	// testing mergeStaff and searchStaff on two empty lists:
	CoachingStaff NL;
	assert(mergeStaffs(padres, dodgers, NL) == true && NL.numberOfCoaches() == 0 && NL.noCoaches() == true);
	searchStaff("*", "*", dodgers, NL);
	searchStaff("Let's Go", "*", dodgers, NL);
	searchStaff("*", "ITFDB", dodgers, NL);
	assert(NL.noCoaches() == true && NL.numberOfCoaches() == 0);

	// For a list with one node:
	assert(dodgers.hireCoach("Dave", "Roberts", "45") == true);
	assert(dodgers.numberOfCoaches() == 1);
	assert(dodgers.noCoaches() == false);
	IType v;
	string firstName; string lastName;
	assert(dodgers.findCoach("Dave", "Roberts", v) && v == "45");
	assert(dodgers.coachOnStaff("Dave", "Roberts") == true);
	assert(dodgers.whichCoach(0, firstName, lastName, v) && firstName == "Dave" && lastName == "Roberts" && v == "45");

	// swap a list with one node and a list that's empty
	CoachingStaff giants;
	dodgers.changeStaff(giants);
	// dodgers is now empty
	assert(dodgers.noCoaches() == true && dodgers.numberOfCoaches() == 0);
	assert(giants.noCoaches() == false && giants.numberOfCoaches() == 1);
	string fName; string lName; IType val;
	assert(giants.coachOnStaff("Dave", "Roberts") && giants.findCoach("Dave", "Roberts", val) && val == "45");
	assert(giants.whichCoach(0, fName, lName, val) && fName == "Dave" && lName == "Roberts" && val == "45");
	giants.hireOrRename("Bruce", "Bochy", "65"); // hires this coach
	assert(giants.hireCoach("Bruce", "Bochy", "75") == false);
	giants.hireOrRename("Bruce", "Bochy", "50"); // changes the value of Bruce Bochy to 50
	assert(giants.whichCoach(0, fName, lName, val) && fName == "Bruce" && lName == "Bochy" && val == "50");
	assert(giants.findCoach("Bruce", "Bochy", val) && val == "50");
	assert(giants.coachOnStaff("Bruce", "Bochy") && giants.coachOnStaff("Dave", "Roberts"));
	IType age = "66";
	giants.renameCoach("Bruce", "Bochy", age);
	assert(giants.whichCoach(0, fName, lName, val) && val == "66");
	assert(giants.noCoaches() == false && giants.numberOfCoaches() == 2);
	assert(dodgers.fireCoach("Dave", "Roberts") == false && giants.fireCoach("Dave", "Roberts") == true);
	assert(giants.fireCoach("Bruce", "Bochy"));
	giants.dump();
	// dodgers and giants have been emptied

	// For a typical list:
	CoachingStaff lad;
	lad.hireCoach("Manny", "Machado", "26");
	lad.hireCoach("Cody", "Bellinger", "23");
	lad.hireCoach("Corey", "Seager", "24");
	lad.hireCoach("Kyle", "Seager", "30");
	assert(lad.numberOfCoaches() == 4 && lad.noCoaches() == false);
	assert(lad.whichCoach(3, fName, lName, val) && fName == "Kyle" && lName == "Seager" && val == "30");
	lad.hireOrRename("Kyle", "Seager", "Corey's brother");
	assert(lad.findCoach("Kyle", "Seager", val) && val == "Corey's brother");
	assert(lad.hireCoach("Corey", "Seager", "25") == false);
	CoachingStaff sfg;
	sfg.changeStaff(lad);
	assert(lad.noCoaches() == true && lad.numberOfCoaches() == 0);
	assert(sfg.noCoaches() == false && sfg.numberOfCoaches() == 4);
	//sfg.dump();
	lad.changeStaff(sfg);
	assert(sfg.noCoaches() == true && sfg.numberOfCoaches() == 0);
	assert(lad.noCoaches() == false && lad.numberOfCoaches() == 4);
	//lad.dump();
	lad.hireOrRename("Cody", "Bellinger", "Bellibomb");
	assert(lad.findCoach("Cody", "Bellinger", val) && val == "Bellibomb");
	lad.renameCoach("Manny", "Machado", "Mannywood");
	assert(lad.findCoach("Manny", "Machado", val) && val == "Mannywood");
	lad.renameCoach("Corey", "Seager", "The Kid");

	// Testing mergeStaff and searchStaff with one non-empty list and one empty list:
	CoachingStaff combo;
	CoachingStaff cali;
	mergeStaffs(lad, sfg, cali);
	cali.dump();
	cerr << endl;
	assert(cali.numberOfCoaches() == 4 && cali.noCoaches() == false);
	searchStaff("*", "*", lad, combo);
	combo.dump();
	cerr << endl;

	// after running searchStaff, combo should contain Kyle Seager and Corey Seager
	searchStaff("*", "Seager", lad, combo);
	combo.dump();
	cerr << endl;

	// after searchStaff below, combo should contain Corey Dickerson and Corey Seager
	lad.hireCoach("Corey", "Dickerson", "Pittsburgh");
	searchStaff("Corey", "*", lad, combo);
	combo.dump();
	cerr << endl;
	// after running searchStaff below, combo should still be an empty list
	CoachingStaff vets; // empty list
	searchStaff("*", "*", vets, combo);
	assert(combo.noCoaches() == true && combo.numberOfCoaches() == 0);
	searchStaff("*", "Kershaw", vets, combo);
	assert(combo.noCoaches() == true && combo.numberOfCoaches() == 0);
	searchStaff("Clayton", "", vets, combo);
	assert(combo.noCoaches() == true && combo.numberOfCoaches() == 0);
	
	// now testing mergeStaffs with two non-empty lists
	sfg.hireCoach("Cody", "Bellinger", "Bellibomb");
	sfg.hireCoach("Buster", "Posey", "The Third");
	sfg.hireCoach("Madison", "Bumgarner", "MadBum");
	sfg.hireCoach("Brandon", "Crawford", "UCLA Alum");
	assert(mergeStaffs(lad, sfg, cali) == true);
	cali.dump();
	cerr << endl;

	// testing mergeStaffs where it should return false:
	sfg.renameCoach("Cody", "Bellinger", "ROTY"); // there is a Cody Bellinger in the lad with a different value
	assert(mergeStaffs(lad, sfg, cali) == false);
	cali.dump();
	cerr << endl;

	// testing mergeStaffs on lists containing just one item each, with same full name and same value
	// and testing searchStaff on a list with just one item
	CoachingStaff sdp;
	CoachingStaff ari;
	CoachingStaff blend;
	sdp.hireCoach("Andy", "Green", "40");
	ari.hireCoach("Andy", "Green", "40");
	searchStaff("*", "*", sdp, blend);
	assert(blend.noCoaches() == false && blend.numberOfCoaches() == 1);
	blend.dump();

	searchStaff("*", "Green", sdp, blend);
	assert(blend.noCoaches() == false && blend.numberOfCoaches() == 1);
	searchStaff("Andy", "*", sdp, blend);
	assert(blend.noCoaches() == false && blend.numberOfCoaches() == 1);
	searchStaff("Bud", "Black", sdp, blend);
	assert(blend.noCoaches() == true && blend.numberOfCoaches() == 0);
	searchStaff("Lavar", "*", sdp, blend);
	assert(blend.noCoaches() == true && blend.numberOfCoaches() == 0);
	searchStaff("*", "Ball", sdp, blend);
	assert(blend.noCoaches() == true && blend.numberOfCoaches() == 0);
	
	mergeStaffs(sdp, ari, blend);
	assert(blend.noCoaches() == false && blend.numberOfCoaches() == 1);

	// now testing merge staffs with lists containing just one item each, with same full name but different value
	// resulting list should be empty
	sdp.renameCoach("Andy", "Green", "30");
	mergeStaffs(sdp, ari, blend);
	assert(blend.noCoaches() == true && blend.numberOfCoaches() == 0);

	// testing mergeStaff and searchStaff on one empty list and a list with one item
	CoachingStaff hou;
	CoachingStaff oak;
	CoachingStaff AL;
	hou.hireCoach("AJ", "Hinch", "52");
	assert(mergeStaffs(hou, oak, AL) && AL.noCoaches() == false && AL.numberOfCoaches() == 1);
	searchStaff("*", "Hinch", hou, AL);
	assert(AL.coachOnStaff("AJ", "Hinch") && AL.numberOfCoaches() == 1);

	
}

/*
int main()
{
	CoachingStaff ucla;
	assert(ucla.numberOfCoaches() == 0);
	assert(ucla.noCoaches() == true);
	assert(ucla.fireCoach("Chip", "Kelly") == false);
	CoachingStaff m;
	m.hireCoach("Chip", "Kelly", "54");
	m.hireCoach("Dana", "Bible", "64");
	m.hireCoach("Jimmie", "Dougherty", "39");
	m.hireCoach("DeShaun", "Foster",  "38");
	m.hireCoach("Derek", "Sage", "40");
	m.hireCoach("Justin", "Frye", "34");
	m.hireCoach("Dave", "Kelly","55");
	m.dump();
	cerr << endl;
	m.fireCoach("Chip", "Kelly");
	m.dump();
	cerr << endl;
	CoachingStaff bball;
	bball.hireCoach("Steve", "Alford", "40");
	bball = m;
	bball.hireCoach("Justin", "Frye", "32");
	bball.dump();
	cerr << endl;
	
	for (int n = 0; n < bball.numberOfCoaches(); n++)
	{
	string first;
	string last;
	IType val;
	bball.whichCoach(n, first, last, val);
	cerr << first << " " << last << " " << val << endl;
	}
	cerr << "---------------------------------------" << endl;
	cerr << "Now testing the searchStaff function: " << endl;
	CoachingStaff csResult;
	CoachingStaff csOne;
	csOne.hireCoach("Steve", "Alford", "53");
	csOne.hireCoach("Tyus", "Edney", "45");
	csOne.hireCoach("Kory", "Alford", "26");
	searchStaff("*", "Alford", csOne, csResult);
	csResult.dump();
	cerr << endl;
	CoachingStaff wbb;
	wbb.hireCoach("Cori", "Close", "46");
	wbb.hireCoach("Shannon", "Perry", "42");
	wbb.hireCoach("Cori", "Doe", "27");
	
	searchStaff("Cori", "*", wbb, csResult);
	csResult.dump();
	cerr << endl;
	cerr << "Now testing the mergeStaffs function: " << endl;
	CoachingStaff uno;
	uno.hireCoach("Bill", "Yoast", "456");
	uno.hireCoach("Herb", "Tyrell", "123");
	uno.hireCoach("Herman", "Boone", "789");
	CoachingStaff dos;
	dos.hireCoach("Herman", "Boone", "789");
	dos.hireCoach("Doc", "Hines", "321");
	CoachingStaff merged;
	merged.hireCoach("Dave", "Roberts", "45");
	if (mergeStaffs(uno, dos, merged) == true)
		cerr << "True" << endl;
	else
		cerr << "False" << endl;
	merged.dump();
	cerr << endl;
	
	CoachingStaff tres;
	tres.hireCoach("Bill", "Yoast", "456");
	tres.hireCoach("Herb", "Tyrell", "123");
	tres.hireCoach("Herman", "Boone", "789");
	CoachingStaff cuatro;
	cuatro.hireCoach("Herman", "Boone", "654");
	cuatro.hireCoach("Doc", "Hines", "321");
	CoachingStaff merged2;
	if (mergeStaffs(tres, cuatro, merged2) == true)
		cerr << "True" << endl;
	else
		cerr << "False" << endl;
	merged2.dump();
	cerr << endl;
	CoachingStaff cinco;
	cinco.hireCoach("Dave", "Roberts", "45");

	cerr << "Staff cinco below:" << endl;
	cinco.dump();
	CoachingStaff seis;
	cinco.changeStaff(seis);
	cinco.dump();
	cerr << "Staff seis below:" << endl;
	seis.dump();
	
	CoachingStaff fortyTimes;
	fortyTimes.hireCoach("Jerry", "Azzinaro", "6.99");
	assert(!fortyTimes.coachOnStaff("", ""));
	fortyTimes.hireCoach("Vince", "Oghobaase", "5.19");
	fortyTimes.hireCoach("", "", "4.00");
	fortyTimes.hireCoach("Roy", "Manning", "4.7");
	assert(fortyTimes.coachOnStaff("", ""));
	fortyTimes.fireCoach("Vince", "Oghobaase");
	assert(fortyTimes.numberOfCoaches() == 3
		&& fortyTimes.coachOnStaff("Jerry", "Azzinaro")
		&& fortyTimes.coachOnStaff("Roy", "Manning")
		&& fortyTimes.coachOnStaff("", ""));

	cerr << "All tests passed" << endl;
	
}
*/
/*
#include <type_traits>
#define CHECKTYPE(f, t) { auto p = (t)(f); (void)p; }
static_assert(std::is_default_constructible<CoachingStaff>::value, "Map must be default-constructible.");
static_assert(std::is_copy_constructible<CoachingStaff>::value, "Map must be copy-constructible.");
void ThisFunctionWillNeverBeCalled()
{
	CHECKTYPE(&CoachingStaff::operator=, CoachingStaff&
		(CoachingStaff::*)(const CoachingStaff&));
	CHECKTYPE(&CoachingStaff::noCoaches, bool
	(CoachingStaff::*)() const);
	CHECKTYPE(&CoachingStaff::numberOfCoaches, int
	(CoachingStaff::*)() const);
	CHECKTYPE(&CoachingStaff::hireCoach, bool (CoachingStaff::*)
		(const std::string&, const std::string&, const IType&));
	CHECKTYPE(&CoachingStaff::renameCoach, bool
	(CoachingStaff::*)(const std::string&, const std::string&,
		const IType&));
	CHECKTYPE(&CoachingStaff::hireOrRename, bool
	(CoachingStaff::*)(const std::string&, const std::string&,
		const IType&));
	CHECKTYPE(&CoachingStaff::fireCoach, bool (CoachingStaff::*)
		(const std::string&, const std::string&));
	CHECKTYPE(&CoachingStaff::coachOnStaff, bool
	(CoachingStaff::*)(const std::string&, const std::string&)
		const);
	CHECKTYPE(&CoachingStaff::findCoach, bool (CoachingStaff::*)
		(const std::string&, const std::string&, IType&) const);
	CHECKTYPE(&CoachingStaff::whichCoach, bool (CoachingStaff::*)
		(int, const std::string&, const std::string&, IType&)
		const);
	CHECKTYPE(&CoachingStaff::changeStaff, void
	(CoachingStaff::*)(CoachingStaff&));
	CHECKTYPE(mergeStaffs, bool(*)(const CoachingStaff&, const
		CoachingStaff&, CoachingStaff&));
	CHECKTYPE(searchStaff, void(*)(const std::string&,
		const std::string&, const CoachingStaff&, CoachingStaff&));
}
int main() {}
*/
/////////////////////////////////////////////////////
/*
#include "CoachingStaff.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;
void test()
{
	CoachingStaff wgym;

	assert(wgym.hireCoach("Valerie", "Kondos",
		"vkondos@athletics.ucla.edu"));
	assert(wgym.hireCoach("Chris", "Waller",
		"cwaller@athletics.ucla.edu"));
	assert(wgym.numberOfCoaches() == 2);
	string first, last, e;
	assert(wgym.whichCoach(0, first, last, e)
		&& e == "vkondos@athletics.ucla.edu");
	assert(wgym.whichCoach(1, first, last, e) &&
		(first == "Chris" && e == "cwaller@athletics.ucla.edu"));
	return;
}
int main()
{
	test();
	cout << "Passed all tests" << endl;
	return 0;
}
*/
/////////////////////////////////////////////
/*
#include "CoachingStaff.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;
void test()
{
	CoachingStaff mwp;
	assert(mwp.hireCoach("Adam", "Wright", 41));
	assert(mwp.hireCoach("Jason", "Falitz", 37));
	assert(mwp.numberOfCoaches() == 2);
	string first, last;
	int a;
	assert(mwp.whichCoach(0, first, last, a) && a == 37);
	assert(mwp.whichCoach(1, first, last, a) && (first == "Adam" && a == 41));
	return;
}
int main()
{
	test();
	cout << "Passed all tests" << endl;
	return 0;
}
*/