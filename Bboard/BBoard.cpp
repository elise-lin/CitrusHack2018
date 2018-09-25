#include "BBoard.h"
#include "Message.h"
#include "Reply.h"
#include "Topic.h"
#include "User.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

BBoard::BBoard() {
    title = "";
    currentUser = 0;

}

BBoard::BBoard(const string & defTitle) {
    title = defTitle;
    currentUser = 0;
}

BBoard::~BBoard() {
    if(messageList.size() != 0) {
        for(unsigned i = 0; i < messageList.size(); ++i){
            delete messageList.at(i);
        }
    }
    
}

bool BBoard::loadUsers(const string & dafile) {
    bool open = true;
    string strU = "";
    string strP = "";
    
    ifstream inFS;
    inFS.open(dafile.c_str());
    
    if(!inFS.is_open()) {
        open = false;
    }
    while(inFS >> strU >> strP) {
        userList.push_back(User(strU, strP));
    }
    
    inFS.close();
    
    return open;
}

bool BBoard::loadMessages(const string &datafile) {
    bool open = true;
    bool isTopic = true;

    string author, subject, body, input, bodyhold;
    unsigned numMessages = 0;
    unsigned id = 0;

    ifstream inFS;
    inFS.open(datafile.c_str());

    if(!inFS.is_open()) {
        open = false;
    }

    inFS >> numMessages; 
    vector<string> childrenO;

    for(int i = numMessages; i > 0; --i) { //keep going until no messages

        subject = "";
        body = "";
        bodyhold = "";
        author = "";


        while(input != "<end>") {
            inFS >> input;

            if(input == "<begin_topic>") {
                isTopic = true;
            }
            if(input == "<begin_reply>") {
                isTopic = false;
            }

            if(input == ":id:") {
                inFS >> id;
            }
            else if(input == ":subject:") {
                inFS.ignore();
                getline(inFS, subject);
            }
            else if(input == ":from:") {
                inFS >> author;
            }
            else if(input == ":children:") {
                getline(inFS, input);
                childrenO.push_back(input);                
            }
            else if(input == ":body:") {
                if(id > childrenO.size()) {
                    childrenO.push_back("");
                }
                inFS.ignore();
                body = "";
                bodyhold = "";
                getline(inFS, bodyhold);
                while(bodyhold.find("<end>") == string::npos) {
                    body += bodyhold + '\n';
                    getline(inFS, bodyhold);
                }
                body = body.substr(0, body.size() - 1);
                break;
            }
            else if(input == "<end>") {
                break;
            }
        }
        
        if(isTopic) {
            Topic *temp = new Topic(author, subject, body, id);
            messageList.push_back(temp);
        } 
        if(!isTopic) {
            Reply *tempI = new Reply(author, subject, body, id);
            messageList.push_back(tempI);
        }
    }

    inFS.close();


    for(unsigned i = 0; i < childrenO.size(); ++i) {
        int childInt = 0;
        stringstream iSS(childrenO.at(i));
        while(iSS >> childInt) {
            messageList.at(i)->addChild(messageList.at(childInt - 1));
        }
    }

    return open;
}

bool BBoard::saveMessages(const string &datafile) {
    ofstream outFS;

    outFS.open(datafile.c_str());

    if(!outFS.is_open()) {
        return false;
    }

    if(messageList.size() == 0) {
        return false;
    }

    outFS << messageList.size() << endl; //# of messages

    for(unsigned i = 0; i < messageList.size(); ++i) {
        outFS << messageList.at(i)->toFormattedString();
    }

    outFS.close();

    return true;
}


bool BBoard::userExists(const string &usern, const string &passw) const {
    bool exists = false;
    
    for(unsigned i = 0; i < userList.size(); ++i) {
        if((usern == userList.at(i).getUsername()) && (passw == userList.at(i).getPassword())) {
            exists = true; 
        } 
    } 
    
    return exists;
}

