# Bibleajax program
# Bob Kasper, MVNU Computer Science
# updated January 2020 to use
# c++11 compiler option, current paths on cs.mvnu.edu

# This is a Makefile for the Bible web app demo program.
# Copy this directory to a location within your home directory. 
# Change the USER name value below to your own user name.
# Then use "make" to build the server program,
# and deploy it to the live web server directory.
# To test the program, go to http://cs.mvnu.edu/class/csc3004/USER/
# and open the bibleajax.html link.

# TO DO: Must replace "username" by your username
USER= pieschuiling

# Use GNU C++ compiler with C++11 standard
CC= g++
CFLAGS= -g -std=c++11

#all:	bibleajax.cgi PutCGI PutHTML
all: lookupserver lookupclient

# TO DO: For bibleajax.cgi, add dependencies to include
# compiled classes from Project 1 to be linked into the executable program
#bibleajax.cgi:	bibleajax.o Ref.o Verse.o Bible.o
#		$(CC) $(CFLAGS) -o bibleajax.cgi bibleajax.o Ref.o Verse.o Bible.o -lcgicc
# -l option is necessary to link with cgicc library


# main program to handle AJAX/CGI requests for Bible references
#bibleajax.o:	bibleajax.cpp Ref.h Verse.h Bible.h
#		$(CC) $(CFLAGS) -c bibleajax.cpp

# TO DO: copy targets to build classes from Project 1:
# Bible.o, Ref.o, Verse.o

#testreader: 	testreader.o Bible.o Ref.o Verse.o
#		$(CC) $(CFLAGS) -o testreader Ref.o Verse.o Bible.o testreader.o
#
#testreader.o: 	testreader.cpp Ref.h Verse.h Bible.h
#		$(CC) $(CFLAGS) -c testreader.cpp

#Server-Side lookup
lookupserver: 	lookupserver.o fifo.o Bible.o Ref.o Verse.o
	$(CC) $(CFLAGS) -o lookupserver fifo.o Ref.o Verse.o Bible.o lookupserver.o

lookupserver.o: lookupserver.cpp fifo.h Ref.h Verse.h Bible.h
	$(CC) $(CFLAGS) -c lookupserver.cpp

#Client-Side lookup
lookupclient: lookupclient.o fifo.o
	$(CC) $(CFLAGS) -o lookupclient fifo.o lookupclient.o

lookupclient.o: lookupclient.cpp fifo.h
	$(CC) $(CFLAGS) -c lookupclient.cpp
	
#Pipe
fifo.o: fifo.h fifo.cpp
	$(CC) $(CFLAGS) -c fifo.cpp

# Ref Object
Ref.o : Ref.h Ref.cpp
	$(CC) $(CFLAGS) -c Ref.cpp

# Verse Object
Verse.o : Ref.h Verse.h Verse.cpp
	$(CC) $(CFLAGS) -c Verse.cpp

# Bible Object
Bible.o : Ref.h Verse.h Bible.h Bible.cpp
	$(CC) $(CFLAGS) -c Bible.cpp
			
#PutCGI:	bibleajax.cgi
#		chmod 755 bibleajax.cgi
#		cp bibleajax.cgi /var/www/html/class/csc3004/$(USER)/cgi-bin
#
#		echo "Current contents of your cgi-bin directory: "
#		ls -l /var/www/html/class/csc3004/$(USER)/cgi-bin/

#PutHTML:
#		cp bibleajax.html /var/www/html/class/csc3004/$(USER)
#
#		echo "Current contents of your HTML directory: "
#		ls -l /var/www/html/class/csc3004/$(USER)

clean:		
#rm *.o core bibleajax.cgi
		rm *.o core lookupserver
		rm *.0 core lookupclient
