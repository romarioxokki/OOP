#pragma once
#include "User.h"



    class Moderator : public User {
    private:
        int intellect;
    public:
        Moderator();
        Moderator(shared_ptr<User>);
        int getIntellect();
        void setIntellect(int );

    };

