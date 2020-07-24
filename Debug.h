//
// Created by 周庆 on 2019-05-26.
//

#ifndef C___DEBUG_H
#define C___DEBUG_H

#include <iostream>

class Debug {
public:
    constexpr Debug(bool b = true) : hw(b), io(b), other(b) {}
    constexpr Debug(bool h, bool i, bool o)
            : hw(h), io(i), other(o) {}

    constexpr bool any() const { return hw || io || other; }  // Add const (since C++14)
    void set_hw(bool b) { hw = b; }
    void set_io(bool b) { io = b; }
    void set_other(bool b) { other = b; }

private:
    bool hw;
    bool io;
    bool other;
};

#endif //C___DEBUG_H
