#include "fifo.h"
#include "Bible.h"
using namespace std;

#include "/home/class/csc3004/cgicc/Cgicc.h"
#include "/home/class/csc3004/cgicc/HTTPHTMLHeader.h"
#include "/home/class/csc3004/cgicc/HTMLClasses.h"
using namespace cgicc;

#define logging
#define LOG_FILENAME "/home/class/csc3004/tmp/pieschuiling-lookupclient.log"
#include "logfile.h"

string buildReplyMessage(string s, string delim, string& prevChap, LookupResult& status);
void buildRequestMessage(Cgicc& cgiObj, string& message, LookupResult& status);

string receive_pipe = "SSrequest";
string send_pipe = "SSreply";

int main() {
    #ifdef logging
        logFile.open(logFilename.c_str(), ios::out);
    #endif
    cout << "Content-Type: text/plain\n\n";
    Cgicc cgi;

    Fifo requestPipe(receive_pipe);
    Fifo replyPipe(send_pipe);

    string request = ""; // string to be sent on request pipe
    string messageToDisplay;
    string delim = "&";
    string previousChapter;

    requestPipe.openwrite();
    log("Request pipe opened.");
    replyPipe.openread();
    log("Reply pipe opened.");

    // Request Format: book&chap&num&numVerses
    LookupResult status = OTHER;
    // make form_iterator num_verse, convert to int, use in for loop
    buildRequestMessage(cgi, request, status);
    log("request = " + request);
    
    // if status == SUCCESS, then request should hold proper string to send on requestPipe
    // else, use status to tell user which value was invalid
    if (status == SUCCESS) {
        log("Verse Found Successfully.");
        requestPipe.send(request);
        log("Request sent to requestPipe.");
        // read messages from replyPipe
        LookupResult replyStatus = OTHER;
        messageToDisplay = buildReplyMessage(replyPipe.recv(), delim, previousChapter, replyStatus);
        cout << messageToDisplay << endl;

        form_iterator num_verse = cgi.getElement("num_verse");
        if (num_verse != cgi.getElements().end()) {
            int numberOfVerses = num_verse->getIntegerValue();
            if (numberOfVerses > 1) {
                log("numberOfVerses = " + to_string(numberOfVerses));
                for (int i = 0; i < (numberOfVerses - 1); i++) {
                    // read from replyPipe
                    messageToDisplay = buildReplyMessage(replyPipe.recv(), delim, previousChapter, replyStatus);
                    cout << messageToDisplay << endl;
                }
            }
        }
        log("Output Successful.");
    }
    else {
        cout << "<p> Search was unsuccessful. Exiting program. </p>" << endl;
        log("else clause reached. Program Terminated.");
        return 0; // exit program
    }
    
    // SUCCESS, NO_BOOK, NO_CHAPTER, NO_VERSE, OTHER
    //    0        1         2           3       4
    requestPipe.fifoclose();
    log("Request pipe closed.");
    replyPipe.fifoclose();
    log("Reply pipe closed.");

    log("--------------------------------------------");

    return 0;
}

string buildReplyMessage(string s, string delim, string& prevChap, LookupResult& status) {
    string line = s;
    if (s == "") {
        return "";
    }
    string message = "";
    string sub; // substring

    // get status
    size_t pos = line.find(delim);
    sub = line.substr(0, pos);
    line.erase(0, pos+1);
    
    // convert sub to integer, check that it's an integer
    int result = 4; // LookupResult.OTHER
    try {
        result = stoi(sub);
    }
    catch (invalid_argument ia) {
        // build message to say invalid message from pipe
        log("An invalid message was received from the server. Please try again.");
        log("Message received: " + line);
        return "An invalid message was received from the server. Please try again.";
    }

    // Try string array to add html code into the final string. 
    /* 
    1) get book
    2) get chapter
    3) form book and chapter into one string
    4) get if book/chapter string is same as previous book/chapter string
    5) get verse text
    */
    if (result == SUCCESS) {
        status = SUCCESS;
        pos = line.find(delim);
        int count = 0;
        message += "<h3>";
        while (pos != string::npos && count < 2) {
            message += line.substr(0, pos) + " ";
            line.erase(0, pos+1);
            pos = line.find(delim);
            count++;
        }
        message += "</h3>";
        if (message == prevChap) {
            // still in same chapter, erase current message and do nothing. 
            message = "";
        }
        else { // book/chapter must be updated to whatever is current stored in message
            prevChap = message;
        }
        // add verse number and text to message
        for (int i = 0; i < 2; i++) {
            pos = line.find(delim);
            if (i == 0) { // if verse number
                message += "<sup>" + line.substr(0, pos) + "</sup>";
            }
            else {  // if verse text
                message += line.substr(0, pos) + " ";
            }
            line.erase(0, pos+1);
        }
    }
    else if (result == NO_BOOK){
        status = NO_BOOK;
        message = "No Book Found.";
    }
    else if (result == NO_CHAPTER) {
        status = NO_CHAPTER;
        message = "No Chapter Found.";
    }
    else if (result == NO_VERSE) {
        status = NO_VERSE;
        message = "No Verse Found.";
    }
    else {
        status = OTHER;
        message = "Unknown Error.";
    }
    return message;
}

void buildRequestMessage(Cgicc& cgiObj, string& message, LookupResult& status) {
    Cgicc cgi = cgiObj;
    form_iterator searchType = cgi.getElement("search_type");
    form_iterator book = cgi.getElement("book");
    form_iterator chapter = cgi.getElement("chapter");
    form_iterator verse = cgi.getElement("verse");
    form_iterator num_verse = cgi.getElement("num_verse");

    if (book != cgi.getElements().end()) {
        message += to_string(book->getIntegerValue()) + "&";
    }
    else {
        status = NO_BOOK;
        return;
    }
    if (chapter != cgi.getElements().end()) {
        message += to_string(chapter->getIntegerValue()) + "&";
    }
    else {
        status = NO_CHAPTER;
        return;
    }
    if (verse != cgi.getElements().end()) {
        message += to_string(verse->getIntegerValue()) + "&";
    }
    else {
        status = NO_VERSE;
        return;
    }
    if (num_verse != cgi.getElements().end()) {
        message += to_string(num_verse->getIntegerValue()) + "&";
    }
    status = SUCCESS;
}
