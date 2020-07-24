//
// Created by 周庆 on 2019/9/26.
//

#ifndef C___NOTQUERY_H
#define C___NOTQUERY_H

class TextQuery;
class QueryResult;

#if DEBUG_LEVEL >= 1
#include <iostream>
#endif

#include <string>
#include <memory>
#include "Query.h"
#include "Query_base.h"

class NotQuery : public Query_base {
    friend Query operator~(const Query &);

    NotQuery(const Query &query) : q(query) {
#if DEBUG_LEVEL >= 1
        std::cout << "NotQuery(const Query &query)" << std::endl;
#endif
    }

    QueryResult eval(const TextQuery &) const override;
    std::string rep() const override {
#if DEBUG_LEVEL >= 1
        std::cout << "NotQuery::rep" << std::endl;
#endif
        return "~(" + q.rep() + ")";
    }

    Query q;
};

Query operator~(const Query &);

#endif //C___NOTQUERY_H
