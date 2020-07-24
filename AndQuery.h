//
// Created by 周庆 on 2019/9/26.
//

#ifndef C___ANDQUERY_H
#define C___ANDQUERY_H

class TextQuery;
class QueryResult;

#if DEBUG_LEVEL >= 1
#include <iostream>
#endif

#include <string>
#include "BinaryQuery.h"

class AndQuery : public BinaryQuery {
    friend Query operator&(const Query &, const Query &);

    AndQuery(const Query &l, const Query &r) : BinaryQuery(l, r, "&") {
#if DEBUG_LEVEL >= 1
        std::cout << "AndQuery(const Query &l, const Query &r)" << std::endl;
#endif
    }

    QueryResult eval(const TextQuery &) const override;
};

Query operator&(const Query &, const Query &);

#endif //C___ANDQUERY_H
