//
// Created by 周庆 on 2019/8/28.
//

#include "Folder.h"
#include "Message.h"

void Folder::save(Message &m) {
    messages.insert(&m);
    m.folders.insert(this);
}

void Folder::remove(Message &m) {
    messages.erase(&m);
    m.folders.erase(this);
}

void Folder::addMsg(Message *m) {
    messages.insert(m);
}

void Folder::remMsg(Message *m) {
    messages.erase(m);
}

void swap(Folder &lhs, Folder &rhs)
{
    using std::swap;
    for (auto &fp : lhs.messages)
        fp->folders.erase(&lhs);
    for (auto &fp : rhs.messages)
        fp->folders.erase(&rhs);
    swap(lhs.messages, rhs.messages);
    for (auto &fp : lhs.messages)
        fp->folders.insert(&lhs);
    for (auto &fp : rhs.messages)
        fp->folders.insert(&rhs);
}

Folder::Folder(const Folder &m) : messages(m.messages) {
    for (auto &fp : messages)
        fp->folders.insert(this);
}

Folder& Folder::operator=(const Folder &rhs) {
    for (auto &fp : messages)
        fp->folders.erase(this);
    messages = rhs.messages;
    for (auto &fp : messages)
        fp->folders.insert(this);
    return *this;
}

Folder::~Folder() {
    for (auto &fp : messages)
        fp->folders.erase(this);
}