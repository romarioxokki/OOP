#include "Forum.h"

void Forum::addSection(string name, shared_ptr<Moderator> moderator) {
    Section part(name,moderator);
    this->chapter.push_back(make_shared<Section>(part));
}
Forum::Forum(){
}
Forum::Forum(vector<shared_ptr<Section>> chapters, map<string, shared_ptr<User>> allUsers, vector<shared_ptr<User>> online) {
    this->onlineUsers = online;
    this->chapter = chapters;
    this->users = allUsers;
}
bool Forum::registrateUser(string login) {
    if (this->users.count(login) > 0){
        return false;
    }
    time_t now = time(0);
    string time = ctime(&now);
    User newClient(login,time);
    this->users.insert(make_pair(login, make_shared<User>(newClient)));
    return true;

}

map<string,shared_ptr<User>> Forum::getAllUsers() {
    return this->users;
}
bool Forum::enterForum(string login) {
    auto found = this->users.find(login);

    if (found != this->users.end()){
        if ((*found).second->getStatus() == "banned"){
            cout << "You are banned!\n";
            return false;
        }
        (*found).second->changeStatus("online");
        this->onlineUsers.push_back((*found).second);
        return true;
    }
    else{
        cout << "Incorrect login, check the login or register!\n";
        return false;
    }
}
vector<shared_ptr<User>> Forum::getOnlineUsers() {
    return this->onlineUsers;
}
vector<shared_ptr<Section>> Forum::getAllSection() {
    return this->chapter;
}
vector<shared_ptr<User>> Forum::getAllBanned() {
    vector<shared_ptr<User>> res;
    auto it = this->users.begin();
    for (it = this->users.begin(); it != this->users.end();it++) {
        if (it->second->getStatus() == "banned") {
            res.push_back(((it->second)));
        }
    }
    return res;
}
bool Forum::moveUser(shared_ptr<User> user, string nameOfChapter) {
    auto it = find_if(this->chapter.begin(),this->chapter.end(),[nameOfChapter](shared_ptr<Section> &s) {return s->getName() == nameOfChapter;});
    if (it == this->chapter.end()){
        cout << "The section does not exist!";
        return false;
    }
    shared_ptr<Section> ptr = user->getChapter();
    if(ptr == nullptr) {
        user->setChapter((*it));
        (*it)->addUserToSection((user));
    }
    else{

        ptr->removeUserFromSection(user);

        user->getChapter()->removeUserFromSection((user));
        user->setChapter((*it));
        (*it)->addUserToSection((user));
    }
    return true;
}
void Forum::exitForum(string login) {
    auto found = this->users.find(login);
    if((*found).second->getStatus() == "online") {
        shared_ptr<Section> ptr = (*found).second->getChapter();
        if (ptr == 0) {
            auto it = find(this->onlineUsers.begin(), this->onlineUsers.end(), (*found).second);
            this->onlineUsers.erase(it);
            (*found).second->changeStatus("offline");
        } else {
            ptr->removeUserFromSection((*found).second);
            auto it = find(this->onlineUsers.begin(), this->onlineUsers.end(), (*found).second);
            this->onlineUsers.erase(it);
            (*found).second->changeStatus("offline");
            (*found).second->setChapter(nullptr);
        }
    }
}
void Forum::changeRole(shared_ptr<User> us, Role role) {
         if (role == moderator){
            Moderator tmp(us);
            map < string, shared_ptr<User> >::iterator it = this->users.find(tmp.getLogin());
            shared_ptr<Moderator> ptr = make_shared<Moderator>(tmp);
            it->second = ptr;
            if (us->getStatus() == "online"){
            this->onlineUsers.erase(find(this->onlineUsers.begin(),this->onlineUsers.end(),us));
            us->getChapter()->removeUserFromSection(us);
            }
            this->users.insert(make_pair(ptr->getLogin(),ptr));
            if (ptr->getStatus() == "online"){
                this->onlineUsers.push_back(ptr);
                moveUser(ptr,ptr->getChapter()->getName());
            }
        }
    if (role == troll){
        Troll tmp(us);
        map < string, shared_ptr<User> >::iterator it = this->users.find(tmp.getLogin());
        shared_ptr<Troll> ptr = make_shared<Troll>(tmp);
        it->second = ptr;
        if (us->getStatus() == "online"){
            this->onlineUsers.erase(find(this->onlineUsers.begin(),this->onlineUsers.end(),us));
            us->getChapter()->removeUserFromSection(us);
        }
        this->users.insert(make_pair(ptr->getLogin(),ptr));
        if (ptr->getStatus() == "online"){
            this->onlineUsers.push_back(ptr);
            moveUser(ptr,ptr->getChapter()->getName());
        }
        }
}
shared_ptr<Troll> Forum::getMostValuableTroll() {
    auto it = this->users.begin();
    shared_ptr<Troll> ptr = nullptr;
    int count = 0;
    int cmp = -1;
    for (;it!=this->users.end();it++){
        if (it->second->getType() == troll){
            count++;
            if (static_pointer_cast<Troll>(it->second)->getSuccess() > cmp){
                cmp = static_pointer_cast<Troll>(it->second)->getSuccess();
                ptr = static_pointer_cast<Troll>(it->second);
            }
        }
    }
    return ptr;
}

