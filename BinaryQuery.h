//
// Created by 周庆 on 2019/9/26.
//

#ifndef C___BINARYQUERY_H
#define C___BINARYQUERY_H

#if DEBUG_LEVEL >= 1
#include <iostream>
#endif

#include <string>
#include "Query_base.h"
#include "Query.h"

class BinaryQuery : public Query_base {
protected:
    BinaryQuery(const Query &l, const Query &r, const std::string &o) : lhs(l), rhs(l), op(o) {
#if DEBUG_LEVEL >= 1
        std::cout << "BinaryQuery(const Query &l, const Query &r, const std::string &o)" << std::endl;
#endif
    }

    std::string rep() const override {
#if DEBUG_LEVEL >= 1
        std::cout << "BinaryQuery::rep" << std::endl;
#endif
        return "(" + lhs.rep() + " " + op + " " + rhs.rep() + ")";
    }

    Query lhs, rhs;
    std::string op;
};

#endif //C___BINARYQUERY_H
