#include <gtest/gtest.h>
#include "BigReal.hpp"
#include <string>
#include <iostream>


TEST(bool_oper, bool_conv)
{
    bool good = true;
    BigReal test(12);
    if (!static_cast<bool>(test))
    {
        std::cout << "Error: " << "12 == true, got " << static_cast<bool>(test) << std::endl;
        good = false;
    }

    test = "-12";
    if (!static_cast<bool>(test))
    {
        std::cout << "Error: " << "-12 == true, got " << static_cast<bool>(test) << std::endl;
        good = false;
    }

    test = "0";
    if (static_cast<bool>(test))
    {
        std::cout << "Error: " << "0 == false, got " << static_cast<bool>(test) << std::endl;
        good = false;
    }

    BigReal test2("0");
    if (static_cast<bool>(test2))
    {
        std::cout << "Error: " << "0 (cot) == false, got " << static_cast<bool>(test2) << std::endl;
        good = false;
    }

    test2 = ",0";
    if (static_cast<bool>(test2))
    {
        std::cout << "Error: " << ",0  == false, got " << static_cast<bool>(test2) << std::endl;
        good = false;
    }

    test2 = "0,";
    if (static_cast<bool>(test2))
    {
        std::cout << "Error: " << ",0  == false, got " << static_cast<bool>(test2) << std::endl;
        good = false;
    }
    ASSERT_TRUE(good);
}

TEST(bool_oper, not_equal)
{
    bool good = true;
    BigReal test1("123,45");
    BigReal test2("123,45");

    if (test1 != test2)
    {
        std::cout << test1 << " != " << test2 << std::endl;
        good = false;
    }

    test1 = "00133,45000";
    test2 = "133,45";
    if (test1 != test2)
    {
        std::cout << test1 << " != " << test2 << std::endl;
        good = false;
    }

    test1 = "45,67000";
    test2 = "000045,67";
    if (test1 != test2)
    {
        std::cout << test1 << " != " << test2 << std::endl;
        good = false;
    }

    test1 = "-123,400000";
    test2 = "-123,400";
    if (test1 != test2)
    {
        std::cout << test1 << " != " << test2 << std::endl;
        good = false;
    }

    test1 = "-000678,8000";
    test2 = "-678,8";
    if (test1 != test2)
    {
        std::cout << test1 << " != " << test2 << std::endl;
        good = false;
    }

    test1 = "0";
    test2 = "0,";
    if (test1 != test2)
    {
        std::cout << test1 << " != " << test2 << std::endl;
        good = false;
    }

    test1 = ",0";
    test2 = "0,";
    if (test1 != test2)
    {
        std::cout << test1 << " != " << test2 << std::endl;
        good = false;
    }

    ASSERT_TRUE(good);
}

TEST(bool_oper, equal)
{
    bool good = true;
    BigReal test1("123,45");
    BigReal test2("12334,45");

    if (test1 == test2)
    {
        std::cout << test1 << "== " << test2 << std::endl;
        good = false;
    }

    test1 = "00133,45000";
    test2 = "1330,45";
    if (test1 == test2)
    {
        std::cout << test1 << " == " << test2 << std::endl;
        good = false;
    }

    test1 = "45,67000";
    test2 = "0000405,67";
    if (test1 == test2)
    {
        std::cout << test1 << " == " << test2 << std::endl;
        good = false;
    }

    test1 = "-1023,400000";
    test2 = "-123,400";
    if (test1 == test2)
    {
        std::cout << test1 << " == " << test2 << std::endl;
        good = false;
    }

    test1 = "-0006708,8000";
    test2 = "-678,8";
    if (test1 == test2)
    {
        std::cout << test1 << " == " << test2 << std::endl;
        good = false;
    }
    
    ASSERT_TRUE(good);
}

TEST(bool_oper, lower_equal)
{
    bool good = true;
    BigReal test1("1234,45");
    BigReal test2("123,45");

    if (test1 <= test2)
    {
        std::cout << test1 << " <= " << test2 << std::endl;
        good = false;
    }

    test1 = "00133,457000";
    test2 = "133,45";
    if (test1 <= test2)
    {
        std::cout << test1 << " <= " << test2 << std::endl;
        good = false;
    }

    test1 = "145,67000";
    test2 = "000045,67";
    if (test1 <= test2)
    {
        std::cout << test1 << " <= " << test2 << std::endl;
        good = false;
    }

    test1 = "-122,400000";
    test2 = "-123,400";
    if (test1 <= test2)
    {
        std::cout << test1 << " <= " << test2 << std::endl;
        good = false;
    }

    test1 = "-000658,8000";
    test2 = "-678,8";
    if (test1 <= test2)
    {
        std::cout << test1 << " <= " << test2 << std::endl;
        good = false;
    }

    test1 = "000658,8000";
    test2 = "0";
    if (test1 <= test2)
    {
        std::cout << test1 << " <= " << test2 << std::endl;
        good = false;
    }

    
    ASSERT_TRUE(good);
}

