/* Demo server program for Bible lookup using AJAX/CGI interface
 * By James Skon, Febrary 10, 2011
 * updated by Bob Kasper, January 2020
 * Mount Vernon Nazarene University
 * 
 * This sample program works using the cgicc AJAX library to
 * allow live communication between a web page and a program running on the
 * same server that hosts the web server.
 *
 * This program is run by a request from the associated html web document.
 * A Javascript client function invokes an AJAX request,
 * passing the input form data as the standard input string.
 *
 * The cgi.getElement function parses the input string, searching for the matching 
 * field name, and returing a "form_iterator" oject, which contains the actual
 * string the user entered into the corresponding field. The actual values can be
 * accessed by dereferencing the form iterator twice, e.g. **verse
 *     refers to the actual string entered in the form's "verse" field.
 */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Ref.h"
#include "Verse.h"
#include "Bible.h"
using namespace std;

/* Required libraries for AJAX to function */
#include "/home/class/csc3004/cgicc/Cgicc.h"
#include "/home/class/csc3004/cgicc/HTTPHTMLHeader.h"
#include "/home/class/csc3004/cgicc/HTMLClasses.h"
using namespace cgicc;

int main() {
  /* A CGI program must send a response header with content type
   * back to the web client before any other output.
   * For an AJAX request, our response is not a complete HTML document,
   * so the response type is just plain text to insert into the web page.
   */
  cout << "Content-Type: text/plain\n\n";
  
  Cgicc cgi;  // create object used to access CGI request data

  Bible webBible("/home/class/csc3004/Bibles/web-complete");
  Verse newVerse;
  LookupResult result;

  int bookNum, chapNum, verseNum, numVerses;
  bool bookFound = false, chapFound = false, verseFound = false;

  // GET THE INPUT DATA
  // browser sends us a string of field name/value pairs from HTML form
  // retrieve the value for each appropriate field name
  form_iterator st = cgi.getElement("search_type");
  form_iterator book = cgi.getElement("book");
  form_iterator chapter = cgi.getElement("chapter");
  form_iterator verse = cgi.getElement("verse");
  form_iterator nv = cgi.getElement("num_verse");

  // Convert and check input data
  
  /* TO DO: OTHER INPUT VALUE CHECKS ARE NEEDED ... but that's up to you! */

  /* Check if book is valid */
  if (book != cgi.getElements().end()) {
    bookNum = book->getIntegerValue();
    if (bookNum > 66) {
      cout << "<p>The book number (" << bookNum << ") is too high.</p>" << endl;
    }
    else if (bookNum <= 0) {
      cout << "<p>The book must be a positive number.</p>" << endl;
    }
    else {
      bookFound = true;
    }
  }
  /* Check if chapter is valid */
  if (chapter != cgi.getElements().end()) {
	 chapNum = chapter->getIntegerValue();
	 if (chapNum > 150) {
		 cout << "<p>The chapter number (" << chapNum << ") is too high.</p>" << endl;
	 }
	 else if (chapNum <= 0) {
		 cout << "<p>The chapter must be a positive number.</p>" << endl;
	 }
	 else
		 chapFound = true;
  }
  /* Check if verse is valid */
  if (verse != cgi.getElements().end()) {
    verseNum = verse->getIntegerValue();
    verseFound = true;
  }/* Maybe add checks based on verses in a chapter */

  numVerses = nv->getIntegerValue();
  if (numVerses < 1) {
    numVerses = 1;
  }

  /* TO DO: PUT CODE HERE TO CALL YOUR BIBLE CLASS FUNCTIONS
   *        TO LOOK UP THE REQUESTED VERSES
   */

  /* if (bookFound and chapFound and verseFound), then print */
  if (bookFound && chapFound && verseFound) {
    Ref ref(bookNum, chapNum, verseNum);
    /* Headings to describe the verse(s) searched */
    cout << "<h2>";
    ref.display();
    cout << "</h2>" << endl;

    cout << "<h3>" << numVerses << " Verse(s)" << "</h3>" << endl;


	  newVerse = webBible.lookup(ref, result);
	  if (result == SUCCESS) {
		  newVerse.display();
		  cout << endl;
		  for (int i = 0; i < (numVerses - 1); i++) {
		  	newVerse = webBible.nextVerse(result);
		  	// check result
		  	if (result != SUCCESS) {
		  		cout << webBible.error(result) << endl;
		  		break;
		  	}
		  	newVerse.display();
		  	cout << endl;
		  }
	  }
	  else {
	  	cout << webBible.error(result) << endl;
	  }
  }


  /* SEND BACK THE RESULTS
   * Finally we send the result back to the client on the standard output stream
   * in HTML text format.
   * This string will be inserted as is inside a container on the web page, 
   * so we must include HTML formatting commands to make things look presentable!
   */

  return 0;
}
