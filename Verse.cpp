// Verse class function definitions
// Computer Science, MVNU

#include "Verse.h"
#include <iostream>
using namespace std;

Verse::Verse() {  	// Default constructor
    verseText = "Uninitialized Verse!";
    verseRef = Ref();
} 

// REQUIRED: Parse constructor - pass verse string from file
Verse::Verse(const string s) {
	// use Ref constructor to create verseRef
	// store the remainder of the string in verseText
    string rtext = s; // make local copy of string to avoid modifying parameter
    int book, chap, verse;

    string strbook = GetNextToken(rtext, ":");
    // Get book number
    book = atoi(strbook.c_str());
    // Get chapter number
    string strchap = GetNextToken(rtext, ":");
    chap = atoi(strchap.c_str());
    // Get verse number
    string strverse = GetNextToken(rtext, " ");
    verse = atoi(strverse.c_str());

    verseRef = Ref(book, chap, verse);
    verseText = rtext;
}  	

// REQUIRED: Accessors
string Verse::getVerse() {
    return verseText;
}

Ref Verse::getRef() {
    return verseRef;
}

// display reference and verse
void Verse::display() {
    //verseRef.display();

    cout << verseRef.getVerse() << " " << verseText;
 }
