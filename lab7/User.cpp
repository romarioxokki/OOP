#include "User.h"

    User::User(){
    this->login = nullptr;
    this->registrationDate = nullptr;
    this->messageCount = 0;
    this->chapter = nullptr;
    this->status = offline;
    this->role = user;
    }

    User::User(string log, string date) {
        this->login = log;
        this->registrationDate = date;
        this->messageCount = 0;
        this->status = offline;
        this->chapter = 0;
        this->role = user;
    }
    User::User(string log){
    this->login = log;
    this->registrationDate = '0';
    this->messageCount = 0;
    this->status = offline;
    this->chapter = 0;
    this->role = user;
}
    User::User(shared_ptr<User> user){
    this->login = user->getLogin();
    this->registrationDate = user->getRegistrationDate();
    this->messageCount = user->getMessageCount();
    this->status = StringToStatus(user->getStatus());
    this->chapter = user->getChapter();
    this->role = user->getType();
}
    shared_ptr<Section> User::getChapter() const {
    return this->chapter;
}
    void User::setChapter(shared_ptr<Section> value){
    this->chapter = value;
}
    string User::getLogin() const {
        return this->login;
    }

    void User::setLogin(string log) {
        this->login = log;
    }

    string User::getRegistrationDate() const {
        return this->registrationDate;
    }

    void User::setRegistrationDate(string date) {
        this->registrationDate = date;
    }

    long long User::getMessageCount() const {
    return this->messageCount;
    }

    void User::setMessageCount(long long count) {
        this->messageCount = count;
    }

    string User::StatusToString(Status e)const {
        switch (e) {
            case Status::offline: return "offline";
            case Status::online: return "online";
            case Status::banned: return "banned";
            default: throw std::invalid_argument("Unimplemented item for status");
        }
    }

    Status User::StringToStatus(string value) {
        if (value == "offline"){
            return offline;
        }
        if (value == "online"){
            return online;
        }
        if (value == "banned"){
            return banned;
        }
        throw std::invalid_argument("Unimplemented string for status");
    }

    void User::changeStatus(string value) {
      this->status = StringToStatus(value);
    }
    string User::getStatus() const {
        return StatusToString(this->status);
    }

     Role User::getType() const {
        return this->role;
    }
    void User::setRole(Role r) {
    this->role = r;
}
    void User::sendMessage() {
    size_t n = 20;
    default_random_engine generator;
    binomial_distribution<int> distribution(n,0.3f);
    int number = fabs(distribution(generator));
    int res = this->getMessageCount();
    res += number;
    this->setMessageCount(res);
}

