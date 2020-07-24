//
// Created by 周庆 on 2019/8/28.
//

#ifndef C___MESSAGE_H
#define C___MESSAGE_H

#include <string>
#include <set>

class Folder;

class Message {
    friend class Folder;
    friend void swap(Message &, Message &);
    friend void swap(Folder &lhs, Folder &rhs);
public:
    explicit Message(const std::string &s = "") : content(s), folders() {};
    Message(const Message &);
    Message &operator=(const Message &);
    ~Message();
    Message(Message &&);
    Message &operator=(Message &&);
    void save(Folder &);
    void remove(Folder &);
private:
    std::string content;
    std::set<Folder *> folders;
    void add_to_folder(const Message &);
    void remove_from_folder();
    void addFdr(Folder *);
    void remFdr(Folder *);
};

void swap(Message &, Message &);

#endif //C___MESSAGE_H