bool Forum::startPerspectiveSituation(string nameOfChapter) {
    vector<shared_ptr<Section>>::iterator it = find_if(this->chapter.begin(),this->chapter.end(),[nameOfChapter](shared_ptr<Section> &s) {return s->getName() == nameOfChapter;});
    if (it == this->chapter.end()){
        cout << "The section does not exist!";
        return false;
    }
    int sumIntellect = 0;
    int sumThickness = 0;
    int cntModerator = 0;
    int cntTroll = 0;
    vector <shared_ptr<User>> tmp = (*it)->getOnlineUser();

    vector<shared_ptr<User>>::iterator item = tmp.begin();
    for (;item!=tmp.end();item++){
        (*item)->sendMessage();
        if ((*item)->getType() == troll ){
            cntTroll++;
            sumThickness += 1.0/static_pointer_cast<Troll>((*item))->getThickness();
        }
        if ((*item)->getType() == moderator ){
            cntModerator++;
            sumIntellect += static_pointer_cast<Moderator>((*item))->getIntellect();
        }
    }
    if (sumIntellect > sumThickness){
        int random =1+rand()%((cntTroll == 0)? cntTroll+1 : cntTroll);
        vector<shared_ptr<User>> fake = (*it)->getOnlineUser();
        auto item = fake.begin();
        int cnt = 0;
        for (;item!=fake.end();item++){
            if ((*item)->getType() == troll ){
                cnt++;
                if (cnt == random){
                    this->exitForum((*item)->getLogin());
                    (*item)->changeStatus("banned");
                    cntTroll--;
                    auto tmp = (*it)->getOnlineUser().begin();
                    for (;tmp!=(*it)->getOnlineUser().end();tmp++){
                        if ((*item)->getType() == troll ) {
                            int value = static_pointer_cast<Troll>((*item))->getSuccess();
                            value++;
                            static_pointer_cast<Troll>((*item))->setSuccess(value);
                        }
                    }
                    break;
                }
            }
        }
    }else{
        vector<shared_ptr<User>> fake = (*it)->getOnlineUser();
        int random = 1 + rand()%((fake.size()-cntTroll == 0) ? fake.size()-cntTroll+1 : fake.size()-cntTroll);

        auto item = fake.begin();
        int cnt = 0;
        for (;item!=fake.end();item++){

                cnt++;
                if (cnt == random){
                    this->exitForum((*item)->getLogin());
                    (*item)->changeStatus("banned");
                    if( (*item)->getType() == moderator ) cntModerator--;
                    if( (*item)->getType() == troll ) cntTroll--;
                    auto tmp = (*it)->getOnlineUser().begin();
                    for (;tmp!=(*it)->getOnlineUser().end();tmp++){
                        if ((*item)->getType() == troll ) {
                            int value = static_pointer_cast<Troll>((*item))->getSuccess();
                            value++;
                            static_pointer_cast<Troll>((*item))->setSuccess(value);
                        }
                        }
                    break;
                    }

        }
        cnt = 0;
        vector<shared_ptr<User>> fake2 = (*it)->getOnlineUser();
         random = 1 + rand()%((fake2.size()-cntTroll== 0)? fake2.size()-cntTroll +1: fake2.size()-cntTroll );
        item = fake.begin();
        for (;item!=fake2.end();item++){
            if ((*item)->getType() != troll ){
                cnt++;
                if (cnt == random){
                    this->changeRole((*item),troll);
                    break;
                }
            }
        }

    }
    if (cntModerator == 0){
        int cnt = 0;
        vector<shared_ptr<User>> fake = (*it)->getOnlineUser();
        int random = 1 + rand()%((fake.size()==0)? fake.size()+1:fake.size());
        auto item = fake.begin();
        for (;item!=fake.end();item++){
                cnt++;
                if (cnt == random){
                    this->changeRole((*item),moderator);
                    cntModerator++;
                    break;
                }
        }

    }
    return true;
}

