//
// Created by 周庆 on 2019-07-22.
//

#ifndef C___CONSTSTRBLOBPTR_H
#define C___CONSTSTRBLOBPTR_H

#include <vector>
#include <string>
#include <memory>

class StrBlob;

class ConstStrBlobPtr {
    friend bool operator==(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator!=(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator<(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator>(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator<=(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator>=(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
public:
    typedef std::vector<std::string>::size_type size_type;

    ConstStrBlobPtr();
    explicit ConstStrBlobPtr(const StrBlob &sb, size_type pos = 0);

    const std::string &operator[](size_type n) const {return (*wptr.lock())[n];}

    const std::string &operator*() const ;
    const std::string *operator->() const ;

    ConstStrBlobPtr &operator++();
    ConstStrBlobPtr operator++(int);
    ConstStrBlobPtr &operator--();
    ConstStrBlobPtr operator--(int);

    ConstStrBlobPtr &operator+=(int);
    ConstStrBlobPtr &operator-=(int);
    ConstStrBlobPtr operator+(int) const ;
    ConstStrBlobPtr operator-(int) const ;

    int operator-(const ConstStrBlobPtr &) const ;

    //const std::string& deref() const;
    //ConstStrBlobPtr& inc();

private:
    std::weak_ptr<std::vector<std::string>> wptr;
    size_type curr;

    std::shared_ptr<std::vector<std::string>> check(size_type pos, const std::string& msg) const;
};

bool operator==(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
bool operator!=(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
bool operator<(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
bool operator>(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
bool operator<=(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
bool operator>=(const ConstStrBlobPtr &, const ConstStrBlobPtr &);

#endif //C___CONSTSTRBLOBPTR_H
