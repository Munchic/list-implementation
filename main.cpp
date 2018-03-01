//
//  main.cpp
//  D
//
//  Created by Munchic Fam on 3/19/17.
//  Copyright © 2017 Munchic. All rights reserved.
//

#include <iostream>

struct Base {
 private:
    int* data;
    size_t sz;
    size_t cp;

    friend void pushElem(Base&, int);
    friend void popElem(Base&);

 public:
    Base(): data(nullptr), sz(0), cp(0) {
    }

    Base(int* ptr, size_t _sz, size_t _cp): data(ptr), sz(_sz), cp(_cp) {
    }

    ~Base() {
        delete[] data;
        sz = cp = 0;
    }

    size_t getSz() const {
        return sz;
    }

    size_t getCp() const {
        return cp;
    }

    int& operator[](size_t pos) {
        return *(data + pos);
    }
};

void pushElem(Base& base, int elem) {
    if (base.sz == base.cp) {
        base.cp = (base.cp == 0 ? 1 : base.cp * 2);

        int* newData = new int[base.cp];
        for (int i = 0; i < base.sz; ++i)
            *(newData + i) = *(base.data + i);

        delete[] base.data;
        base.data = newData;
    }

    *(base.data + base.sz++) = elem;
}

void popElem(Base& base) {
    if (base.sz > 0)
        *(base.data + base.sz-- - 1) = 0;
}

class ListIter {
 private:
    int* data;
    size_t sz, pos;

 public:
    ListIter(int* front, int* back, size_t _sz, size_t _pos)
    : data(new int[_sz]), sz(_sz), pos(_pos) {
    }

    int operator*() {
        return data[pos];
    }

    bool operator!=(ListIter other) const {
        return pos != other.pos;
    }

    ListIter& operator++() {
        if (pos < sz - 1)
            ++pos;
        else
            pos = 0;
        return *this;
    }

    ListIter operator++(int) {
        ListIter copyOfThis = *this;
        if (pos < sz - 1)
            ++pos;
        else
            pos = 0;
        return copyOfThis;
    }

    ListIter& operator--() {
        pos = (pos > 0 ? pos - 1 : pos);
        return *this;
    }

    ListIter operator--(int) {
        ListIter copyOfThis = *this;
        pos = (pos > 0 ? pos - 1 : pos);
        return copyOfThis;
    }

    ListIter& operator-(size_t i) {
        pos -= i;
        return *this;
    }
};

class List {
 private:
    Base front, back;

 public:
    List() {
    }

    List(const List& other) {
        *this = other;
    }

    ~List() {
    }

 public:
    void push_front(int elem) {
        pushElem(front, elem);
    }

    void push_back(int elem) {
        pushElem(back, elem);
    }

    void pop_front() {
        popElem(front);
    }

    void pop_back() {
        popElem(back);
    }

    size_t size() const {
        return front.getSz() + back.getSz();
    }

    ListIter begin() {
        int* reversedFront(new int[front.getSz()]);
        for (size_t i = 0; i < front.getSz(); ++i)
            *(reversedFront + i) = front[front.getSz() - i - 1];

        int* copyOfBack(new int[back.getSz()]);
        for (size_t i = 0; i < back.getSz(); ++i)
            *(copyOfBack + i) = back[i];

        return ListIter(reversedFront, copyOfBack, front.getSz() + back.getSz(), 0);
    }

    ListIter end() {
        int* reversedFront(new int[front.getSz()]);
        for (size_t i = 0; i < front.getSz(); ++i)
            *(reversedFront + i) = front[front.getSz() - i - 1];

        int* copyOfBack(new int[back.getSz()]);
        for (size_t i = 0; i < back.getSz(); ++i)
            *(copyOfBack + i) = back[i];

        size_t fullSz = front.getSz() + back.getSz();
        return ListIter(reversedFront, copyOfBack, fullSz, fullSz - 1);
    }
};

int main() {
    List myList;

    for (int i = 0; i < 10; ++i)
        myList.push_back(i);

    for (auto elem : myList)
        std::cout << elem;
}
