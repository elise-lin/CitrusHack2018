#include "Message.h"
#include "User.h"
#include "Topic.h"
#include "Reply.h"

Message::Message() {
    author = "";
    subject = "";
    body = "";
    id = 0;
}

Message::Message(const string &athr, const string &sbjct, const string &bdy, unsigned id) :
    author(athr), subject(sbjct), body(bdy), id(id) {}

Message::~Message(){
	for(unsigned i = 0; i < childList.size(); ++i) {
		delete childList.at(i);
	}
}

void Message::print(unsigned indentation) const {
	string space = "";

	for(unsigned i = 0; i < indentation; ++i) {
		space += "  ";
	}

	if(isReply() == true) {
		cout << endl;
	} 

	cout << space << "Message #" << id << ": " << subject << endl;
	cout << space << "from " << author << ": ";

	for(unsigned i = 0; i < body.size(); ++i) {
		if(body.at(i) == '\n') {
			cout << endl;
			cout << space;
		} else {
			cout << body.at(i);
		}
	}
	cout << endl;

	if(childList.size() != 0) {
		for(unsigned i = 0; i < childList.size(); ++i) {
			childList.at(i)->print(indentation + 1);
		}
	}
	
}

const string & Message::getSubject() const {
	return subject;
}

unsigned Message::getID() const {
	return id;
}

void Message::addChild(Message *child) {
	childList.push_back(child);
}