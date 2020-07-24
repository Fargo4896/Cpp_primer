//
// Created by 周庆 on 2019-07-11.
//

#ifndef C___STRBLOB_H
#define C___STRBLOB_H

#include <memory>
#include <string>
#include <vector>
#include <initializer_list>
#include <iostream>

class StrBlobPtr;
class ConstStrBlobPtr;

class StrBlob {
    friend class StrBlobPtr;
    friend class ConstStrBlobPtr;
    friend bool operator==(const StrBlob &, const StrBlob &);
    friend bool operator!=(const StrBlob &, const StrBlob &);
    friend bool operator<(const StrBlob &, const StrBlob &);
    friend bool operator>(const StrBlob &, const StrBlob &);
    friend bool operator<=(const StrBlob &, const StrBlob &);
    friend bool operator>=(const StrBlob &, const StrBlob &);

public:
    typedef std::vector<std::string>::size_type size_type;

    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    StrBlob(const StrBlob &);

    StrBlob &operator=(const StrBlob &);

    std::string &operator[](size_type n) {return (*data)[n];}
    const std::string &operator[](size_type n) const {return (*data)[n];}

    size_type size() const {return data->size();}
    bool empty() const {return data->empty();}

    void push_back(const std::string &s);
    void push_back(std::string &&s);
    void pop_back();

    std::string& front();
    const std::string& front() const;
    std::string& back();
    const std::string& back() const;

    StrBlobPtr begin();
    StrBlobPtr end();

    ConstStrBlobPtr cbegin() const;
    ConstStrBlobPtr cend() const;

private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type pos, const std::string &msg) const;
};

inline void StrBlob::push_back(const std::string &s) {
    std::cout << "lvalue push back" << std::endl;
    data->push_back(s);
}

inline void StrBlob::push_back(std::string &&s) {
    std::cout << "rvalue push back" << std::endl;
    data->push_back(std::move(s));
}

bool operator==(const StrBlob &, const StrBlob &);
bool operator!=(const StrBlob &, const StrBlob &);
bool operator<(const StrBlob &, const StrBlob &);
bool operator>(const StrBlob &, const StrBlob &);
bool operator<=(const StrBlob &, const StrBlob &);
bool operator>=(const StrBlob &, const StrBlob &);

#endif //C___STRBLOB_H
