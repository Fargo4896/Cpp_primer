//
// Created by 周庆 on 2020-04-14.
//

#include "TextQuery_tuple.h"
#include "QueryResult.h"
#include <iterator>
#include <algorithm>
#include <sstream>

// Constructor
TextQuery_tuple::TextQuery_tuple(std::ifstream & is) : file(new std::vector<std::string>)
{
    // each line
    std::string line;
    while (std::getline(is, line)) {
        file->push_back(line);
        // current line index
        int index = file->size() - 1;

        // for each word
        std::stringstream lineSteam(line);
        std::string word;
        while (lineSteam >> word) {
            // fetch the smart pointer which is null when the word first time seen
            std::shared_ptr<std::set<index_Tp> > &sp_lineIndex = wm[word];

            // if null, allocate a new set to contain line indices
            if (!sp_lineIndex)
                sp_lineIndex.reset(new std::set<index_Tp>);

            // insert
            sp_lineIndex->insert(index);
        }
    }
}
/*
// do a query operation and return QueryResult object
QueryResult TextQuery_tuple::query(const std::string &sought) const
{
    // dynamicaly allocated set used for the word does not appear
    static std::shared_ptr<std::set<index_Tp> > noData(new std::set<index_Tp>);

    // fetch the iterator to the matching element in the map<word, lines>
    // std::map<std::string, std::shared_ptr<std::set<index_Tp>>>::const_iterator
    auto iter = wm.find(sought);
    if (iter == wm.end())
        return QueryResult(sought, noData, file);
    else
        return QueryResult(sought, iter->second, file);
    
}
*/
// do a query operation and return tuple
TextQuery_tuple::result_tuple TextQuery_tuple::query(const std::string &sought)
{
    // dynamicaly allocated set used for the word does not appear
    static std::shared_ptr<std::set<index_Tp> > noData(new std::set<index_Tp>);

    // fetch the iterator to the matching element in the map<word, lines>.
    auto iter = wm.find(sought);
    if(iter == wm.end())
        return result_tuple(sought, noData, file);
    else
        return result_tuple(sought, iter->second, file);
}