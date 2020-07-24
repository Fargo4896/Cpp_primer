//
// Created by 周庆 on 2019/8/31.
//

#ifndef C___STRING_H
#define C___STRING_H

#include <initializer_list>
#include <memory>
#include <string>

class String {
    friend std::ostream &operator<<(std::ostream &, const String &);
    friend bool operator==(const String &, const String &);
    friend bool operator!=(const String &, const String &);
    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator>=(const String &, const String &);
public:
    typedef size_t size_type;
    typedef char *iterator;
    typedef const char *const_iterator;
    typedef char &reference;
    typedef const char &const_reference;

    String() : first_element(nullptr), first_free(nullptr), cap(nullptr) {}
    String(const_iterator);
    String(std::initializer_list<char>);

    String(const String &);
    ~String();
    String &operator=(const String &);
    String &operator=(const_iterator);
    String(String &&) noexcept ;
    String &operator=(String &&) noexcept ;

    reference operator[](size_type n) {return first_element[n];}
    const_reference operator[](size_type n) const { return first_element[n];}

    void push_back(const_reference);
    void pop_back();

    void reserve(size_type);
    void resize(size_type, const_reference = char());

    bool empty() const {return cbegin() == cend();}
    size_type size() const {return first_free - first_element;}
    size_type capacity() const {return cap - first_element;}

    iterator begin() {return first_element;}
    iterator end() {return first_free;}
    const_iterator begin() const { return first_element;}
    const_iterator end() const {return first_free;}
    const_iterator cbegin() const {return begin();}
    const_iterator cend() const {return end();}

    std::string str() const;

private:
    static std::allocator<char> alloc;
    iterator first_element;
    iterator first_free;
    iterator cap;

    void reallocate(size_t);
    void free();
};

std::ostream &operator<<(std::ostream &, const String &);
bool operator==(const String &, const String &);
bool operator!=(const String &, const String &);
bool operator<(const String &, const String &);
bool operator>(const String &, const String &);
bool operator<=(const String &, const String &);
bool operator>=(const String &, const String &);
#endif //C___STRING_H
