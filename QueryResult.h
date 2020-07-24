//
// Created by 周庆 on 2019-08-10.
//

#ifndef C___QUERYRESULT_H
#define C___QUERYRESULT_H

#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>
#include "StrVec.h"

class QueryResult {
friend std::ostream &print(std::ostream &os, const QueryResult &qr);

public:
    typedef StrVec::size_type  line_no_type;
    QueryResult() = default;    // TODO for test only
    QueryResult(const std::string &wd,
                line_no_type t,
                std::shared_ptr<std::set<line_no_type>> lns,
                std::shared_ptr<StrVec> lt) :
                word(wd), total(t), line_numbers(lns), line_text(lt) {}
    std::set<line_no_type>::iterator begin() {return line_numbers->begin();}
    std::set<line_no_type>::iterator end() {return line_numbers->end();}
    std::set<line_no_type>::const_iterator cbegin() {return line_numbers->cbegin();}
    std::set<line_no_type>::const_iterator cend() {return line_numbers->cend();}
    std::shared_ptr<StrVec> get_file() {return line_text;}
private:
    std::string word;
    line_no_type total;
    std::shared_ptr<std::set<line_no_type>> line_numbers;
    std::shared_ptr<StrVec> line_text;
};

std::ostream &print(std::ostream &os, const QueryResult &qr);

#endif //C___QUERYRESULT_H