void BBoard::login() {
    string usernam;
    string passwd;
    
    cout << "Welcome to " << title << endl;
    
    while ( getUser(usernam,passwd) == NULL ) {
        cout << "Enter your username ('Q' or 'q' to quit): ";
        cin >> usernam;   
        
        if (usernam == "Q" || usernam == "q") {   
            cout << "Bye!" << endl;
            currentUser = 0;
            return;
        } else {      
            cout << "Enter your password: ";
            cin >> passwd;
            
            if (getUser(usernam,passwd) == NULL) {  
                cout << "Invalid Username or Password!" << endl << endl;
            } else {    
                cout << "\nWelcome back " << usernam << "!" << endl;
                currentUser = getUser(usernam,passwd);
            }
        }
        
    }
}

void BBoard::display() const {
    if(messageList.size() == 0) {
        cout << "Nothing to Display.\n";
    } else {
        for(unsigned i = 0; i < messageList.size(); ++i) {
            if(!(messageList.at(i)->isReply())) {
                cout << "---------------------------------------------------------" << endl;
                messageList.at(i)->print(0);
            } 
        }
        cout << "---------------------------------------------------------" << endl;
    }
}

void BBoard::addTopic() {
    string author = currentUser->getUsername();
    string body;
    string test = "";
    string subject;

    unsigned id = messageList.size() + 1;

    cin.ignore();
    cout << "Enter Subject: ";
    getline(cin, subject);

    cout << "Enter Body: ";
    getline(cin, test);

    while(test != "") {
        body += test + '\n';
        getline(cin, test);
    }
    body = body.substr(0, body.size() - 1);

    Topic *tempo = new Topic(author, subject, body, id);
    messageList.push_back(tempo);

    return;
}

void BBoard::addReply() {
    string author = currentUser->getUsername();
    string body, subject = "";
    string temp;
    unsigned messageID;
    unsigned id = messageList.size() + 1;

    while(1) {
        cout << "Enter Message ID (-1 for Menu): ";
        cin >> messageID;

        if(messageID < 0) {
            return;
        }
        else if (messageID == 0 || messageID > messageList.size()) {
            cout << "Invalid Message ID!!\n";
        } else {
            break;
        }
    }

    subject = "Re: " + messageList.at(messageID - 1)->getSubject();
    cin.ignore();
    cout << "Enter Body: ";
    getline(cin, temp);
    while(temp != "") {
        body += temp + '\n';
        getline(cin, temp);
    }

    body = body.substr(0, body.size() - 1);
    Reply *tempo = new Reply(author, subject, body, id);
    messageList.push_back(tempo);
    messageList.at(messageID - 1)->addChild(tempo);
    return; 
}

void BBoard::run() {
    char action;
    
    if(currentUser == 0) {
        return;
    }

    do {
        cout << endl << "Menu" << endl; 
        cout << "- Display Messages ('D' or 'd')" << endl;
        cout << "- Add New Topic ('N' or 'n')" << endl;
        cout << "- Add Reply to a Topic ('R' or 'r')" << endl;
        cout << "- Quit ('Q' or 'q')" << endl;

        cout << "Choose an action: ";
        cin >> action;  

        if (action == 'D' || action == 'd') { 
            cout << endl;
            display();
        } else if( action == 'N' || action == 'n' ) { 
            addTopic();
        } else if( action == 'R' || action == 'r' ) { 
            addReply();
        } else if( action == 'Q' || action == 'q' ) { 
            cout << "Bye!" << endl;
            return;
        } else {   
            cout << "Invalid action. Please try again." << endl << endl;
        }
    } 

    while(action != 'Q' || action != 'q');
}

const User * BBoard::getUser(const string &name, const string &pw) const {
    for(unsigned i = 0; i < userList.size(); ++i) {
        if(userList.at(i).check(name, pw)) {
            return &userList.at(i);
        }
    }

    return 0;
}
