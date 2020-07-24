//
// Created by 周庆 on 2019/8/28.
//

#ifndef C___FOLDER_H
#define C___FOLDER_H

#include <string>
#include <set>

class Message;

class Folder {
    friend class Message;
    friend void swap(Folder &, Folder &);
    friend void swap(Message &, Message &);
public:
    Folder() = default;
    void save(Message &);
    void remove(Message &);
    Folder(const Folder &);
    Folder &operator=(const Folder &);
    ~Folder();
private:
    std::set<Message *> messages;
    void addMsg(Message *);
    void remMsg(Message *);
};

void swap(Folder &, Folder &);

#endif //C___FOLDER_H