TEST(bool_oper, greater_equal)
{
    bool good = true;
    BigReal test1("1234,45");
    BigReal test2("123,45");

    if (test2 >= test1)
    {
        std::cout << test1 << " <= " << test2 << std::endl;
        good = false;
    }

    test1 = "00133,457000";
    test2 = "133,45";
    if (test2 >= test1)
    {
        std::cout << test1 << " <= " << test2 << std::endl;
        good = false;
    }

    test1 = "145,67000";
    test2 = "000045,67";
    if (test2 >= test1)
    {
        std::cout << test1 << " <= " << test2 << std::endl;
        good = false;
    }

    test1 = "-122,400000";
    test2 = "-123,400";
    if (test2 >= test1)
    {
        std::cout << test1 << " <= " << test2 << std::endl;
        good = false;
    }

    test1 = "-000658,8000";
    test2 = "-678,8";
    if (test2 >= test1)
    {
        std::cout << test1 << " <= " << test2 << std::endl;
        good = false;
    }

    test1 = "0";
    test2 = "-000658,8000";
    if (test2 >= test1)
    {
        std::cout << test1 << " <= " << test2 << std::endl;
        good = false;
    }
    
    ASSERT_TRUE(good);
}

TEST(bool_oper, lower)
{
    bool good = true;
    BigReal test1("1234,45");
    BigReal test2("123,45");

    if (test1 < test2)
    {
        std::cout << test1 << " < " << test2 << std::endl;
        good = false;
    }

    test1 = "00133,457000";
    test2 = "133,45";
    if (test1 < test2)
    {
        std::cout << test1 << " < " << test2 << std::endl;
        good = false;
    }

    test1 = "145,67000";
    test2 = "000045,67";
    if (test1 < test2)
    {
        std::cout << test1 << " < " << test2 << std::endl;
        good = false;
    }

    test1 = "-122,400000";
    test2 = "-123,400";
    if (test1 < test2)
    {
        std::cout << test1 << " < " << test2 << std::endl;
        good = false;
    }

    test1 = "-000658,8000";
    test2 = "-678,8";
    if (test1 < test2)
    {
        std::cout << test1 << " < " << test2 << std::endl;
        good = false;
    }

    test1 = "000658,8000";
    test2 = "0";
    if (test1 < test2)
    {
        std::cout << test1 << " < " << test2 << std::endl;
        good = false;
    }

    test1 = "00133,45000";
    test2 = "133,45";
    if (test1 < test2)
    {
        std::cout << test1 << " < " << test2 << std::endl;
        good = false;
    }

    test1 = "45,67000";
    test2 = "000045,67";
    if (test1 < test2)
    {
        std::cout << test1 << " < " << test2 << std::endl;
        good = false;
    }

    
    ASSERT_TRUE(good);
}

TEST(bool_oper, greater)
{
    bool good = true;
    BigReal test1("1234,45");
    BigReal test2("123,45");

    if (test2 > test1)
    {
        std::cout << test1 << " < " << test2 << std::endl;
        good = false;
    }

    test1 = "00133,457000";
    test2 = "133,45";
    if (test2 > test1)
    {
        std::cout << test1 << " < " << test2 << std::endl;
        good = false;
    }

    test1 = "145,67000";
    test2 = "000045,67";
    if (test2 > test1)
    {
        std::cout << test1 << " < " << test2 << std::endl;
        good = false;
    }

    test1 = "-122,400000";
    test2 = "-123,400";
    if (test2 > test1)
    {
        std::cout << test1 << " < " << test2 << std::endl;
        good = false;
    }

    test1 = "-000658,8000";
    test2 = "-678,8";
    if (test2 > test1)
    {
        std::cout << test1 << " < " << test2 << std::endl;
        good = false;
    }

    test1 = "000658,8000";
    test2 = "0";
    if (test2 > test1)
    {
        std::cout << test1 << " < " << test2 << std::endl;
        good = false;
    }

    test1 = "00133,45000";
    test2 = "133,45";
    if (test2 > test1)
    {
        std::cout << test1 << " < " << test2 << std::endl;
        good = false;
    }

    test1 = "45,67000";
    test2 = "000045,67";
    if (test2 > test1)
    {
        std::cout << test1 << " < " << test2 << std::endl;
        good = false;
    }

    test1 = "2147483647";
    test2 = "2147473648";
    if (test2 > test1)
    {
        std::cout << test1 << " < " << test2 << std::endl;
        good = false;
    }

    ASSERT_TRUE(good);
}