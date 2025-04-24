#include "BigReal.hpp"


//conversions
BigReal::BigReal()
{
    _chars.push_back(0);
    _comma_pos = 1;
    _negative = false;
}

BigReal::BigReal(const std::string & s)
{
    _comma_pos = -1;
    _negative = false;
    
    size_t pos = 0;
    for (char test : s)
    {
        if ('_' == test)
            continue;
        else if ('0' <= test && '9' >= test)
        {
            _chars.push_back(static_cast<int>(test - 0x30));
            pos++;
        }
        else if (',' == test  || '.' == test)
        {
            this->_comma_pos = static_cast<int>(pos);
            if (_chars.empty())
            {
                _chars.push_back(0);
                ++_comma_pos;
            }
        }
        else if ('-' == test && 0 != pos)
            break;
        else if ('-' == test)
            this->_negative = true;
        else
            break;
    }
    
    if (-1 == _comma_pos)
        _comma_pos = static_cast<int>(_chars.size());
    
    this->simplify();
}

BigReal::BigReal(double d)
: BigReal(std::to_string(d)) {}

BigReal::BigReal(float f)
: BigReal(std::to_string(f)) {}

BigReal::BigReal(int i)
: BigReal(std::to_string(i)) {}

BigReal::BigReal(long l)
: BigReal(std::to_string(l)) {}

BigReal::BigReal(long long ll)
: BigReal(std::to_string(ll)) {}

BigReal::BigReal(BigReal && b)
{
    _comma_pos = b._comma_pos;
    _negative = b._negative;
    _chars = std::move(b._chars);
}

BigReal& BigReal::operator=(const char * ptr)
{
    std::string temp(ptr);
    return this->operator=(temp);
}

BigReal& BigReal::operator=(const std::string & s)
{
    this->_negative = false;
    this->_comma_pos = -1;
    std::vector<int> temp;

    size_t pos = 0;
    for (char test : s)
    {
        if ('_' == test)
            continue;
        else if ('0' <= test && '9' >= test)
        {
            temp.push_back(static_cast<int>(test - 0x30));
            pos++;
        }
        else if (',' == test  || '.' == test)
        {
            this->_comma_pos = static_cast<int>(pos);
            if (temp.empty())
            {
                temp.push_back(0);
                ++_comma_pos;
            }
        }
        else if ('-' == test && 0 != pos)
            break;
        else if ('-' == test)
            this->_negative = true;
        else
            break;
    }

    if (-1 == _comma_pos)
        _comma_pos = static_cast<int>(temp.size());
    this->_chars = std::move(temp);

    this->simplify();
    return *this;
}

BigReal& BigReal::operator=(const BigReal & b)
{
    if (this == &b)
        return *this;
    this->_comma_pos = b._comma_pos;
    this->_negative = b._negative;
    this->_chars = b._chars;
    return *this;
}

BigReal& BigReal::operator=(BigReal && b)
{
    if (this == &b)
        return *this;
    this->_comma_pos = b._comma_pos;
    this->_negative = b._negative;
    this->_chars = std::move(b._chars);
    return *this;
}

BigReal::operator std::string() const
{
    std::string result = this->_negative ? "-" : "";
    size_t pos = 0;
    for (int x : _chars)
    {
        if (static_cast<int>(pos) == this->_comma_pos)
            result += ',';
        result += static_cast<char>(x + 0x30);
        ++pos;
    }
    return result;
}


//I/O operations
std::ostream& operator<<(std::ostream & os, const BigReal & b)
{
    os << static_cast<std::string>(b);
    return os;
}

std::istream& operator>>(std::istream & is, BigReal & b)
{
    std::string input;
    is >> input;
    b = input;
    return is;
}

//bool operators
BigReal::operator bool() const
{
    return !(_chars.size() == 1 && 0 == _chars.at(0));
}

bool BigReal::operator==(const BigReal & b) const
{
    bool sign = this->_negative == b._negative;
    bool equal = true;
    if (this->_chars.size() == b._chars.size() && this->_comma_pos == b._comma_pos)
    {
        for (size_t i = 0; i < this->_chars.size(); i++)
        {
            if (this->_chars.at(i) != b._chars.at(i))
            {
                equal = false;
                break;
            }
        }
    }
    else
        equal = false;
    return sign && equal;
}

bool BigReal::operator!=(const BigReal & b) const
{
    return !(*this == b);
}

