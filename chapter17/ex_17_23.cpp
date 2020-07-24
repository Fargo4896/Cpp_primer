#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <string>
using std::string;

#include <regex>
using std::regex;
using std::sregex_iterator;
using std::smatch;

bool valid(const smatch &m)
{
    if ((m[2].matched) && (!m[3].matched))
        return false;
    else
        return true;
}

int main()
{
    string zipcode = "(\\d{5})([-])?(\\d{4})?\\b";
    regex r(zipcode);
    smatch m;
    string s;

    while (getline(cin, s)) {
        // for each matching zipcode number
        for (sregex_iterator it(s.begin(), s.end(), r), end; it != end; it++) {
            // check whether the number's formatting is valid
            if (valid(*it))
                cout << "valid zipcode number: " << it->str() << endl;
            else
                cout << "invalid zipcode number: " << s << endl;
        }
    }
    return 0;
}