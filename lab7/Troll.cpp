#include "Troll.h"


Troll::Troll(){
    this->thickness = 1.0/(1+rand()%10);
    this->success = 0;
    this->setRole(troll);
}
Troll::Troll(shared_ptr<User> ptr):User(ptr) {
    this->thickness = 1.0/(1+rand()%10);
    this->success = 0;
    this->setRole(troll);
}
float Troll::getThickness() {
    return this->thickness;
}

void Troll::setThickness(float value) {
    this->thickness = value;
}
int  Troll::getSuccess() {
    return this->success;
}
void Troll::setSuccess(int value) {
    this->success = value;
}

