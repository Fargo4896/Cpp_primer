//
// Created by 周庆 on 2019/9/26.
//

#ifndef C___QUERY_BASE_H
#define C___QUERY_BASE_H

class QueryResult;

#include <string>
#include "TextQuery.h"

class Query_base {
    friend class Query;

protected:
    using line_no_type = TextQuery::line_no_type;
    virtual ~Query_base() = default;

private:
    virtual QueryResult eval(const TextQuery &) const = 0;
    virtual std::string rep() const = 0;
};

#endif //C___QUERY_BASE_H
