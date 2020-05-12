#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H
#include <iostream>
class HugeInteger{
    static const int MaxRead = 20010;
    static const int MaxLength = 27000;
    static const int MaxSize_ = 30000;
    static const int Base = 10;
    int* digit_;
    bool is_negative;
    int size_;
public:
    int* getDigit();
    ~HugeInteger();
    int getSize();
    template <typename IntegerType = int>
    HugeInteger(IntegerType digit = 0);

    explicit HugeInteger(const char* other);
    HugeInteger(const HugeInteger& other);
    const HugeInteger& operator= (const HugeInteger& rhs);
    friend bool operator>(const HugeInteger& lhs, const HugeInteger& rhs);
    friend bool operator<=(const HugeInteger& lhs, const HugeInteger& rhs);
    friend bool operator==(const HugeInteger& lhs, const HugeInteger& rhs);
    friend bool operator!=(const HugeInteger& lhs, const HugeInteger& rhs);
    friend bool operator>=(const HugeInteger& lhs, const HugeInteger& rhs);
    friend bool operator<(const HugeInteger& lhs, const HugeInteger& rhs);
    friend HugeInteger abs(const HugeInteger& digit);
    friend HugeInteger operator-(const HugeInteger& digit);
    friend const HugeInteger operator+(const HugeInteger& lhs, const HugeInteger& rhs);
    template <typename IntegerType>
    friend HugeInteger operator+(const HugeInteger& lhs, const IntegerType& rhs);

    template <typename IntegerType>
    friend HugeInteger operator+(const IntegerType& lhs, const HugeInteger& rhs);

    friend HugeInteger operator-(const HugeInteger& lhs, const HugeInteger& rhs);
    template <typename IntegerType>
    friend HugeInteger operator-(const HugeInteger& lhs, const IntegerType& rhs);

    template <typename IntegerType>
    friend HugeInteger operator-(const IntegerType lhs, const HugeInteger& rhs);

    HugeInteger& operator+=(const HugeInteger& value);
    HugeInteger& operator-=(const HugeInteger& value);
    HugeInteger& operator++();
    HugeInteger& operator--();
    friend HugeInteger operator*(const HugeInteger& lhs, const HugeInteger& rhs);
    template <typename IntegerType>
    friend HugeInteger operator*(const HugeInteger& digit, const IntegerType& coefficient);

    template <typename IntegerType>
    friend HugeInteger operator*(const IntegerType& coefficient, const HugeInteger& digit);

    HugeInteger& operator*=(const HugeInteger& rhs);
    friend int ElementaryDivision(const HugeInteger& lhs, const HugeInteger& rhs);
    friend HugeInteger operator/(const HugeInteger& lhs, const HugeInteger& rhs);
    friend HugeInteger operator%(const HugeInteger& lhs, const HugeInteger& rhs);
    friend std::ostream& operator<<(std::ostream& out, const HugeInteger& digit);
    friend std::istream& operator>>(std::istream& in, HugeInteger& digit);
};
#include "HugeInteger_impl.hpp"
#endif // HUGEINTEGER_H
