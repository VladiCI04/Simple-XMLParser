#pragma once
#include <iostream>

namespace StringHelperFunctions {
    size_t getNextPowerOfTwo(size_t n);
}

class String {
private:
    char* data = nullptr;
    size_t length = 0;
    size_t capacity = 15;

    void resize(size_t lengthToFit);

    explicit String(size_t capacity);

public:
    String();
    String(const char* str);
    String(const String& other);
    String(String&& other) noexcept;
    String& operator=(const String& other);
    String& operator=(String&& other) noexcept;
    ~String();

    size_t getLength() const;
    size_t getCapacity() const;
    const char* c_str() const;
    int find(const char ch, const int curLengt) const;
    int find(const int startIndex, const char ch, const int curLength) const;
    char* const substr(const int startIndex, const int endIndex) const;
    char* const substr2(const int startIndex, const int endIndex) const;

    String& operator+=(const String& other);
    String& operator+=(char ch);

    char& operator[](size_t index);
    char operator[](size_t index) const;

    // this is not in the standard
    operator bool() const;

    friend String operator+(const String& lhs, const String& rhs);
    friend std::istream& operator>>(std::istream& is, String& str);

private:
    void copyFrom(const String& other);
    void moveFrom(String&& other) noexcept;
    void free();
};

std::ostream& operator<<(std::ostream& os, const String& str);

bool operator<(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);
bool operator>=(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);