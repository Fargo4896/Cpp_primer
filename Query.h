//
// Created by 周庆 on 2019/9/26.
//

#ifndef C___QUERY_H
#define C___QUERY_H

class TextQuery;
class QueryResult;
class Query_base;

#include <memory>
#include <string>
#include <iostream>

class Query {
    friend Query operator~(const Query &);
    friend Query operator&(const Query &, const Query &);
    friend Query operator|(const Query &, const Query &);

public:
    Query(const std::string &);

    QueryResult eval(const TextQuery &) const ;
    std::string rep() const ;

private:
    Query(std::shared_ptr<Query_base> query) : pq(query) {
#if DEBUG_LEVEL >= 1
        std::ocut << "Query::Query(std::shared_ptr<Query_base> query)" << std::endl;
#endif
    }

    std::shared_ptr<Query_base> pq;
};

inline std::ostream &operator<<(std::ostream &os, const Query &q) {
    return os << q.rep();
}

#endif //C___QUERY_H
