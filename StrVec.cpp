//
// Created by 周庆 on 2019/8/30.
//

#include <iostream>
#include <algorithm>
#include "StrVec.h"

std::allocator<std::string> StrVec::alloc;

StrVec::StrVec(std::initializer_list<std::string> il) : StrVec(){
    for (auto const &s : il)
        push_back(s);
}

std::pair<std::string *, std::string *> StrVec::alloc_n_copy(const std::string *b, const std::string *e) {
    auto b2 = alloc.allocate(e - b);
    return {b2, std::uninitialized_copy(b, e, b2)};
}

void StrVec::reallocate() {
    auto new_cap_size = size() ? 2 * size() : 1;
    auto new_first_element = alloc.allocate(new_cap_size);
    auto new_first_free = new_first_element;
    auto old_first_element = first_element;
    for (size_t i = 0; i != size(); i++)
        alloc.construct(new_first_free++, *old_first_element++);
    free();
    first_element = new_first_element;
    first_free = new_first_free;
    cap = first_element + new_cap_size;
}

void StrVec::free() {
    if (first_element)
        std::for_each(first_element, first_free, [](std::string &p){alloc.destroy(&p);});
        //for (auto p = first_free; p != first_element; alloc.destroy(--p)) {}
    alloc.deallocate(first_element, cap - first_element);
}

StrVec::StrVec(const StrVec &rhs) {
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    first_element = data.first;
    first_free = cap = data.second;
}

StrVec::~StrVec() {
    free();
}

StrVec::StrVec(StrVec &&rhs) noexcept : first_element(rhs.first_element), first_free(rhs.first_free), cap(rhs.cap){
    std::cout << "move constructor used " << std::endl;
    rhs.first_element = rhs.first_free = rhs.cap = nullptr;
}

StrVec& StrVec::operator=(StrVec &&rhs) noexcept {
    std::cout << "move assignment operator used" << std::endl;
    if (this != &rhs)
    {
        free();
        first_element = rhs.first_element;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.first_element = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

StrVec& StrVec::operator=(const StrVec &rhs) {
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    first_element = data.first;
    first_free = cap = data.second;
    return *this;
}

StrVec& StrVec::operator=(std::initializer_list<std::string> il) {
    std::cout << "initializer list assignment operator used" << std::endl;
    auto data = alloc_n_copy(il.begin(), il.end());
    free();
    first_element = data.first;
    first_free = cap = data.second;
    return *this;
}

void StrVec::push_back(const std::string &s) {
    chk_n_copy();
    alloc.construct(first_free++, s);
}

void StrVec::pop_back() {
    if (size() > 0)
        alloc.destroy(--first_free);
}

void StrVec::reserve(StrVec::size_type n) {
    if (n > capacity())
    {
        auto new_first_element = alloc.allocate(n);
        auto new_first_free = new_first_element;
        auto old_first_element = first_element;
        for (size_t i = 0; i != size(); i++)
            alloc.construct(new_first_free++, *old_first_element++);
        free();
        first_element = new_first_element;
        first_free = new_first_free;
        cap = first_element + n;
    }
}

void StrVec::resize(StrVec::size_type n, const std::string &s) {
    if (n > size())
    {
        for (int i = n - size(); i != 0; --i)
            push_back(s);
    } else if (n < size())
    {
        for (int i = size() - n; i != 0; --i)
            pop_back();
    }
}

bool operator==(const StrVec &lhs, const StrVec &rhs) {
    return lhs.size() == rhs.size() &&
    std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

bool operator!=(const StrVec &lhs, const StrVec &rhs) {
    return !(lhs == rhs);
}

bool operator<(const StrVec &lhs, const StrVec &rhs) {
    auto lit = lhs.begin(), rit = rhs.begin();
    for (; lit != lhs.end() && rit != rhs.end(); ++lit, ++rit)
        if (*lit < *rit)
            return true;
        else if (*rit < *lit)
            return false;
    return lit == lhs.end() && rit != rhs.end();
}

bool operator>(const StrVec &lhs, const StrVec &rhs) {
    return rhs < lhs;
}

bool operator<=(const StrVec &lhs, const StrVec &rhs) {
    return !(lhs > rhs);
}

bool operator>=(const StrVec &lhs, const StrVec &rhs)  {
    return !(lhs < rhs);
}