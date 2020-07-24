//
// Created by 周庆 on 2019/9/26.
//

#include "AndQuery.h"
#include <memory>
#include <algorithm>
#include <iterator>
#include "TextQuery.h"
#include "QueryResult.h"

#if DEBUG_LEVEL >= 1
#include <iostream>
#endif

QueryResult AndQuery::eval(const TextQuery &t) const {
#if DEBUG_LEVEL >= 1
    std::cout << "AndQuery::eval" << std::endl;
#endif
    auto left = lhs.eval(t), right = rhs.eval(t);
    auto ret_lines = std::make_shared<std::set<line_no_type>>();

    std::set_intersection(left.cbegin(), left.cend(), right.cbegin(), right.cend(), std::inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(rep(), ret_lines->size(), ret_lines, left.get_file());
}

Query operator&(const Query &lhs, const Query &rhs) {
#if DEBUG_LEVEL >= 1
    std::cout << "Query operator&(const Query &, const Query &)" << std::endl;
#endif
    return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}