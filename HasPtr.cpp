//
// Created by 周庆 on 2019/9/2.
//

#include "HasPtr.h"

void HasPtr::swap(HasPtr &rhs) {
    std::cout << "HasPtr::swap(HasPtr &rhs)" << std::endl;
    using std::swap;
    swap(ps, rhs.ps);
    swap(i, rhs.i);
}

void swap(HasPtr &lhs, HasPtr &rhs) {
    std::cout << "swap(HasPtr &lhs, HasPtr &rhs)" << std::endl;
    lhs.swap(rhs);
}

HasPtr::~HasPtr() {
    delete ps;
}

#ifndef COPY_N_SWAP_ASSIGNMENT_OP
HasPtr& HasPtr::operator=(const HasPtr &rhs) {
    std::cout <<"copy assignment operator used" << std::endl;
    auto newps = new std::string(*rhs.ps);
    delete ps;
    ps = newps;
    i = rhs.i;
    return *this;
}

HasPtr& HasPtr::operator=(HasPtr &&rhs) noexcept {
    std::cout << "move assignment operator used" << std::endl;
    if (this != &rhs)
    {
        ps = rhs.ps;
        i  = rhs.i;
        rhs.ps = nullptr;
    }
    return *this;
}

#endif

#ifdef COPY_N_SWAP_ASSIGNMENT_OP
HasPtr& HasPtr::operator=(HasPtr rhs) {
    ::swap(*this, rhs);
    return *this;
}

#endif

bool HasPtr::operator<(const HasPtr &rhs) const {
    return *ps < *rhs.ps;
}

void testHasPtrVec(std::vector<HasPtr> &v)
{
    std::cout << "\nBefore sort " << v.size() << " elements:\n";
    for (const auto &e: v)
        std::cout << e.get() << std::endl;
    std::cout << "\n sorting \n";
    std::sort(v.begin(), v.end());
    std::cout << "\nAfter sort \n";
    for (const auto &e: v)
        std::cout << e.get() << std::endl;
}
