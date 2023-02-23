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

int main() {
    string infile = "/home/class/csc3004/Bibles/web-complete";
    //string infile = "C:\\Users\\piers\\School\\SoftwareDevelopment\\BibleVersions\\web-complete";  // personal copy of Bible

    Bible webBible(infile); 

    map<Ref, int> refs = webBible.getReferences();
    cout << "Index contains " << refs.size() << " references." << endl;


    map<Ref, int>::iterator iter = refs.begin();

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