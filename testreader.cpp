/* Test Application for Project3 */

#include <iostream>
#include <fstream>
#include <map>

#include "Bible.h"
#include "Ref.h"
#include "Verse.h"

using namespace std;

/****************************************/
/*  Game Plan:                          */
/*      use nextVerse() to get verse,   */
/*      parse verrse to Ref object ,    */
/*      store Ref in map   :)           */
/****************************************/

int main(int argc, char **argv) {
    string infile = "/home/class/csc3004/Bibles/web-complete";
    //string infile = "C:\\Users\\piers\\School\\SoftwareDevelopment\\BibleVersions\\web-complete";  // personal copy of Bible

    Bible webBible(infile); 

    map<Ref, int> refs = webBible.getRefIndex();
    //cout << "Index contains " << refs.size() << " references." << endl;


    map<Ref, int>::iterator iter = refs.begin();

    Verse verse;
	int b, c, v;
	if (argc > 4) {
        cout << "Too Many Arguments!" << endl;
        return 0;
    }
	LookupResult result;

    if (argc < 4) {
		cout << "Error: Missing Aruments." << endl;
		return 0;
	}
	
	b = atoi(argv[1]);
	c = atoi(argv[2]);
	v = atoi(argv[3]);

	// Create a reference from the numbers
	Ref ref(b, c, v);
    ref.display();
    cout << " ";

    verse = webBible.lookup(ref, result);
    if (result == SUCCESS) {    
        verse.display();
        cout << endl;
    }
    else if (result == NO_VERSE) {
        cout << "Verse Not Found." << endl;
    }
    else if (result == NO_CHAPTER) {
        cout << "Chapter Not Found." << endl;
    }
    else {
        cout << "Book Not Found." << endl;
    }




    /*
    for (int i = 0; i < 4; i++) {
        Ref r = iter->first;
        cout << r.getBook() << " " << r.getChap() << " " << r.getVerse();
        cout << " at position: " << iter->second << endl;
        iter++;
    }

    //Print Genesis Refs
    /*
    while (iter->first.getBook() < 2) {
        Ref r = iter->first;
        cout << r.getBook() << " " << r.getChap() << " " << r.getVerse();
        cout << " at position: " << iter->second << endl;
        iter++;
    }
    */
    


    // Print entire map 
    /*
    while (iter != refs.end()) {
        Ref r = iter->second;
        cout << r.getBook() << " " << r.getChap() << " " << r.getVerse() << endl;
        iter++;
    }
    */

    return 0;
}