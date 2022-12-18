#include "Section.h"

Section::Section(string name, shared_ptr<Moderator> moderator) {
    this->name = name;
    this->mainModerator = moderator;
    this->onlineUser.clear();
}
string Section::getName() {
    return this->name;
}
void Section::setName(string value) {
    this->name =  value;
}
shared_ptr<Moderator> Section::getMainModerator() {
    return this->mainModerator;
}
vector<shared_ptr<User>> Section::getOnlineUser() {
    return this->onlineUser;
}
void Section::addUserToSection(shared_ptr<User> value) {
    this->onlineUser.push_back(value);
}
void Section::removeUserFromSection(shared_ptr<User> value) {

  this->onlineUser.erase(remove(this->onlineUser.begin(),this->onlineUser.end(),value),this->onlineUser.end());

}