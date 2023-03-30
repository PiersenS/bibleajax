// Ref class function definitions
// Computer Science, MVNU

#include "Ref.h"
#include <iostream>
#include <string>
using namespace std;

// GetNextToken - general routine for getting next token from a string
// Parameters
//    str - string to search. search is destructive, i.e., token is removed.
//    delimiters - string, a list of characters to use a delimiters between tokens
// Returns: string token (removed from str)

string GetNextToken(string& str, const string& delimiters = " ") {
  // Skip delimiters at beginning                                          
  string::size_type startPos = str.find_first_not_of(delimiters, 0);
  // Find position of delimiter at end of token                                           
  string::size_type endPos = str.find_first_of(delimiters, startPos);

  // Found a token, remove it from string, and return it                       
  string next = str.substr(startPos, endPos - startPos);
  string rest = str.substr(endPos - startPos + 1, string::npos);
  str = rest;
  return(next);
}

// Ref member functions

Ref::Ref() {book = 0; chap = 0; verse = 0;}  	// Default constructor

Ref::Ref(const string s) { // Parse constructor - receives a line "34:5:7 text"
    string rtext = s; // make local copy of string to avoid modifying parameter
    // parse the reference - notice, currently there is no error checking!
    // Get book number
    string strbook = GetNextToken(rtext,":");
    book = atoi(strbook.c_str());
    // Get the chapter number
    string strchap = GetNextToken(rtext,":");
    chap = atoi(strchap.c_str());
    // Get the verse number
    string strverse = GetNextToken(rtext," ");
    verse = atoi(strverse.c_str());
}

Ref::Ref(const int b, const int c, const int v) { 	// Construct Ref from three integers
	book = b;
	chap = c;
	verse = v;
}

// Accessors
int Ref::getBook() const {return book;}	 // Access book number
int Ref::getChap() const {return chap;}	 // Access chapter number
int Ref::getVerse() const {return verse;}; // Access verse number

string Ref::getBookName() {
    string bookNames[67] = { "", "Genesis","Exodus","Leviticus","Numbers","Deuteronomy","Joshua","Judges","Ruth","1 Samuel","2 Samuel","1 Kings","2 Kings",
        "1 Chronicles","2 Chronicles","Ezra","Nehemiah","Esther","Job","Psalms","Proverbs","Ecclesiastes","Song of Solomon","Isaiah","Jeremiah","Lamentations",
        "Ezekiel","Daniel","Hosea","Joel","Amos","Obadiah","Jonah","Micah","Nahum","Habakkuk","Zephaniah","Haggai","Zechariah","Malachi", 
        "Matthew","Mark","Luke","John","Acts","Romans","1 Corinthians","2 Corinthians","Galatians","Ephesians","Philippians","Colossians","1 Thessalonians",
        "2 Thessalonians","1 Timothy","2 Timothy","Titus","Philemon","Hebrews","James","1 Peter","2 Peter","1 John","2 John","3 John","Jude","Revelation" };

    return bookNames[book];
}
// TO DO: implement comparison functions
// REQUIRED: == comparison
bool Ref::operator==(const Ref r) const{
    // compare book, chapter, and verse of Ref;
    bool equal = (book == r.book) && (chap == r.chap) && (verse == r.verse);
    return equal;
}

bool Ref::operator<(const Ref r) const {
    if (book == r.book) {
        if (chap == r.chap) {
            return (verse < r.verse);
        }
        else {
            return (chap < r.chap);
        }
    }
    else {
        return (book < r.book);
    }
}

bool Ref::operator>(const Ref r) const {
    if (book == r.book) {
        if (chap == r.chap) {
            return (verse > r.verse);
        }
        else {
            return (chap > r.chap);
        }
    }
    else {
        return (book > r.book);
    }
}

// OPTIONAL: define < and > comparisons

// TO DO: modify display function to show book name instead of book number
void Ref::display() { 	// Display Reference
    /* 
    *  NOTE: array holds 67 elements. First element is empty inorder for the book number to remain unaltered.
    *  Genesis is book 1, so it is element 1 instead of element 0.
    */
    string bookNames[67] = { "", "Genesis","Exodus","Leviticus","Numbers","Deuteronomy","Joshua","Judges","Ruth","1 Samuel","2 Samuel","1 Kings","2 Kings",
        "1 Chronicles","2 Chronicles","Ezra","Nehemiah","Esther","Job","Psalms","Proverbs","Ecclesiastes","Song of Solomon","Isaiah","Jeremiah","Lamentations",
        "Ezekiel","Daniel","Hosea","Joel","Amos","Obadiah","Jonah","Micah","Nahum","Habakkuk","Zephaniah","Haggai","Zechariah","Malachi", 
        "Matthew","Mark","Luke","John","Acts","Romans","1 Corinthians","2 Corinthians","Galatians","Ephesians","Philippians","Colossians","1 Thessalonians",
        "2 Thessalonians","1 Timothy","2 Timothy","Titus","Philemon","Hebrews","James","1 Peter","2 Peter","1 John","2 John","3 John","Jude","Revelation" };

    string bookname = bookNames[book];
    cout << bookname << " " << chap << ":" << verse;
}

string Ref::displayString() {

    string bookNames[67] = { "", "Genesis","Exodus","Leviticus","Numbers","Deuteronomy","Joshua","Judges","Ruth","1 Samuel","2 Samuel","1 Kings","2 Kings",
        "1 Chronicles","2 Chronicles","Ezra","Nehemiah","Esther","Job","Psalms","Proverbs","Ecclesiastes","Song of Solomon","Isaiah","Jeremiah","Lamentations",
        "Ezekiel","Daniel","Hosea","Joel","Amos","Obadiah","Jonah","Micah","Nahum","Habakkuk","Zephaniah","Haggai","Zechariah","Malachi", 
        "Matthew","Mark","Luke","John","Acts","Romans","1 Corinthians","2 Corinthians","Galatians","Ephesians","Philippians","Colossians","1 Thessalonians",
        "2 Thessalonians","1 Timothy","2 Timothy","Titus","Philemon","Hebrews","James","1 Peter","2 Peter","1 John","2 John","3 John","Jude","Revelation" };

        string bookname = bookNames[book];

        string line = bookname + " ";
        string chapString = chap + "";
        string verseString = verse + "";

        line += chapString + ":" + verseString;

        cout << line << endl;

        return line;
}