bool BigReal::operator>(const BigReal & b) const
{
    bool sign = this->_negative == b._negative;
    bool greater = true;
    if (sign)
    {
        if (this->_negative)
        {
            if ( this->_comma_pos == b._comma_pos)
                greater = !this->greater_chars(b);
            else
                greater = this->_comma_pos > b._comma_pos ? false : true;
        }
        else
        {
            if ( this->_comma_pos == b._comma_pos)
                greater = this->greater_chars(b);
            else
                greater = this->_comma_pos > b._comma_pos ? true : false;
        }
    }
    else
        greater = !this->_negative;

    return greater && *this != b;
}

bool BigReal::operator>=(const BigReal & b) const
{
    return (*this > b || *this == b);
}

bool BigReal::operator<(const BigReal & b) const
{
    bool sign = this->_negative == b._negative;
    bool less = true;
    if (sign)
    {
        if (this->_negative)
        {
            if (this->_comma_pos == b._comma_pos)
                less = !this->less_chars(b);
            else
                less = this->_comma_pos < b._comma_pos ? false : true;
        }
        else
        {
            if (this->_comma_pos == b._comma_pos)
                less = this->less_chars(b);
            else
                less = this->_comma_pos < b._comma_pos ? true : false;
        }
    }
    else
        less = this->_negative;
    
    return less && *this != b;
}

bool BigReal::operator<=(const BigReal & b) const
{
    return (*this < b || *this == b);
}

//arithmetic
BigReal BigReal::operator-() const
{
    BigReal temp(*this);
    temp._negative = !temp._negative;
    return temp;
}

BigReal BigReal::operator+(const BigReal & b) const
{
    BigReal result;
    if (this->_negative && !b._negative)
    {
        BigReal temp(*this);
        temp = -temp;
        result = b - temp;
    }
    else if ( !this->_negative && b._negative)
    {
        BigReal temp(b);
        temp = -temp;
        result = *this - temp;
    }
    else //the same signs
    {
        result._negative = this->_negative;
        int add_zeros = static_cast<int>(this->_chars.size() - this->_comma_pos) - static_cast<int>(b._chars.size() - b._comma_pos);
        result._comma_pos = this->_comma_pos > b._comma_pos ? this->_comma_pos : b._comma_pos;
        std::vector<int> val1 = this->_chars;
        std::vector<int> val2 = b._chars;
        while (add_zeros < 0)
        {
            val1.push_back(0);
            add_zeros++;
        }
        while (add_zeros > 0)
        {
            val2.push_back(0);
            add_zeros--;
        }
        std::vector<int> res;
        size_t len = val1.size() > val2.size() ? val1.size() : val2.size();
        int addition = 0;
        for (size_t i = 0; i < len; i++)
        {
            int sum = addition;
            if (i < val1.size())
                sum += *(val1.end() - i - 1);
            if (i < val2.size())
                sum += *(val2.end() - i - 1);
            addition = sum / 10;
            res.push_back(sum % 10);
        }
        if (0 != addition)
        {
            res.push_back(addition);
            ++result._comma_pos;
        }
        std::reverse(res.begin(), res.end());
        result._chars = std::move(res);
    }
    result.simplify();
    return result;
}

BigReal BigReal::operator-(const BigReal & b) const
{
    BigReal result;
    if ( this->_negative && !b._negative)
    {
        BigReal temp(b);
        temp = -temp;
        result = *this + temp;
    }
    else if ( !this->_negative && b._negative)
    {
        BigReal temp(b);
        temp = -temp;
        result = *this + temp;
    }
    else
    {
        std::vector<int> val1;
        std::vector<int> val2;
        int add_zeros = 0;
        bool this_greater = *this > b;
        if (this->_negative)
            this_greater = !this_greater;
        if (this_greater)
        {
            val1 = this->_chars;
            val2 = b._chars;
            result._negative = this->_negative;
            add_zeros = static_cast<int>(this->_chars.size() - this->_comma_pos) - static_cast<int>(b._chars.size() - b._comma_pos);
        }
        else
        {
            val1 = b._chars;
            val2 = this->_chars;
            result._negative = !b._negative;
            add_zeros = static_cast<int>(b._chars.size() - b._comma_pos) - static_cast<int>(this->_chars.size() - this->_comma_pos);
        }
        result._comma_pos = this->_comma_pos > b._comma_pos ? this->_comma_pos : b._comma_pos;

        while (add_zeros < 0)
        {
            val1.push_back(0);
            add_zeros++;
        }
        while (add_zeros > 0)
        {
            val2.push_back(0);
            add_zeros--;
        }

        std::vector<int> res;
        int substraction = 0;
        for (size_t i = 0; i < val1.size(); i++)
        {
            int sum = substraction + *(val1.end() - i - 1);
            if (i < val2.size())
                sum -= *(val2.end() - i - 1);
            if (sum < 0)
            {
                sum += 10;
                substraction = -1;
            }
            else
                substraction = 0;
            res.push_back(sum);
        }

        std::reverse(res.begin(), res.end());
        result._chars = std::move(res);
    }

    result.simplify();
    if (result == BigReal("-0"))
        result._negative = false;
    return result;
}

