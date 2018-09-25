//BBoard.h
#ifndef BBOARD_H
#define BBOARD_H
#include "Message.h"
#include "User.h"
#include "Topic.h"
#include "Reply.h"
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;


class BBoard {
 private:
    string title;
    vector<User> userList;
    const User * currentUser; //User currentUser;
    vector<Message* > messageList; 

 public:
    // Constructs a board with a default title, 
    // empty user & message lists, 
    // and the "default" User 
    BBoard();

    // Same as the default constructor except 
    // it sets the title of the board
    BBoard(const string & defTitle);

    //destructor that deallocates all Messages pointed by messageList
    ~BBoard();

    // Imports all the authorized users from an input file, 
    // storing them as User objects in the vector userList 
    // The name of the input file is passed in as a parameter to this function.
    // Returns true if the file opened, false if it did not. 
    // See specifications for file format.
    bool loadUsers(const string & dafile);

    bool loadMessages(const string &datafile);

    bool saveMessages(const string &datafile);

    // Asks for and validates a user/password.
    // Always asks for both user and password combo unless 'q' or 'Q' entered.
    // Checks userList to validate user and password.
    // If valid, sets currentUser to this User, outputs welcome message, 
    // then returns true.
    // Otherwise outputs error message and then repeats request
    // for username/password.
    // Continues until valid user/password 
    // or until 'q' or 'Q' is entered for username.
    // If 'q' or 'Q' is entered, does not ask for password, outputs "Bye!"
    // and then returns false.
    void login();

    // Contains main loop of Bulletin Board.
    // First verifies a User has been logged in before calling this function.
    // (Do not call login function within this function.)
    // Returns from **function** immediately if no User logged in (Default User).
    // Continues to display menu options to user and performs requested action
    // until user chooses to quit.
    // See output samples for exact format of menu.
    void run(); 

 private:
    void display() const;
    void addTopic();
    void addReply();
    bool userExists(const string &usern, const string &passw) const;
    const User * getUser(const string &name, const string &pw) const;
};

#endif