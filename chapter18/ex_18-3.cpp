#include <iostream>
#include <stdexcept>
#include <memory>
#include <vector>
#include <fstream>

class intArray {
public:
    intArray() : p(nullptr) { }
    explicit intArray(std::size_t s) : p(new int[s]) { }

    ~intArray() {
        delete[] p;
    }

private:
    int *p;
};

void exercise(int *b, int *e) 
{
    std::vector<int> v(b, e);
    //int *p = new int[v.size()];
    // approach 1
    // intArray p(v.size());

    // approach 2
    std::shared_ptr<int> p(new int[v.size()], [](int *p) { delete[] p; });
    std::ifstream in("ints");
}

int main()
{
    std::range_error r("error");
    //throw r;
    std::exception *p = &r;
    //throw *p;
    return 0;
}