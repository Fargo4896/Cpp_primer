//
// Created by 周庆 on 2019/10/6.
//

#ifndef C___CONSTBLOBPTR_H
#define C___CONSTBLOBPTR_H

template <typename T> class Blob;
template <typename T> class ConstBlobPtr;
template <typename T> bool operator==(const ConstBlobPtr<T> &, const ConstBlobPtr<T> &);
template <typename T> bool operator<(const ConstBlobPtr<T> &, const ConstBlobPtr<T> &);
template <typename T> bool operator-(const ConstBlobPtr<T> &, const ConstBlobPtr<T> &);

#include <vector>
#include <memory>
#include <string>
#include <stdexcept>
#include "Blob.h"

template <typename T>
class ConstBlobPtr {
    friend bool operator==<T>(const ConstBlobPtr &, const ConstBlobPtr &);
    friend bool operator< <T>(const ConstBlobPtr &, const ConstBlobPtr &);
    friend bool operator-<T>(const ConstBlobPtr &, const ConstBlobPtr &);

public:
    using size_type = typename std::vector<T>::size_type;
    ConstBlobPtr() : wptr(), curr(0) { }
    explicit ConstBlobPtr(Blob<T> &b, size_type pos = 0) : wptr(b.data), curr(0) {
        check(pos, "BlobPtr initial position out of range");
        curr = pos;
    }

    const T &operator*() const {
        return (*check(curr + 1, "dereference out pf range"))[curr];
    }

    const T *operator->() const {
        return &**this;
    }

    ConstBlobPtr &operator++() {
        check(curr + 1, "BlobPtr increment pass the end");
        ++curr;
        return *this;
    }

    ConstBlobPtr operator++(int) {
        ConstBlobPtr ret = *this;
        ++*this;
        return ret;
    }

    ConstBlobPtr &operator--() {
        check(curr - 1, "BlobPtr decrement pass the beginning");
        --curr;
        return *this;
    }

    ConstBlobPtr operator--(int) {
        ConstBlobPtr ret = *this;
        --*this;
        return ret;
    }

    ConstBlobPtr &operator+=(int n) {
        check(curr + n, "compound assignment out pf range");
        curr += n;
        return *this;
    }

    ConstBlobPtr &operator-=(int n) {
        return *this + -n;
    }

    ConstBlobPtr operator+(int n) const {
        ConstBlobPtr ret = *this;
        return ret += n;
    }

    ConstBlobPtr operator-(int n) const {
        ConstBlobPtr ret = *this;
        return ret -= n;
    }

private:
    std::weak_ptr<std::vector<T>> wptr;
    size_type curr;

    std::shared_ptr<std::vector<T>>
    check(size_type pos, const std::string &msg) const {
        std::shared_ptr<std::vector<T>> ret = wptr.lock();
        if (!ret)
            throw std::runtime_error("unbound BlobPtr");
        else if (pos > ret->size())
            throw std::out_of_range(msg);
        return ret;
    }
};

template <typename T>
int operator-(const ConstBlobPtr<T> &lhs, const ConstBlobPtr<T> &rhs) {
    return lhs.curr - rhs.curr;
}

template <typename T>
bool operator==(const ConstBlobPtr<T> &lhs, const ConstBlobPtr<T> &rhs) {
    // compare identity
    return lhs.wptr.lock() == rhs.wptr.lock() && lhs.curr == rhs.curr;
}

template <typename T>
bool operator!=(const ConstBlobPtr<T> &lhs, const ConstBlobPtr<T> &rhs) {
    return !(lhs == rhs);
}

template <typename T>
bool operator<(const ConstBlobPtr<T> &lhs, const ConstBlobPtr<T> &rhs) {
    // compare identity
    return lhs.wptr.lock() == rhs.wptr.lock() && lhs.curr < rhs.curr;
}

template <typename T>
bool operator>(const ConstBlobPtr<T> &lhs, const ConstBlobPtr<T> &rhs) {
    return rhs < lhs;
}

template <typename T>
bool operator<=(const ConstBlobPtr<T> &lhs, const ConstBlobPtr<T> &rhs) {
    return !(lhs > rhs);
}

template <typename T>
bool operator>=(const ConstBlobPtr<T> &lhs, const ConstBlobPtr<T> &rhs) {
    return !(lhs < rhs);
}

using ConstStrBlobPtr = ConstBlobPtr<std::string>;


#endif //C___CONSTBLOBPTR_H
