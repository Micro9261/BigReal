#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <inttypes.h>
#include <stdexcept>

class BigReal
{
public:
    //conversions
    BigReal();
    BigReal(const std::string &);
    BigReal(double);
    BigReal(float);
    BigReal(int);
    BigReal(long);
    BigReal(long long);
    BigReal(const BigReal &) = default;
    BigReal(BigReal &&);
    BigReal& operator=(const char * );
    BigReal& operator=(const std::string &);
    BigReal& operator=(const BigReal &);
    BigReal& operator=(BigReal &&);
    

    operator std::string() const;
    ~BigReal() = default;
    
    //I/O operations
    friend std::ostream& operator<<(std::ostream &, const BigReal &);
    friend std::istream& operator>>(std::istream &, BigReal &);

    //bool operators
    operator bool() const;
    bool operator==(const BigReal &) const;
    bool operator!=(const BigReal &) const;
    bool operator>(const BigReal &) const;
    bool operator>=(const BigReal &) const;
    bool operator<(const BigReal &) const;
    bool operator<=(const BigReal &) const;

    //arithmetic
    BigReal operator-() const;
    BigReal operator+(const BigReal &) const;
    BigReal operator-(const BigReal &) const;
    BigReal operator*(const BigReal &) const;
    BigReal operator/(const BigReal &) const;

private:
    std::vector<int> _chars;
    bool _negative;
    int _comma_pos;

    void simplify(void);
    bool greater_chars(const BigReal &) const;
    bool less_chars(const BigReal &) const;
};