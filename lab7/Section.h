#ifndef LAB7_SECTION_H
#define LAB7_SECTION_H

#include "Moderator.h"
#include <bits/stdc++.h>
#include "User.h"

using namespace std;

class User;
class Moderator;

class Section{
private:
    vector<shared_ptr<User>> onlineUser;
    string name;
    shared_ptr<Moderator> mainModerator;
public:
    Section(string, shared_ptr<Moderator>);
    string getName();
    void setName(string );
    vector<shared_ptr<User>> getOnlineUser();
    shared_ptr<Moderator> getMainModerator();
    void addUserToSection(shared_ptr<User>);
    void removeUserFromSection(shared_ptr<User>);

};

#endif