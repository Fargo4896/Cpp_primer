//
// Created by 周庆 on 2019-08-09.
//

#ifndef C___TEXTQUERY_H
#define C___TEXTQUERY_H

class QueryResult;

#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include "StrVec.h"

class TextQuery {
public:
    typedef std::vector<std::string>::size_type  line_no_type;
    explicit TextQuery(std::ifstream &in);
    QueryResult query(const std::string &word) const;

private:
    std::shared_ptr<StrVec> text;
    std::map<std::string, std::shared_ptr<std::set<line_no_type>>> lines;
};


#endif //C___TEXTQUERY_H
