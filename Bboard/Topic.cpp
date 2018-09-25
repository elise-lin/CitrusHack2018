#include "Topic.h"
#include "Message.h"
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

Topic::Topic() : Message() {}


Topic::Topic(const string &athr, const string &sbjct, const string &body, unsigned id) : 
     		 Message(athr, sbjct, body, id) {}

bool Topic::isReply() const {
	return false;
}

string Topic::toFormattedString() const {
	string newFormat; //concatenating 

	newFormat = "<begin_topic>\n:id: " + IntToString(id) + 
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

string Topic::IntToString(unsigned number) const {
	stringstream ss; //create stringstream
	ss << number; //add number to stream
	return ss.str(); //return string w/ contents of stream
}