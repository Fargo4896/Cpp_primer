#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <regex>
using std::regex;
using std::regex_error;
using std::sregex_iterator;
using std::smatch;

bool valid(const smatch &m)
{
    if (m[1].matched)
        return m[3].matched && (m[4].matched == 0 || m[4].str() == " ");
    else
        return !m[3].matched && m[4].str() == m[6].str();
    
}

int main()
{   /*
    // for ex_17_14 error_brack
    try
    {
        regex r("[[:alnum:]+\\.(cpp|cxx|cc)$", regex::icase);
    }
    catch(regex_error e)
    {
        cout << e.what() << "\ncode: " << e.code() << endl;
    }

    // for ex_17_15
    regex r("[[:alpha:]]*[^c]ei[[:alpha:]]*", regex::icase);
    string s;
    cout << "Please input a world. Input 'q' to quit" << endl;
    while (cin >> s && s != "q") {
        if (std::regex_match(s, r))
            cout << "Input word" << s << "is okay." << endl;
        else
            cout << "Input word" << s << "is not okay." << endl;  
    }

   // for ex_17_16
   regex r("[^c]ei", regex::icase);
   string s;
   cout << "Please input a word! Input 'q' to quit!" << endl;
    while(cin >> s && s != "q")
    {
        if(std::regex_match(s, r))
            cout << "Input word " << s << " is okay!" << endl;
        else
            cout << "Input word " << s << " is not okay!" <<endl;
    }
    
    // for ex_17_17
    string s;
    cout << "Please input a sequence of words:" << endl;
    getline(cin, s);
    cout << endl;
    cout << "Word(s) that violiate the \"ei\" grammar rule:" << endl;
    string pattern("[^c]ei");
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    regex r(pattern, regex::icase);
    for (sregex_iterator it(s.begin(), s.end(), r), end; it != end; it++)
        cout << it->str() << endl;
    */
    // for ex_17_19
    string phonenumber = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})";
    regex r(phonenumber);
    string s;
    bool valid_record;
    while(getline(cin, s)) {
        valid_record = false;
        for(sregex_iterator it(s.begin(), s.end(), r), end; it != end; it++) {
            valid_record = true;
            if (valid(*it))
                cout << "Valid phone number" << it->str() << endl;
            else
                cout << "InValid phone number" << it->str() << endl;
        }
        if (!valid_record)
            cout << "Invalid record" << endl;
    }
    return 0;
}