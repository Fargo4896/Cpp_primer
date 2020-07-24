//
// Created by 周庆 on 2019/9/26.
//

#ifndef C___WORDQUERY_H
#define C___WORDQUERY_H

#if DEBUG_LEVEL >= 1
#include <iostream>
#endif

#include <string>
#include "TextQuery.h"
#include "QueryResult.h"
#include "Query_base.h"

class WordQuery : public Query_base {
    friend class Query;

    WordQuery(const std::string &s) : query_word(s) {
#if DEBUG_LEVEL >= 1
        std::cout << "WordQuery(const std::string &s)" << std::endl;
#endif
    }

    QueryResult eval(const TextQuery &t) const override {
#if DEBUG_LEVEL >= 1
        std::cout << "WordQuery::eval" << std::endl;
#endif
        return t.query(query_word);
    }

    std::string rep() const override {
#if DEBUG_LEVEL >= 1
        std::cout << "WordQuery::rep" << std::endl;
#endif
        return query_word;
    }
    std::string query_word;
};

#endif //C___WORDQUERY_H
