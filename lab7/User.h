#ifndef LAB7_USER_H
#define LAB7_USER_H

#include "bits/stdc++.h"

class Section;

using namespace std;

enum Status{
    online,
    offline,
    banned,
};
enum Role{
    user,
    moderator,
    troll,
};
    class User {
    private:
        string login;
        string registrationDate;
        long long messageCount;
        shared_ptr<Section> chapter;
        Status status;
        Role role;
    public:
        User();
        User(string log);
        User(string log, string date);
        User(shared_ptr<User> );

        Role getType() const;
        string getLogin() const;
        void setLogin(string);
        string getRegistrationDate() const;
        void setRegistrationDate(string);
        long long getMessageCount() const;
        void setMessageCount(long long);
        void setRole(Role);
        void changeStatus(string);
        string getStatus() const;
        void sendMessage();
        bool operator< (const User& second) const{
            return this->login<second.login;
        }
        shared_ptr<Section> getChapter() const;
        void setChapter(shared_ptr<Section>);
        // help function
        string StatusToString(Status) const;
        Status StringToStatus(string);

    };

#endif
