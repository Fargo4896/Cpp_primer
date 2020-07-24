//
// Created by 周庆 on 2019/8/31.
//

#include <iostream>
#include "String.h"

std::allocator<char> String::alloc;

String::String(String::const_iterator i) : String(){
    while (i && *i != '\0')
        push_back(*i++);
}

String::String(std::initializer_list<char> il) : String() {
    for (auto const &s : il)
        push_back(s);
}

void String::push_back(const char &c) {
    if (size() == capacity())
        reallocate(empty()? 1 : 2 * size());
    alloc.construct(first_free++, c);
}

void String::pop_back() {
    if (!empty())
        alloc.destroy(--first_free);
}

void String::reserve(String::size_type n) {
    if (n > capacity())
        reallocate(n);
}

void String::resize(String::size_type n, const char &c) {
    if (n > size())
    {
        for (int i = n - size(); i > 0; i--)
            push_back(c);
    } else if (n < size())
    {
        for (int i = size() - n; i > 0; i--)
            pop_back();
    }
}

void String::reallocate(size_t n) {
    auto new_first_element  = alloc.allocate(n);
    auto new_first_free = new_first_element;
    for (auto it = begin(); it != end(); it++)
        alloc.construct(new_first_free++, std::move(*it));
    free();
    first_element = new_first_element;
    first_free = new_first_free;
    cap = first_element + n;
}

void String::free() {
    while (!empty())
        alloc.destroy(--first_free);
    alloc.deallocate(first_element, capacity());
}

String::String(const String &rhs) {
    std::cout << "copy constructor used " << std::endl;
    first_element = alloc.allocate(rhs.size());
    first_free = cap = std::uninitialized_copy(rhs.begin(), rhs.end(),
                                               first_element);
}

String& String::operator=(const String &rhs) {
    std::cout << "copy assignmnet operator used " << std::endl;
    auto new_first_element = alloc.allocate(rhs.size());;
    auto new_first_free = std::uninitialized_copy(rhs.begin(), rhs.end(),
                                                  new_first_element);
    free();
    first_element = new_first_element;
    first_free = cap = new_first_free;
    return *this;
}

String& String::operator=(String::const_iterator rhs) {
    *this = String(rhs);
    return *this;
}

String::~String() {
    free();
}

String::String(String &&rhs) noexcept : first_element(rhs.first_element), first_free(rhs.first_free), cap(rhs.cap){
    std::cout << "move constructor used " << std::endl;
    rhs.first_element = rhs.first_free = rhs.cap = nullptr;
}

String& String::operator=(String &&rhs) noexcept {
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

std::string String::str() const {
    return std::string(cbegin(), cend());
}

std::ostream &operator<<(std::ostream &os, const String &s) {
    os << s.str();
    return os;
}

bool operator==(const String &lhs, const String &rhs) {
    return lhs.size() == rhs.size() &&
           std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

bool operator!=(const String &lhs, const String &rhs) {
    return !(lhs == rhs);
}

bool operator<(const String &lhs, const String &rhs) {
    auto lit = lhs.begin(), rit = rhs.begin();
    for (; lit != lhs.end() && rit != rhs.end(); ++lit, ++rit)
        if (*lit < *rit)
            return true;
        else if (*rit < *lit)
            return false;
    return lit == lhs.end() && rit != rhs.end();
}

bool operator>(const String &lhs, const String &rhs) {
    return rhs < lhs;
}

bool operator<=(const String &lhs, const String &rhs) {
    return !(lhs > rhs);
}

bool operator>=(const String &lhs, const String &rhs) {
    return !(lhs < rhs);
}