//
// Created by 周庆 on 2019/8/30.
//

#ifndef C___STRVEC_H
#define C___STRVEC_H

#include <string>
#include <memory>
#include <initializer_list>

class StrVec {
    friend bool operator==(const StrVec &, const StrVec &);
    friend bool operator!=(const StrVec &, const StrVec &);
    friend bool operator<(const StrVec &, const StrVec &);
    friend bool operator>(const StrVec &, const StrVec &);
    friend bool operator<=(const StrVec &, const StrVec &);
    friend bool operator>=(const StrVec &, const StrVec &);
public:
    typedef size_t size_type;
    StrVec() : first_element(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(std::initializer_list<std::string>);

    StrVec(const StrVec &);
    StrVec &operator=(const StrVec &);
    ~StrVec();
    StrVec(StrVec &&) noexcept ;
    StrVec &operator=(StrVec &&) noexcept ;

    StrVec &operator=(std::initializer_list<std::string>);
    std::string &operator[](size_type n) {return first_element[n];}
    const std::string &operator[](size_type n) const {return first_element[n];}

    void push_back(const std::string &);
    void pop_back();

    bool empty() const {return cbegin() == cend();}
    void reserve(size_type);
    void resize(size_type, const std::string & = std::string());

    template <typename... Args>
    void emplace_back(Args&&...);

    size_type size() const {return first_free - first_element;}
    size_type capacity() const {return cap - first_element;}
    std::string *begin() {return first_element;}
    std::string *end() {return first_free;}
    const std::string *begin() const {return first_element;}
    const std::string *end() const {return first_free;}
    const std::string *cbegin() const {return begin();}
    const std::string *cend() const {return end();}

private:
    static std::allocator<std::string> alloc;

    std::string *first_element;
    std::string *first_free;
    std::string *cap;

    void chk_n_copy() {if (size() == capacity()) reallocate();}
    std::pair<std::string *, std::string *> alloc_n_copy(const std::string *, const std::string *);
    void reallocate();
    void free();
};

bool operator==(const StrVec &, const StrVec &);
bool operator!=(const StrVec &, const StrVec &);
bool operator<(const StrVec &, const StrVec &);
bool operator>(const StrVec &, const StrVec &);
bool operator<=(const StrVec &, const StrVec &);
bool operator>=(const StrVec &, const StrVec &);

template <typename... Args>
inline void
StrVec::emplace_back(Args &&... args) {
    chk_n_copy();
    alloc.construct(first_free++, std::forward<Args>(args)...);
}

#endif //C___STRVEC_H
