#include "String.h"
#include <cstring>
#pragma warning(disable:4996)

namespace StringHelperFunctions {
    size_t getNextPowerOfTwo(size_t n) {
        size_t step = 1;

        while ((n >> step) > 0) {
            n |= n >> step;
            step *= 2;
        }

        return n + 1;
    }
}

using namespace StringHelperFunctions;

void String::copyFrom(const String& other) {
    length = other.length;
    capacity = other.capacity;
    data = new char[capacity + 1];
    strcpy(data, other.data);
}

void String::moveFrom(String&& other) noexcept {
    data = other.data;
    length = other.length;
    capacity = other.capacity;

    other.data = nullptr;
    other.length = 0;
    other.capacity = 0;
}

void String::free() {
    delete[] data;
    data = nullptr;
    length = capacity = 0;
}

void String::resize(size_t lengthToFit) {
    capacity = length < 16 ? 15 : getNextPowerOfTwo(lengthToFit + 1) - 1;

    char* newData = new char[capacity + 1];
    strcpy(newData, data);
    delete[] data;

    data = newData;
}

String::String(size_t capacity) : capacity(capacity) {
    data = new char[capacity + 1];
}

String::String() : String("") { }

String::String(const char* str) {
    if (!str) {
        data = new char[capacity + 1];
        data[0] = '\0';
    }
    else {
        length = strlen(str);
        capacity = std::max((int)getNextPowerOfTwo(length), 16) - 1;
        data = new char[capacity + 1];
        strcpy(data, str);
    }
}

String::String(const String& other) {
    copyFrom(other);
}

String::String(String&& other) noexcept {
    moveFrom(std::move(other));
}

String& String::operator=(const String& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

String& String::operator=(String&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }

    return *this;
}

String::~String() {
    free();
}

size_t String::getLength() const {
    return length;
}

size_t String::getCapacity() const {
    return capacity;
}

const char* String::c_str() const {
    return data;
}

int String::find(const char ch, const int curLength) const {
    for (int index = 0; index < curLength; index++) {
        if (data[index] == ch) {
            return index;
        }
    }

    return -1;
}

int String::find(const int startIndex, const char ch, const int curLength) const {
    for (int index = startIndex; index < curLength; index++) {
        if (data[index] == ch) {
            return index;
        }
    }

    return -1;
}

char* const String::substr(const int startIndex, const int endIndex) const {
    if (startIndex == 0 || endIndex < startIndex) {
        return nullptr;
    }

    char* curSubstr = new char[endIndex - startIndex + 1];
    for (int curIndex = startIndex; curIndex < endIndex; curIndex++) {
        curSubstr[curIndex - startIndex] = data[curIndex];
    }
    curSubstr[endIndex - startIndex] = '\0';

    return curSubstr;
}

char* const String::substr2(const int startIndex, const int endIndex) const {
    if (startIndex == -1 || endIndex < startIndex) {
        return nullptr;
    }

    char* curSubstr = new char[endIndex - startIndex + 1];
    for (int curIndex = startIndex; curIndex < endIndex; curIndex++) {
        curSubstr[curIndex - startIndex] = data[curIndex];
    }
    curSubstr[endIndex - startIndex] = '\0';

    return curSubstr;
}

String& String::operator+=(const String& other) {
    length += other.length;
    if (length >= capacity) {
        // resize with the new length
        resize(length);
    }

    //use strncat instead of strcat, because strcat will not work for str += str (the term zero of str will be destroyed by the first char)
    std::strncat(data, other.data, other.length);
    return *this;
}

String& String::operator+=(char ch) {
    if (length == capacity) {
        resize(length + 1);
    }
    data[length++] = ch;
    return *this;
}

char& String::operator[](size_t index) {
    return data[index];
}

char String::operator[](size_t index) const {
    return data[index];
}

String::operator bool() const {
    return length == 0;
}

String operator+(const String& lhs, const String& rhs) {
    size_t resultLength = lhs.length + rhs.length;
    size_t capacity = getNextPowerOfTwo(resultLength) - 1;

    String res(capacity);
    strcpy(res.data, lhs.data);
    strcat(res.data, rhs.data);
    res.length = resultLength;

    return res;
}

std::istream& operator>>(std::istream& is, String& str) {
    char buff[1024];
    is >> buff;

    delete[] str.data;
    str.length = strlen(buff);
    str.capacity = std::max((int)getNextPowerOfTwo(str.length), 16) - 1;
    str.data = new char[str.capacity + 1];
    strcpy(str.data, buff);

    return is;
}

std::ostream& operator<<(std::ostream& os, const String& str) {
    return os << str.c_str();
}

bool operator<(const String& lhs, const String& rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}
bool operator<=(const String& lhs, const String& rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}
bool operator>=(const String& lhs, const String& rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}
bool operator>(const String& lhs, const String& rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}
bool operator==(const String& lhs, const String& rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}
bool operator!=(const String& lhs, const String& rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) != 0;
}