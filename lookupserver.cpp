#include "Bible.h"
#include "fifo.h"

#include <iostream>

using namespace std;

string receive_pipe = "SSrequest";
string send_pipe = "SSreply";

int main() {
    Fifo requestPipe(receive_pipe);
    Fifo replyPipe(send_pipe);

    string infile = "/home/class/csc3004/Bibles/web-complete";
    //string infile = "C:\\Users\\piers\\School\\SoftwareDevelopment\\BibleVersions\\web-complete";

    Bible webBible(infile); 

    map<Ref, int> refs = webBible.getRefIndex();
    map<Ref, int>::iterator iter = refs.begin();
    
    
    string clientRequest;
    string message;

    requestPipe.openread();
    replyPipe.openwrite();

    while(true) {
        //read from request pipe
        clientRequest = requestPipe.recv();

        // convert clientRequest into book, chap, and verse numbers
        int refNums[4]{};
        string substring;
        string delim = "&";
	    int i = 0;
        size_t pos = clientRequest.find(delim);
		while (pos != string::npos) {
			substring = clientRequest.substr(0, pos);
			refNums[i] = stoi(substring);

			clientRequest.erase(0, pos + 1);
			i++;
			pos = clientRequest.find(delim);
		}
        
        Verse verse;
        int b = refNums[0];
        int c = refNums[1];
        int v = refNums[2];
	    int numVerses = refNums[3];
	    LookupResult result;

        // Create a reference from the numbers
	    Ref ref(b, c, v);

        // TODO: convert to print to pipe instead of standard output
        verse = webBible.lookup(ref, result);
        if (result == SUCCESS) {    
            replyPipe.send(verse.getVerse());
            if (numVerses > 1) {
                for (int i = 0; i < (numVerses - 1); i++) {
	    	    	verse = webBible.nextVerse(result);
	    	    	// check result
	    	    	if (result != SUCCESS) {
	    	    		cout << webBible.error(result) << endl;
	    	    		break;
	    	    	}
	    	    	replyPipe.send(verse.getVerse());
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
        // send on reply pipe

    }
    requestPipe.fifoclose();
    replyPipe.fifoclose();

    return 0;
}