//
// Created by 周庆 on 2020-04-14.
//

#ifndef C___TEXTQUERY_TUPLE_H
#define C___TEXTQUERY_TUPLE_H

#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <memory>
#include <tuple>

class QueryResult;

class TextQuery_tuple {
public:
    typedef std::vector<std::string>::size_type index_Tp;
    typedef std::tuple <std::string, std::shared_ptr<std::set<index_Tp> >, std::shared_ptr<std::vector<std::string> > >  result_tuple;

    // constructor
    TextQuery_tuple(std::ifstream&);

    // query operation return QueryResult
    QueryResult query(const std::string &) const;

    // query operation return tuple
    result_tuple query(const std::string &);

private:
    std::shared_ptr<std::vector<std::string> > file;
    std::map<std::string, std::shared_ptr<std::set<index_Tp> > > wm;
};

#endif //C___TEXTQUERY_TUPLE_H