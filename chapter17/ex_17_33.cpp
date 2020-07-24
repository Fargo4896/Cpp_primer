#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <utility>

int main()
{
    typedef std::pair<std::string, std::string> ps;
    std::ifstream i("d.txt");
    std::vector<ps> dict;
    std::string str1, str2;
    // read words from dictionary
    while (i >> str1 >> str2)
        dict.emplace_back(str1, str2);
    i.close();
    // sort words in vector
    std::sort(dict.begin(), dict.end(), [](const ps &_ps1, const ps &_ps2) {return _ps1.first < _ps2.first;});
    i.open("i.txt");
    std::default_random_engine e(static_cast<unsigned int>(std::time(nullptr)));
    // read word in dictionary
    while (i >> str1) {
        // find word in dictionary
        std::vector<ps>::const_iterator it = std::find_if(dict.cbegin(), dict.cend(), [&str1](const ps &_ps) {return _ps.first == str1; });
        // if word doesn't exist in dictionary
        if (it == dict.cend())
            // write it itself
            std::cout << str1 << ' ';
        else {
            // get random meaning of word
            std::uniform_int_distribution<unsigned int> u(0, 
            std::find_if(dict.cbegin(), dict.cend(), [&str1](const ps &_ps) {return _ps.first == str1; }) - it - 1);
            // write random meaning
            std::cout << (it + u(e))->second << ' '; 
        }
    }
    return 0;
}