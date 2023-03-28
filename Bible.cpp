// Bible class function definitions
// Computer Science, MVNU

#include "Ref.h"
#include "Verse.h"
#include "Bible.h" 
#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

Bible::Bible() { // Default constructor
	infile = "/home/class/csc3004/Bibles/web-complete";
	//infile = "C:\\Users\\piers\\School\\SoftwareDevelopment\\BibleVersions\\web-complete";  // personal copy of Bible
	instream.open(infile);	// add check if file opened
	if (instream.is_open()) {
		isOpen = true;
	}
	else {
		isOpen = false;
	}
	buildIndex();
}

// Constructor – pass bible filename
Bible::Bible(const string s) { 
	infile = s; 
	instream.open(infile);
	if (instream.is_open()) {
		isOpen = true;
	}
	else {
		isOpen = false;
	}
	buildIndex();
}

// stores location of Ref objects in a map
void Bible::buildIndex() {
	// Strategy: Call nextVerse() until end of file. Parse verse from each call into Ref object, put Ref into map with file position from infile.tellg()
	// Repeat.

	// consider using LookupResult enum to tell if end of file has been reached. 
	if (!isOpen) {
		cout << "Could not find file." << endl;
	}

	string nextLine;
	LookupResult result = OTHER;
	Verse current;
	streampos position;

	/*
	while (!instream.eof()) {
		position = instream.tellg();
		current = nextVerse(result);
		refIndex[current.getRef()] = position;
	}
	*/

	while (!instream.eof()) {
		position = instream.tellg();
		if (getline(instream, nextLine)) {
			//parse to Verse and store in index
			Verse currentVerse(nextLine);
			refIndex[currentVerse.getRef()] = position;
		}
	}
}

//Ref Bible::searchIndex(Ref ref, LookupResult& status) {}

// REQUIRED: lookup finds a given verse in this Bible
Verse Bible::lookup(Ref ref, LookupResult& status) { 
	// check if ref can be found
	if (ref.getBook() < 1 || ref.getBook() > 66) {
		status = NO_BOOK;
		return Verse();
	}

	/* Strategy: 
		check if ref exists in map, extract streampos
		use seekg(streampos) to find verse text in Bible
		parse text to verse, return verse
	*/
	streampos startpos = 0;

	if (refIndex.find(ref) != refIndex.end()) {
		// ref is found
		startpos = refIndex[ref];
		instream.clear();
		instream.seekg(startpos); // set position to start reading file

		string verseText;
		getline(instream, verseText);
		
		Verse verse(verseText); 

		status = SUCCESS;
		return verse;
	}
	else if (refIndex.find(Ref(ref.getBook(), ref.getChap(), 1)) != refIndex.end()) {
		status = NO_VERSE;
		return Verse();
	}
	else if (refIndex.find(Ref(ref.getBook(), 1, 1)) != refIndex.end()) {
		status = NO_CHAPTER;
		return Verse();
	}
	else {
		status = NO_BOOK;
		return Verse();
	}
}

// REQUIRED: Return the next verse from the Bible file stream if the file is open.
// If the file is not open, open the file and return the first verse.
Verse Bible::nextVerse(LookupResult& status) {
	string nextLine;
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
	status = SUCCESS;
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
	}
	
	return error;
}

void Bible::display() {
	cout << "Bible file: " << infile << endl;
}
	
// OPTIONAL access functions
// OPTIONAL: Return the reference after the given ref

Ref Bible::next(const Ref ref, LookupResult& status) {
	map<Ref, int>::iterator iter = refIndex.find(ref);
	iter++;
	status = SUCCESS;
	return iter->first;
}

/*
// OPTIONAL: Return the reference before the given ref
Ref Bible::prev(const Ref ref, LookupResult& status) {
}
*/
