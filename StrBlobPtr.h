//
// Created by 周庆 on 2019-07-19.
//

#ifndef C___STRBLOBPTR_H
#define C___STRBLOBPTR_H

#include <vector>
#include <string>
#include <memory>

class StrBlob;

class StrBlobPtr {
    friend bool operator==(const StrBlobPtr &, const StrBlobPtr &);
    friend bool operator!=(const StrBlobPtr &, const StrBlobPtr &);
    friend bool operator<(const StrBlobPtr &, const StrBlobPtr &);
    friend bool operator>(const StrBlobPtr &, const StrBlobPtr &);
    friend bool operator<=(const StrBlobPtr &, const StrBlobPtr &);
    friend bool operator>=(const StrBlobPtr &, const StrBlobPtr &);
public:
    typedef std::vector<std::string>::size_type size_type;

    StrBlobPtr();
    explicit StrBlobPtr(StrBlob &sb, size_type pos = 0);

    std::string &operator[](size_type n) {return (*wptr.lock())[n];}
    const std::string &operator[](size_type n) const {return (*wptr.lock())[n];}

    std::string &operator*() const ;
    std::string *operator->() const ;

    StrBlobPtr &operator++();
    StrBlobPtr operator++(int);
    StrBlobPtr &operator--();
    StrBlobPtr operator--(int);

    StrBlobPtr &operator+=(int);
    StrBlobPtr &operator-=(int);
    StrBlobPtr operator+(int) const ;
    StrBlobPtr operator-(int) const ;

    int operator-(const StrBlobPtr &) const ;

    //std::string& deref() const;
    //StrBlobPtr& inc();

private:
    std::weak_ptr<std::vector<std::string>> wptr;
    size_type curr;

    std::shared_ptr<std::vector<std::string>> check(size_type pos, const std::string& msg) const;
};

bool operator==(const StrBlobPtr &, const StrBlobPtr &);
bool operator!=(const StrBlobPtr &, const StrBlobPtr &);
bool operator<(const StrBlobPtr &, const StrBlobPtr &);
bool operator>(const StrBlobPtr &, const StrBlobPtr &);
bool operator<=(const StrBlobPtr &, const StrBlobPtr &);
bool operator>=(const StrBlobPtr &, const StrBlobPtr &);
#endif //C___STRBLOBPTR_H
