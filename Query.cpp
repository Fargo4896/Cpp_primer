//
// Created by 周庆 on 2019/9/26.
//

#include "Query.h"
#include "TextQuery.h"
#include "QueryResult.h"
#include "Query_base.h"
#include "WordQuery.h"

#if DEBUG_LEVEL >= 1
#include <iostream>
#endif

Query::Query(const std::string &s) : pq(new WordQuery(s)) {
#if DEBUG_LEVEL >= 1
    std::cout << "Query::Query(const std::string &)" << std::endl;
#endif
}

QueryResult Query::eval(const TextQuery &t) const {
#if DEBUG_LEVEL >= 1
    std::cout << "Query::eval" << std::endl;
#endif
    return pq->eval(t);
}

std::string Query::rep() const {
#if DEBUG_LEVEL >= 1
    std::cout << "Query::rep" << std::endl;
#endif
    return pq->rep();
}