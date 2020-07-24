#include<string>
#include<iostream>
#include<memory>
#include<typeinfo>
#include<cxxabi.h>
std::string demangle(const char *mangled)
{
    int status;
    std::unique_ptr<char [], decltype(std::free) *> result(
        abi::__cxa_demangle(mangled, 0, 0, &status), std::free);
    return result.get() ? std::string(result.get()) : "error occurred";
}

template<class T>
void foo(T&& t) {
    std::cout << "before: " << typeid(t).name() << std::endl;
    std::cout << "after: " << demangle(typeid(t).name()) << std::endl;
}

int main() {
    foo("f");
    foo(std::string());
    return 0;
}