BigReal BigReal::operator*(const BigReal & b) const
{
    BigReal result;
    if (this->_negative == b._negative)
        result._negative = false;
    else
        result._negative = true;
    //get how may pos after comma
    result._comma_pos = (static_cast<int>(this->_chars.size()) - this->_comma_pos) + (static_cast<int>(b._chars.size()) - b._comma_pos);

    std::vector<int> res;
    for (size_t i = 0; i < this->_chars.size(); i++)
        res.push_back( *(this->_chars.end() -i - 1) * (*(b._chars.end() -1)));

    for (size_t i = 1; i < b._chars.size(); i++)
    {
        for (size_t j = 0; j < this->_chars.size() - 1; j++)
            res.at(j + i) += *(this->_chars.end() - j - 1) * (*(b._chars.end() - i - 1));
        res.push_back( *(this->_chars.end() - this->_chars.size()) * (*(b._chars.end() - i - 1)));
    }
    int addition = 0;
    for (size_t i = 0; i < res.size(); i++)
    {
        res.at(i) += addition;
        addition = res.at(i) / 10;
        res.at(i) %= 10;
    }
    if (0 != addition)
        res.push_back(addition);
    
    result._comma_pos = static_cast<int>(res.size()) - result._comma_pos;
    std::reverse(res.begin(), res.end());
    result._chars = std::move(res);
    result.simplify();

    if (result == BigReal("-0"))
        result._negative = false;
    return result;
}

BigReal BigReal::operator/(const BigReal & b) const
{
    BigReal result;
    if (b == BigReal("0"))
        throw std::logic_error("Division by 0\n");
    if (*this == BigReal("0"))
        result = "0";
    else if (this->_negative == b._negative)
        result._negative = false;
    else 
        result._negative = true;
    //make temp variables
    BigReal dividend = *this;
    BigReal divisor = b;
    //decimal points modifications
    size_t add_zeros = divisor._chars.size() - divisor._comma_pos;
    divisor._comma_pos = static_cast<int>(divisor._chars.size());
    dividend._comma_pos += static_cast<int>(add_zeros);
    //add zeros do dividend if comma after change bigger than numbers stored
    while (dividend._comma_pos > dividend._chars.size())
        dividend._chars.push_back(0);
    //prepare test variable
    BigReal temp;
    temp._chars.clear();
    for (size_t i = 0; i < divisor._chars.size(); i++)
        temp._chars.push_back(dividend._chars.at(i));
    temp._comma_pos = static_cast<int>(temp._chars.size());
    result._comma_pos = dividend._comma_pos - divisor._comma_pos + 1;
    std::vector<int> res;
    size_t precision = 6;
    size_t limit = dividend._chars.size() - divisor._chars.size();
    for (size_t i = divisor._chars.size(); i < limit || precision; i++)
    {
        int count = 0;
        BigReal val = temp - divisor;
        while (val >= BigReal("0"))
        {
            count++;
            temp = val;
            val = temp - divisor;
        }
        res.push_back(count);
        if (temp == BigReal("0") && i >= dividend._chars.size())
        {
            break;
        }
        int to_push;
        if (i < dividend._chars.size())
        to_push = dividend._chars.at(i);
        else
        {
            to_push = 0;
            --precision;
        }
        temp._chars.push_back(to_push);
        ++temp._comma_pos;
        temp.simplify();
    }
    result._chars = std::move(res);
    
    result.simplify();
    return result;
}

//private
void BigReal::simplify(void)
{
    if (_chars.empty())
        return;
    
    while ( 0 == _chars.back() && _chars.size() > _comma_pos)
        _chars.pop_back();
    
    size_t zeros = 0;
    while ( 0 == _chars.at(zeros++) && zeros < _comma_pos);
    zeros--;

    if (0 != zeros)
    {
        _chars.erase(_chars.begin(), _chars.begin() + zeros);
        _comma_pos -= static_cast<int>(zeros);
    }
}

bool BigReal::greater_chars(const BigReal & b) const
{
    bool greater = true;
    for (size_t i = 0; i < this->_chars.size(); i++)
    {
        if (i >= b._chars.size())
            break;
        if ( this->_chars.at(i) == b._chars.at(i))
            continue;
        else if (this->_chars.at(i) < b._chars.at(i))
            greater = false;
        break;
    }
    if (greater && b._chars.size() > this->_chars.size())
        greater = false;
    return  greater;
}

bool BigReal::less_chars(const BigReal & b) const
{
    return !this->greater_chars(b);
}
