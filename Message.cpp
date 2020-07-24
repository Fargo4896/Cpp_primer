//
// Created by 周庆 on 2019/8/28.
//

#include <iostream>
#include "Message.h"
#include "Folder.h"

void Message::save(Folder &f) {
    folders.insert(&f);
    f.addMsg(this);
}

void Message::remove(Folder &f) {
    folders.erase(&f);
    f.remMsg(this);
}

void Message::add_to_folder(const Message &f) {
    for (auto &fp : f.folders)
        fp->addMsg(this);
}

void Message::remove_from_folder() {
    for (auto &fp : folders)
        fp->remMsg(this);
    folders.clear();
}

void Message::addFdr(Folder *f) {
    folders.insert(f);
}

void Message::remFdr(Folder *f) {
    folders.erase(f);
}

Message::Message(const Message &m) : content(m.content), folders(m.folders){
    add_to_folder(m);
}

Message& Message::operator=(const Message &rhs) {
    remove_from_folder();
    content = rhs.content;
    folders = rhs.folders;
    add_to_folder(rhs);
    return *this;
}

Message::~Message() {
    remove_from_folder();
}

Message::Message(Message &&rhs) : content(std::move(rhs.content)), folders(std::move(rhs.folders)) {
    std::cout << "move constructor used" << std::endl;
    for (auto &p : folders)
    {
        p->remMsg(&rhs);
        p->addMsg(this);
    }
    rhs.folders.clear();
}

Message& Message::operator=(Message &&rhs) {
    std::cout << "move assignment operator used" << std::endl;
    if (this != &rhs)
    {
        content = std::move(rhs.content);
        folders = std::move(rhs.folders);
        for (auto &p : folders)
        {
            p->remMsg(&rhs);
            p->addMsg(this);
        }
        rhs.folders.clear();
    }
    return *this;
}

void swap(Message &lhs, Message &rhs)
{
    using std::swap;
    for (auto &fp : lhs.folders)
        fp->remMsg(&lhs);
    for (auto &fp : rhs.folders)
        fp->remMsg(&rhs);
    swap(lhs.folders, rhs.folders);
    swap(rhs.content, rhs.content);
    for (auto &fp : lhs.folders)
        fp->addMsg(&lhs);
    for (auto &fp : rhs.folders)
        fp->addMsg(&rhs);
}