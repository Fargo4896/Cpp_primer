//
// Created by 周庆 on 2019/9/2.
//

#ifndef C___HASPTR_H
#define C___HASPTR_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#define COPY_N_SWAP_ASSIGNMENT_OP

class HasPtr {
friend void swap(HasPtr &, HasPtr &);
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {}
    HasPtr(const char *cs) : ps(new std::string(cs)), i(0) {}

    HasPtr(const HasPtr &rhs) : ps(new std::string(*rhs.ps)), i(rhs.i) {
        std::cout << "copy constructor used" << std::endl;
    }
    ~HasPtr();

#ifndef COPY_N_SWAP_ASSIGNMENT_OP
    HasPtr &operator=(const HasPtr &rhs);
#endif

    HasPtr(HasPtr &&rhs) noexcept : ps(rhs.ps), i(rhs.i)
    {
        std::cout << "move constructor used" << std::endl;
        rhs.ps = nullptr;
    }

#ifndef COPY_N_SWAP_ASSIGNMENT_OP
    HasPtr &operator=(HasPtr &&rhs) noexcept ;
#endif

#ifdef COPY_N_SWAP_ASSIGNMENT_OP
    HasPtr &operator=(HasPtr rhs);
#endif

    void swap(HasPtr &rhs);
    bool operator<(const HasPtr &rhs) const ;

    const std::string &get() const { return *ps;}
    void set(const std::string &s) { *ps = s;}
private:
    std::string *ps;
    int i;
};

void swap(HasPtr &, HasPtr &);
void testHasPtrVec(std::vector<HasPtr> &);

#endif //C___HASPTR_H
