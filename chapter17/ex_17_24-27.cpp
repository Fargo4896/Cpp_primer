#include <iostream>
#include <regex>
#include <string>

using namespace std;
/*
string pattern = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})";
string format = "$2.$5.$7";
regex r(pattern);
string s;
*/
string pattern = "(\\d{5})([.- ])?(\\d{4})";
string fmt = "$1-$3";

regex r(pattern);
string s;

int main()
{
    while (getline(cin, s)) {
        smatch result;
        regex_search(s, result, r);
        if (!result.empty())
            cout << result.format(fmt) << endl;
        else
            cout << "No match" << endl;
    }
    return 0;
}