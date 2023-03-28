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
	int b, c, v, numVerses = 1;
	LookupResult result;

    if (argc < 4) {
		cout << "Error: Missing Aruments." << endl;
		return 0;
	}
	
	b = atoi(argv[1]);
	c = atoi(argv[2]);
	v = atoi(argv[3]);
    if (argc > 4) {
        numVerses = atoi(argv[4]);
    }

	// Create a reference from the numbers
	Ref ref(b, c, v);
    ref.display();
    cout << " ";

    verse = webBible.lookup(ref, result);
    if (result == SUCCESS) {    
        verse.displayVerseText();
        cout << endl;
        if (numVerses > 1) {
            for (int i = 0; i < (numVerses - 1); i++) {
		    	verse = webBible.nextVerse(result);
		    	// check result
		    	if (result != SUCCESS) {
		    		cout << webBible.error(result) << endl;
		    		break;
		    	}
		    	verse.display();
		    	cout << endl;
		    }
        }
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

    return 0;
}