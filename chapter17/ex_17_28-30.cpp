#include <iostream>
#include <random>
#include <string>

unsigned int random_gen()
{
    static std::default_random_engine e;
    static std::uniform_int_distribution<unsigned int> ud;
    return ud(e);
}

unsigned int random_gen(unsigned int seed)
{
    static std::default_random_engine e(seed);
    static std::uniform_int_distribution<unsigned int> ud;
    return ud(e);
}

unsigned int random_gen(unsigned int seed, unsigned int min, unsigned int max)
{
    static std::default_random_engine e(seed);
    static std::uniform_int_distribution<unsigned int> ud(min, max);
    return ud(e);
}

int main()
{
    std::string temp;
    while (std::cin >> temp)
        std::cout << random_gen(19, 1, 10) << std::endl;
    return 0;
}