#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include "HugeInteger.hpp"
class BigIntegerOverflow{};

int* HugeInteger::getDigit(){
    return digit_;
}
HugeInteger::~HugeInteger(){
    delete[] digit_;
    size_ = 0;
}
int HugeInteger::getSize(){
    return size_;
}
template <typename IntegerType>
HugeInteger::HugeInteger(IntegerType digit){
    IntegerType other_ = digit;
    if(other_ == 0){
        is_negative = false;
        digit_ = new int[MaxSize_];
        size_ = 1;
        for (int i = 0; i < MaxSize_; ++i)
            digit_[i] = 0;
    }else {
        if(other_ > 0)
            is_negative = false;
        else{
            is_negative = true;
            other_ *= -1;
        }
        size_ = 0;
        digit_ = new int[MaxSize_];
        for(int i = 0; i < MaxSize_; ++i)
            digit_[i] = 0;
        while(other_){
            digit_[size_] = other_ % Base;
            size_ += 1;
            other_ /= Base;
        }
    }
}
HugeInteger::HugeInteger(const char* other){
    if(other[0] == '-'){
        if(strlen(other) - 1 >= static_cast<unsigned int>(MaxRead))
            throw BigIntegerOverflow();
    }else {
        if(strlen(other) >= static_cast<unsigned int>(MaxRead))
            throw BigIntegerOverflow();
    }
    digit_ = new int[MaxSize_];
    for(int i = 0; i < MaxSize_; ++i)
        digit_[i] = 0;
    int end_idx = 0;
    is_negative = false;
    if(other[0] == '-'){
        is_negative = true;
        end_idx = 1;
    }
    if(other[0] != '-'){
        int length = strlen(other) - 1;
        size_ = length + 1;
        for(int i = length; i >= end_idx; --i)
            digit_[length - i] = other[i] - '0';
    }else{
        int length = strlen(other) - end_idx;
        size_ = length;
        for(int i = length; i >= end_idx; --i)
            digit_[length - i] = other[i] - '0';
    }
    int zero_counter = 0;
    for(int i = size_ - 1; i >= 0; --i){
        if(digit_[i] != 0)
            break;
        else
            ++zero_counter;
    }
    if(zero_counter != 0)
        size_ -= zero_counter;
}
HugeInteger::HugeInteger(const HugeInteger& other){
    is_negative = other.is_negative;
    size_ = other.size_;
    digit_ = new int[MaxSize_];
    for(int i = 0; i < MaxSize_; ++i)
        digit_[i] = other.digit_[i];
}
const HugeInteger& HugeInteger::operator= (const HugeInteger& rhs){
    if(&rhs == this)
        return *this;
    delete[] this->digit_;
    this->is_negative = rhs.is_negative;
    this->digit_ = nullptr;
    this->size_ = rhs.size_;
    this->digit_ = new int[MaxSize_];
    for(int i = 0; i < MaxSize_; ++i)
        this->digit_[i] = 0;
    for(int i = 0; i < rhs.size_; ++i)
        this->digit_[i] = rhs.digit_[i];
    return *this;
}
bool operator>(const HugeInteger& lhs, const HugeInteger& rhs){
    if(lhs.is_negative && !rhs.is_negative)
        return false;
    if(!lhs.is_negative && rhs.is_negative)
        return true;
    if(!lhs.is_negative && !rhs.is_negative){
        if(lhs.size_ > rhs.size_)
            return true;
        if(lhs.size_ < rhs.size_)
            return false;
        for(int i = lhs.size_ - 1; i >= 0; --i){
            if(lhs.digit_[i] < rhs.digit_[i])
                return false;
            if(lhs.digit_[i] > rhs.digit_[i])
                return true;
        }
        return false;
    }
    return !(abs(lhs) > abs(rhs) || abs(lhs) == abs(rhs));
}
bool operator<=(const HugeInteger& lhs, const HugeInteger& rhs){
    return !(lhs > rhs);
}
bool operator==(const HugeInteger& lhs, const HugeInteger& rhs){
    return !(lhs > rhs) && !(rhs > lhs);
}
bool operator!=(const HugeInteger& lhs, const HugeInteger& rhs){
    return !(lhs == rhs);
}
bool operator>=(const HugeInteger& lhs, const HugeInteger& rhs){
    return (lhs > rhs || lhs == rhs);
}
bool operator<(const HugeInteger& lhs, const HugeInteger& rhs){
    return !(lhs >= rhs);
}
HugeInteger abs(const HugeInteger& digit){
    HugeInteger result = digit;
    if(result.is_negative)
        result.is_negative = false;
    return result;
}
HugeInteger operator-(const HugeInteger& digit){
    bool check_zero = true;
    for(int i = 0; i < digit.size_; ++i){
        if(digit.digit_[i] != 0){
            check_zero = false;
            break;
        }
    }
    if(check_zero){
        HugeInteger result;
        return result;
    }
    HugeInteger result = digit;
    result.is_negative = !result.is_negative;
    return result;
}
const HugeInteger operator+(const HugeInteger& lhs, const HugeInteger& rhs){
    HugeInteger result;
    if(!lhs.is_negative && !rhs.is_negative){
        result.size_ = std::max(lhs.size_, rhs.size_);
        int add(0);
        for(int i = 0; i < result.size_; ++i){
            int tmp = lhs.digit_[i] + rhs.digit_[i] + add;
            result.digit_[i] = tmp % HugeInteger::Base;
            add = tmp / HugeInteger::Base;
        }
        if(add != 0){
            if(result.size_ + 1 >= HugeInteger::MaxLength){
                throw BigIntegerOverflow();
            }
            result.digit_[result.size_] = add;
            ++result.size_;
        }
        for(int i = HugeInteger::MaxSize_ - 1; i >= 0; --i){
            if(result.digit_[i] != 0){
                result.size_ = i + 1;
                break;
            }
        }
        if (result.size_ >= lhs.MaxLength) {
                throw BigIntegerOverflow();
        }
        return result;
    }
    if(!lhs.is_negative && rhs.is_negative){
        if(lhs >= abs(rhs)){
            return lhs - abs(rhs);
        }
        return -(abs(rhs) - lhs);
    }
    if(lhs.is_negative && !rhs.is_negative){
        if (abs(lhs) <= rhs) {
            return rhs - abs(lhs);
        }
        return -(abs(lhs) - rhs);
    }
    return  -(abs(lhs) + abs(rhs));
}
template <typename IntegerType>
HugeInteger operator+(const HugeInteger& lhs, const IntegerType& rhs){
    HugeInteger result = lhs + HugeInteger(rhs);
    return result;
}
template <typename IntegerType>
HugeInteger operator+(const IntegerType& lhs, const HugeInteger& rhs){
    HugeInteger result = HugeInteger(lhs) + rhs;
    return result;
}
HugeInteger operator-(const HugeInteger& lhs, const HugeInteger& rhs){
    if(!lhs.is_negative && !rhs.is_negative){
        if(lhs == rhs)
            return HugeInteger(0);
        if(lhs < rhs){
            HugeInteger result = rhs - lhs;
            result.is_negative = true;
            return result;
        }
        HugeInteger result;
        result = lhs;
        for(int i = 0; i < lhs.size_; ++i){
            --result.digit_[i + 1];
            result.digit_[i] += HugeInteger::Base;
            result.digit_[i] -= rhs.digit_[i];
            result.digit_[i + 1] += result.digit_[i] / 10;
            result.digit_[i] %= 10;
        }
        for(int i = HugeInteger::MaxLength - 1; i >= 0; --i){
            if (result.digit_[i] != 0){
                result.size_ = i + 1;
                break;
            }
        }
        return result;
    } else if(!lhs.is_negative && rhs.is_negative){
        return lhs + abs(rhs);
    } else if(lhs.is_negative && !rhs.is_negative){
        return -(abs(lhs) + rhs);
    }
    return abs(rhs) - abs(lhs);
}
template <typename IntegerType>
HugeInteger operator-(const HugeInteger& lhs, const IntegerType& rhs){
    HugeInteger result = lhs - HugeInteger(rhs);
    return result;
}
template <typename IntegerType>
HugeInteger operator-(const IntegerType lhs, const HugeInteger& rhs){
    HugeInteger result = HugeInteger(lhs) - rhs;
    return result;
}
HugeInteger&  HugeInteger::operator+=(const HugeInteger& value){
    *this = *this + value;
    return *this;
}
HugeInteger&  HugeInteger::operator-=(const HugeInteger& value){
    *this = *this - value;
    return *this;
}
HugeInteger&  HugeInteger::operator++(){
    *this += HugeInteger(1);
    return *this;
}
HugeInteger&  HugeInteger::operator--(){
    *this -= HugeInteger(1);
    return *this;
}
HugeInteger operator*(const HugeInteger& lhs, const HugeInteger& rhs){
    HugeInteger result;
    if(lhs == result || rhs == result){
        return result;
    }
    const HugeInteger& small_ = (abs(lhs) >= abs(rhs)) ? rhs : lhs;
    const HugeInteger& big_ = (abs(lhs) > abs(rhs)) ? lhs : rhs;
    for(int i = 0; i < small_.size_; ++i){
        int add = 0;
        for(int j = 0; j < big_.size_ || add != 0; ++j){
            int tmp = result.digit_[i + j] + small_.digit_[i] * big_.digit_[j] + add;
            result.digit_[i + j] = tmp % HugeInteger::Base;
            add = tmp / HugeInteger::Base;
        }
    }
    if((rhs.is_negative && !lhs.is_negative) || (lhs.is_negative && !rhs.is_negative)){
        result.is_negative = true;
    }
    for(int i = HugeInteger::MaxSize_ - 1; i >= 0; --i){
        if(result.digit_[i] != 0){
            result.size_ = i + 1;
            break;
        }
    }
    if (result.size_ >= HugeInteger::MaxLength) {
        throw BigIntegerOverflow();
    }
    return result;
}
template <typename IntegerType>
HugeInteger operator*(const HugeInteger& digit, const IntegerType& coefficient){
    if(coefficient == -1){
        return -digit;
    }
    if(coefficient == 1){
        return digit;
    }
    HugeInteger Coefficient(coefficient);
    return Coefficient * digit;
}
template <typename IntegerType>
HugeInteger operator*(const IntegerType& coefficient, const HugeInteger& digit) {
    if (coefficient == -1) {
        return -digit;
    }
    if (coefficient == 1) {
        return digit;
    }
    HugeInteger Coefficient(coefficient);
    return digit * Coefficient;
}
HugeInteger&  HugeInteger::operator*=(const HugeInteger& rhs){
    *this = (*this) * rhs;
    return (*this);
}
int ElementaryDivision(const HugeInteger& lhs, const HugeInteger& rhs){
    int lhs_begin = lhs.digit_[lhs.size_ - 1];
    int rhs_begin = rhs.digit_[rhs.size_ - 1];
    if(lhs_begin < rhs_begin){
        lhs_begin = lhs_begin * HugeInteger::Base + lhs.digit_[lhs.size_ - 2];
    }
    int upper_bound = lhs_begin / rhs_begin;
    int lower_bound = lhs_begin / (rhs_begin + 1);
    int middle = (upper_bound + lower_bound) / 2;
    int result;
    while(true){
        if (abs(lhs) - middle * abs(rhs) >= 0 && abs(lhs) - middle * abs(rhs) < abs(rhs)){
            result = middle;
            break;
        }else if(lhs - middle * rhs < 0){
            upper_bound = middle - 1;
            middle = (upper_bound + lower_bound) / 2;
        }else{
            lower_bound = middle + 1;
            middle = (upper_bound + lower_bound) / 2;
        }
    }
    return result;
}
HugeInteger operator/(const HugeInteger& lhs, const HugeInteger& rhs){
    if(abs(lhs) < abs(rhs)){
        return HugeInteger(0);
    }
    HugeInteger result;
    int lhs_size = lhs.size_;
    int lhs_iterator = lhs_size - 1;
    HugeInteger carry(lhs.digit_[lhs_iterator]);
    while(lhs_iterator >= 1){
        while(carry < rhs){
            --lhs_iterator;
            carry = carry * 10 + lhs.digit_[lhs_iterator];
        }
        int next_digit = ElementaryDivision(carry, rhs);
        int base = HugeInteger::Base;
        result = result * base + next_digit;
        carry = carry - next_digit * rhs;
    }
    if((!lhs.is_negative && !rhs.is_negative) || (lhs.is_negative && rhs.is_negative)){
        result.is_negative = false;
    }else {
        result.is_negative = true;
    }
    return result;
}
HugeInteger operator%(const HugeInteger& lhs, const HugeInteger& rhs){
    HugeInteger result;
    result = lhs - (lhs / rhs) * rhs;
    if(lhs.is_negative){
        result.is_negative = true;
    }else {
        result.is_negative = false;
    }
    return result;
}
std::ostream& operator<<(std::ostream& out, const HugeInteger& digit){
    bool check_zero = true;
    for(int i = 0; i < digit.MaxLength; ++i){
        if (digit.digit_[i] != 0) {
            check_zero = false;
            break;
        }
    }
    if(check_zero){
        out << "0";
        return out;
    } else{
        if(digit.is_negative){
            std::cout << "-";
        }
        for (int i = digit.size_ - 1; i >= 0; --i) {
            out << digit.digit_[i];
        }
        return out;
    }
}
std::istream& operator>>(std::istream& in, HugeInteger& digit){
    char buffer[digit.MaxLength];
    in >> buffer;
    digit = HugeInteger(static_cast<const char*>(buffer));
    return in;
}
