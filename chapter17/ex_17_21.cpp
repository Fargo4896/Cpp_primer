#include <iostream>
using std::cerr;
using std::cout;
using std::cin;
using std::endl;
using std::istream;
using std::ostream;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <sstream>
using std::istringstream;
using std::ostringstream;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <regex>
using std::regex;
using std::sregex_iterator;
using std::smatch;

struct PersonInfo {
    string name;
    vector<string> phones;
};

bool valid(const smatch& m)
{
    if (m[1].matched)
        return m[3].matched && (m[4].matched == 0 || m[4].str() == " ");
    else
        return !m[3].matched && m[4].str() == m[6].str();
}

bool read_record(istream &is, vector<PersonInfo> &people)
{
    if (is) {
        string line, word;

        while (getline(is, line)) {
            PersonInfo info;
            istringstream record(line);
            record >> info.name;
            while (record >> word)
                info.phones.push_back(word);
            people.push_back(info);
        }
        return true;
    }
    else
        return false;
}

void format_record(ostream &os, const vector<PersonInfo> &people)
{
    string phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})";
    regex r(phone);
    smatch m;

    for (const auto &entry: people) {
        // for each entry in people
        ostringstream formatted, badNums; 
        for (const auto &nums: entry.phones) {
            for (sregex_iterator it(nums.begin(), nums.end(), r), end; it != end; it++) {
                // for each number, check whether the number's formatting is valid
                if (!valid(*it))
                    badNums << " " << nums;
                else
                    formatted << " " << nums;
            }
        }

        if (badNums.str().empty()) // there were no bad numbers
            os << entry.name << " " // print the name
            << formatted.str() << endl; // and reformatted numbers;
        else // otherwise, print the name and bad numbers
            cerr << "input error: " << entry.name
            << " invalid numbers" << badNums.str() << endl;
    }    
}

int main()
{
    vector<PersonInfo> people;

    string filename;
    cout << "Please input a record file name: ";
    cin >> filename;
    cout << endl;
    ifstream fin(filename);

    if (read_record(fin, people)) {
        ofstream fout("data\\result.txt", ofstream::trunc);
        format_record(fout, people);
    }
    else
        cout << "Fail to open file" << filename << endl;
    
    return 0;
}