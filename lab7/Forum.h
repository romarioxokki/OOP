#pragma once
 #include "User.h"
#include "Troll.h"
#include "Moderator.h"
#include "Section.h"

class Forum{
private:

    vector<shared_ptr<Section>> chapter;
    map<string,shared_ptr<User>> users;
    vector<shared_ptr<User>> onlineUsers;
public:
    Forum();
    Forum(vector<shared_ptr<Section>>,map<string,shared_ptr<User>>, vector<shared_ptr<User>> );
    void addSection(string , shared_ptr<Moderator>);
    bool registrateUser(string);
    bool enterForum(string );
    bool enterChapter(string );
    vector<shared_ptr<User>> getOnlineUsers();
    map<string,shared_ptr<User>> getAllUsers();
    shared_ptr<Troll> getMostValuableTroll();
    bool startPerspectiveSituation(string );
    vector<shared_ptr<Section>> getAllSection();
    vector<shared_ptr<User>> getAllBanned();
    bool moveUser(shared_ptr<User>,string );
    void changeRole(shared_ptr<User>,Role );
    void exitForum(string );



};

