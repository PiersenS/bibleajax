// Bible class function definitions
// Computer Science, MVNU

// temporary useless comment

#include "Ref.h"
#include "Verse.h"
#include "Bible.h" 
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

Bible::Bible() { // Default constructor
	infile = "/home/class/csc3004/Bibles/web-complete";
	//infile = "web-complete";
}

// Constructor – pass bible filename
Bible::Bible(const string s) { 
	infile = s; 
	isOpen = false;
}

// REQUIRED: lookup finds a given verse in this Bible
Verse Bible::lookup(Ref ref, LookupResult& status) { 
	// check if ref can be found
	if (ref.getBook() < 1 || ref.getBook() > 66) {
		status = NO_BOOK;
		return Verse();
	}

	instream.open(infile);
	isOpen = true;
	bool bookFound = false, chapFound = false, verseFound = false; // found book, chapter, verse
	string line;
    // TODO: scan the file to retrieve the line that holds ref ...
    // update the status variable
	status = OTHER; // placeholder until retrieval is attempted
	do {
		getline(instream, line);
		if (line == "")
			break;

		Ref cur(line);	// Ref of current line being read in

		if (cur.getBook() == ref.getBook())
			bookFound = true;
		if (cur.getBook() == ref.getBook() && cur.getChap() == ref.getChap())
			chapFound = true;
		if (cur.getBook() == ref.getBook() && cur.getChap() == ref.getChap() && cur.getVerse() == ref.getVerse())
			verseFound == true;

		if (cur == ref) {	// compare objects
			status = SUCCESS;
		}

	} while (!instream.eof() && status != SUCCESS);
	if (status != SUCCESS) {
		if (bookFound && chapFound)
			status = NO_VERSE;
		else if (bookFound)
			status = NO_CHAPTER;
		else
			status = NO_BOOK;
	}

	// create and return the verse object
	if (line == "")
		return Verse();
	else {
		Verse verse(line);
		return verse;
	}
}

// REQUIRED: Return the next verse from the Bible file stream if the file is open.
// If the file is not open, open the file and return the first verse.
Verse Bible::nextVerse(LookupResult& status) {
	string nextLine;
	status = SUCCESS;
	if (isOpen) {
		getline(instream, nextLine);
		if (nextLine == "") {
			status = OTHER; // end of Bible
			return Verse();
		}
	}
	else {
		// return first line of Bible
		instream.open(infile);
		getline(instream, nextLine);
	}
	Verse nextVerse(nextLine);
	return nextVerse;
}

// REQUIRED: Return an error message string to describe status
string Bible::error(LookupResult status) {
	string error;
	switch (status) {
	case NO_BOOK:
		error = "Error: No Book Found";
		break;
	case NO_CHAPTER:
		error = "Error: No Chapter Found";
		break;
	case NO_VERSE:
		error = "Error: No Verse Found";
		break;
	default:
		error = "Uknown Error";
	}
	return error;
}

void Bible::display() {
	cout << "Bible file: " << infile << endl;
}
	
// OPTIONAL access functions
// OPTIONAL: Return the reference after the given ref
/*
Ref Bible::next(const Ref ref, LookupResult& status) {
}

// OPTIONAL: Return the reference before the given ref
Ref Bible::prev(const Ref ref, LookupResult& status) {
}
*/
