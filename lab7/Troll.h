#pragma once
#include "User.h"

class Troll : public User {
    private:
        float thickness;
        int   success;
    public:
        Troll();
        Troll(shared_ptr<User>);
        float getThickness();
        void setThickness(float );
        int   getSuccess();
        void setSuccess(int);
    };