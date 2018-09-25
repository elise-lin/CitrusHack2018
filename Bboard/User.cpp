#include "User.h"

User::User() {
    username = "";
    password = "";
}

User::User(const string& uname, const string& pass) {
    username = uname;
    password = pass;
}

string User::getUsername() const {
    return username;
}

string User::getPassword() const {
    return password;
}

bool User::check(const string &uname, const string &pass) const {
    
    if((uname == "") && (pass == "")) {
        return false;
    } else if((uname == username) && (pass == password)) {
        return true;
    }  
    
    return false;
}

bool User::setPassword(const string &oldpass, const string &newpass) {
    bool value = false;
    
    if((oldpass == password) && (oldpass != "")) {
        password = newpass;
        value = true;
    }
    
    return value;
}