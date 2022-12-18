#include "User.h"
#include "Forum.h"
using namespace std;
string RoleToString(Role e){
    switch (e) {
        case Role::user: return "user";
        case Role::moderator: return "moderator";
        case Role::troll: return "troll";
        default: throw std::invalid_argument("Unimplemented item for status");
    }
}
int main()
{
    Forum forum;
    system("chcp 65001");
    int n = 0;
    string login;
    while (n != -1){
        cout << "РАЗДЕЛЫ ---------------------------------------------------:\n";
        for (int i = 0; i < forum.getAllSection().size();i++){
            cout << i+1 << "." << forum.getAllSection()[i]->getName() << " " << forum.getAllSection()[i]->getMainModerator()->getLogin() <<" " << forum.getAllSection()[i]->getOnlineUser().size() << endl;
        }
        cout << "ПОЛЬЗОВАТЕЛИ ----------------------------------------------:\n";
        map<string,shared_ptr<User>> kek = forum.getAllUsers();
        auto it = kek.begin();
        for (int i = 0;it != kek.end();it++,i ++){
            cout << i+1 << "." << (*it).first << " " << RoleToString(it->second->getType()) << " " << it->second->getStatus();
            if (it->second->getChapter()!= nullptr) cout << " "<< it->second->getChapter()->getName();
            if (it->second->getType() == moderator){
                cout << " " << static_pointer_cast<Moderator>(it->second)->getIntellect();
            }
            if (it->second->getType() == troll){
                cout << " " << static_pointer_cast<Troll>(it->second)->getThickness();
            }
            cout << endl;
        }


        cout <<"------------------------------------------------------------:\n";
        cout << "1.Добавление раздела с указанием названия и назначением модератора\n";
        cout << "2.Регистрация участника на форуме\n";
        cout << "3.Заход участника в раздел (с уходом из предыдущего раздела, если он был)\n";
        cout << "4.Явное изменение статуса участника (назначение модератором или начало троллинга)\n";
        cout << "5.Изменение разумности модератора или толщины тролля\n";
        cout << "6.выход участника на форум или уход с форума (online<->offline)\n";
        cin >> n;
        if (n == 1){
            string Name;
            cout << "Введите имя модератора:\n";
            cin >> Name;
            map<string,shared_ptr<User>> tmp = forum.getAllUsers();
            if (tmp.count(Name) == 0){
                cout << "Нет такого пользователя" << endl;
                continue;
            }
            shared_ptr<User> ptr = tmp.find(Name)->second;
            forum.changeRole(ptr,moderator);
            cout << "Введите название раздела:\n";
            string section;
            cin >> section;
            forum.addSection(section, static_pointer_cast<Moderator>(forum.getAllUsers().find(Name)->second));
        }
        if (n == 2){
            string Name;
          do {
            cout << "Придумайте логин:\n";
            cin >> Name;}
           while(! forum.registrateUser(Name));
        }
        if (n == 3){
            string Name;
            cout << "Введите имя пользователя:\n";
            cin >> Name;
            map<string,shared_ptr<User>> tmp = forum.getAllUsers();

            if (tmp.count(Name) == 0){
                cout << "Нет такого пользователя" << endl;
                continue;
            }
            shared_ptr<User> ptr = tmp.find(Name)->second;
            string section;
            cout << "Введите имя раздела:\n";
            cin >> section;
            forum.moveUser(ptr,section);
        }
        if (n == 4){
            string Name;
            cout << "Введите имя пользователя:\n";
            cin >> Name;
            map<string,shared_ptr<User>> tmp = forum.getAllUsers();

            if (tmp.count(Name) == 0){
                cout << "Нет такого пользователя" << endl;
                continue;
            }
            shared_ptr<User> ptr = tmp.find(Name)->second;
            cout << "1.Сделать троллем" << endl;
            cout << "2.Сделать модератором" << endl;
            int x;
            cin >> x;
            if (x == 2){
                forum.changeRole(ptr,moderator);
            }
            else{
                forum.changeRole(ptr,troll);
            }
        }
        if (n == 5){
            string Name;
            cout << "Введите имя пользователя:\n";
            cin >> Name;
            map<string,shared_ptr<User>> tmp = forum.getAllUsers();
            if (tmp.count(Name) == 0){
                cout << "Нет такого пользователя" << endl;
                continue;
            }
            shared_ptr<User> ptr = tmp.find(Name)->second;
            if(ptr->getType() == user){
                cout << "Обычный участник без интеллекта и толщины \n";
            }
            if (ptr->getType() == troll){
                double x;
                cout << "Введите толщину троля от 0.1 до 1:\n" ;
                cin >> x;
                static_pointer_cast<Troll>(ptr)->setThickness(x);
            }
            if (ptr->getType() == moderator){
                cout << "Введите интелект модератора от 1 до 10:\n";
                double x;
                cin >> x;
                static_pointer_cast<Moderator>(ptr)->setIntellect(x);
            }
        }
        if (n == 6){
            string Name;
            cout << "Введите имя пользователя:\n";
            cin >> Name;
            map<string,shared_ptr<User>> tmp = forum.getAllUsers();
            shared_ptr<User> ptr = tmp.find(Name)->second;
            if (tmp.count(Name) == 0){
                cout << "Нет такого пользователя" << endl;
                continue;
            }
            if (ptr->getStatus() == "offline") {
                forum.enterForum(Name);
                continue;
            }
            if (ptr->getStatus() == "online") {
                forum.exitForum(Name);
                continue;
            }

        }
        if (n == 7){
            string section;
            cout << "Введите имя раздела:\n";
            cin >> section;
            forum.startPerspectiveSituation(section);
        }

    }



    return 0;
}
