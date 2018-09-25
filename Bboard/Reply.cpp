#include "Message.h"
#include "User.h"
#include "Topic.h"
#include "Reply.h"
#include <iostream>
#include <vector>
#include <sstream>

Reply::Reply() : Message() {}

Reply::Reply(const string &athr, const string &sbjct, const string &body, unsigned id) : 
     		 Message(athr, sbjct, body, id) {}

bool Reply::isReply() const {
	return true;
}

string Reply::toFormattedString() const {
	string newFormat; //concatenating 

	newFormat = "<begin_reply>\n:id: " + IntToString(id) + 
				"\n:subject: " + subject + "\n:from: " + 
				author; 

	if(childList.size() != 0) {
		newFormat += "\n:children: ";

		for(unsigned i = 0; i + 1 < childList.size(); ++i) {
			newFormat = newFormat + IntToString(childList.at(i)->getID()) + " ";
		}
		newFormat += IntToString(childList.at(childList.size() - 1)->getID());
	} 

	newFormat = newFormat + '\n' + ":body: " + body + '\n' + "<end>" + '\n';

	return newFormat;
	
}

string Reply::IntToString(unsigned number) const {
	stringstream ss; //create stringstream
	ss << number; //add number to stream
	return ss.str(); //return string w/ contents of stream
}