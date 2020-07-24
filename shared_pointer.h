//
// Created by 周庆 on 2019/10/12.
//

#ifndef C___SHARED_POINTER_H
#define C___SHARED_POINTER_H

#pragma once

#include <functional>

struct Delete {
    template <typename T>
    auto operator() (T* p) const {
        delete p;
    }
};

template <typename T> class SharedPointer;
template <typename T> void swap(SharedPointer<T> &lhs, SharedPointer<T> &rhs) {
    using std::swap;
    swap(lhs.ptr, rhs.ptr);
    swap(lhs.ret_count, rhs.ret_count);
    swap(lhs.deleter, rhs.deleter);
}

template <typename T>
class SharedPointer {
        friend void ::swap<T>(SharedPointer<T> &lhs, SharedPointer<T> &rhs);
public:
    SharedPointer() : ptr(nullptr), ret_count(new std::size_t(1)), deleter(Delete()) { }

    explicit SharedPointer(T* raw_ptr) : ptr(raw_ptr), ret_count(new std::size_t(1)), deleter(Delete()) { }

    explicit SharedPointer(std::shared_ptr<T> &&sp, std::function<void(T*)> d = Delete()) {
        if (sp.unique())
            *this = SharedPointer(new T(*sp));
        else
            throw std::runtime_error("only unique and rvalue reference can transfer ownership\n");
    }

    SharedPointer(const SharedPointer &other) : ptr(other.ptr), ret_count(other.ret_count), deleter(other.deleter) {
        ++*ret_count;
    }

    SharedPointer(SharedPointer &&other) noexcept : ptr(other.ptr), ret_count(other.ret_count), deleter(std::move(other.deleter)) {
        other.ptr = nullptr;
        other.ret_count = nullptr;
    }

    SharedPointer &operator=(const SharedPointer &rhs) {
        ++*rhs.ret_count;
        decrement_and_destory();
        ptr = rhs.ptr;
        ret_count = rhs.ret_count;
        deleter = rhs.deleter;
        return *this;
    }

    SharedPointer &operator=(SharedPointer &&rhs) noexcept {
        ::swap(*this, rhs);
        rhs.decrement_and_destory();
        return *this;
    }

    operator bool() const {
        return ptr ? true : false;
    }

    T &operator*() const {
        return *ptr;
    }
    T *operator->() const {
        return &*ptr;
    }

    auto use_count() const {
        return *ret_count;
    }

    auto get() const {
        return ptr;
    }

    auto unique() const {
        return 1 == *ret_count;
    }

    auto swap(SharedPointer &rhs) {
        ::swap(*this, rhs);
    }

    auto reset() {
        decrement_and_destory();
    }

    auto reset(T* pointer) {
        if (ptr != pointer) {
            decrement_and_destory();
            ptr = pointer;
            ret_count = new std::size_t(1);
        }
    }

    auto reset(T* pointer, const std::function<void(T*)> &d) {
        reset(pointer);
        deleter = d;
    }

    ~SharedPointer() {
        decrement_and_destory();
    }

private:
    T* ptr;
    std::size_t *ret_count;
    std::function<void(T*)> deleter;

    auto decrement_and_destory() {
        if (ptr && 0 == --*ret_count) {
            delete ret_count;
            deleter(ptr);
        }
        else if (!ptr)
            delete ret_count;
        ret_count = nullptr;
        ptr = nullptr;
    }
};
#endif //C___SHARED_POINTER_H
