#include "fifo.h"

#include <iostream>

using namespace std;

string receive_pipe = "SSrequest";
string send_pipe = "SSreply";

int main() {
    Fifo requestPipe(receive_pipe);
    Fifo replyPipe(send_pipe);

    // TODO: open replyPipe for reading and requestPipe for writing
    //  keep program running 

    replyPipe.openread(); 
    requestPipe.openwrite();
    while(true) {
        // send messages on requestPipe
    }
}