#include "Moderator.h"

int Moderator::getIntellect() {
    return this->intellect;
}
Moderator::Moderator() {
    this->intellect = 1+rand()%10;
    this->setRole(moderator);
}
Moderator::Moderator(shared_ptr<User> ptr): User(ptr){
    this->intellect = 1+rand()%10;
    this->setRole(moderator);
}
void Moderator::setIntellect(int value) {
    this->intellect = value;
}

