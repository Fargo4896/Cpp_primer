//
// Created by 周庆 on 2019/10/12.
//

#ifndef C___DEBUGDELETE_H
#define C___DEBUGDELETE_H

#include <iostream>

class DebugDelete {
public:
    DebugDelete(std::ostream &s = std::cerr) : os(s) { }
    template <typename T>
    void operator() (T* p) const {
        os << "deleting unique_ptr" << std::endl;
        delete p;
    }

private:
    std::ostream &os;
};

#endif //C___DEBUGDELETE_H
