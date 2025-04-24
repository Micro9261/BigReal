#include <gtest/gtest.h>
#include <string>
#include "BigReal.hpp"
#include <limits.h>
#include <memory>
#include <float.h>

TEST(Conversion, string_var)
{
    bool good = true;
    BigReal test("-1234,5646");
    if ("-1234,5646" != static_cast<std::string>(test))
    {
        std::cout << "Error: " << "-1234,5646" << " , got: " << test << std::endl;
        good = false;
    }

    BigReal test1("0,0");
    if ("0" != static_cast<std::string>(test1))
    {
        std::cout << "Error: " << "0" << " , got: " << test1 << std::endl;
        good = false;
    }

    BigReal test2("1234,5646");
    if ("1234,5646" != static_cast<std::string>(test2))
    {
        std::cout << "Error: " << "1234,5646" << " , got: " << test2 << std::endl;
        good = false;
    }

    BigReal test3("0,003452");
    if ("0,003452" != static_cast<std::string>(test3))
    {
        std::cout << "Error: " << "0,003452" << " , got: " << test3 << std::endl;
        good = false;
    }

    BigReal temp;
    temp = "-1234,5646";
    if ("-1234,5646" != static_cast<std::string>(temp))
    {
        std::cout << "Error assign: " << "-1234,5646" << std::endl;
        good = false;
    }

    temp = "0,0";
    if ("0" != static_cast<std::string>(temp))
    {
        std::cout << "Error assign: " << "0" << std::endl;
        good = false;
    }

    temp = ",0";
    if ("0" != static_cast<std::string>(temp))
    {
        std::cout << "Error assign: " << ",0" << std::endl;
        good = false;
    }

    temp = "0,";
    if ("0" != static_cast<std::string>(temp))
    {
        std::cout << "Error assign: " << "0," << std::endl;
        good = false;
    }

    temp = "1234,5646";
    if ("1234,5646" != static_cast<std::string>(temp))
    {
        std::cout << "Error assign: " << "1234,5646" << std::endl;
        good = false;
    }

    temp ="0,003452";
    if ("0,003452" != static_cast<std::string>(temp))
    {
        std::cout << "Error assign: " << "0,003452" << std::endl;
        good = false;
    }

    ASSERT_TRUE(good);
}

TEST(Conversion, double_var)
{
    bool good = true;
    double test{-1234.5645};
    if ("-1234,5645" != static_cast<std::string>(BigReal(test)))
    {
        std::cout << "Error:" <<  test << std::endl;
        good = false;
    }
    test = 0.0;
    if ("0" != static_cast<std::string>(BigReal(test)))
    {
        std::cout << "Error:" <<  test << std::endl;
        good = false;
    }
    test = 86749.7846;
    if ("86749,7846" != static_cast<std::string>(BigReal(test)))
    {
        std::cout << "Error:" <<  test << std::endl;
        good = false;
    }
    ASSERT_TRUE(good);
}

TEST(Conversion, float_var)
{
    bool good = true;
    float test{-1234.5645f};
    std::string temp = std::to_string(test);
    for (size_t i = 0; i < temp.size(); i++)
        if ('.' == temp.at(i))
        {
            temp.at(i) = ',';
            break;
        }
    if ( temp != static_cast<std::string>(BigReal(test)))
    {
        std::cout << "Error:" <<  std::to_string(test) << " , got: " << BigReal(test) << std::endl;
        good = false;
    }
    test = 0.0f;
    if ("0" != static_cast<std::string>(BigReal(test)))
    {
        std::cout << "Error:" <<  test << " , got: " << BigReal(test) << std::endl;
        good = false;
    }
    test = 86749.7846f;
    if ("86749,78125" != static_cast<std::string>(BigReal(test)))
    {
        std::cout << "Error:" <<  std::to_string(test) << " , got: " << BigReal(test) << std::endl;
        good = false;
    }
    ASSERT_TRUE(good);
}

TEST(Conversion, int_var)
{
    bool good = true;
    for (int i = INT_MIN; i < INT_MAX - 20000; i += 11111)
        if (std::to_string(i) != static_cast<std::string>(BigReal(i)))
        {
            std::cout << "Error: " << i << std::endl;
            good = false;
            break;
        }
    ASSERT_TRUE(good);
}

TEST(Conversion, long_var)
{
    bool good = true;
    for (long i = LONG_MIN; i < INT_MAX - 20000; i += 11111)
        if (std::to_string(i) != static_cast<std::string>(BigReal(i)))
        {
            std::cout << "Error: " << i << std::endl;
            good = false;
            break;
        }
    ASSERT_TRUE(good);
}

TEST(Conversion, long_long_var)
{
    bool good = true;
    for (long long i = INT_MIN; i < INT_MAX- 200000; i += 11111)
        if (std::to_string(i) != static_cast<std::string>(BigReal(i)))
        {
            std::cout << "Error: " << i << std::endl;
            good = false;
            break;
        }
    ASSERT_TRUE(good);
}

TEST(Conversion, copy_default)
{
    bool good = true;
    BigReal test("123,45");
    BigReal test2(test);
    if ("123,45" != static_cast<std::string>(test2))
    {
        std::cout << "Error: " << "123,45" << std::endl;
        good = false;
    }

    BigReal test3("-123,45");
    BigReal test4(test3);
    if ("-123,45" != static_cast<std::string>(test4))
    {
        std::cout << "Error: " << "-123,45" << std::endl;
        good = false;
    }
    BigReal test5("0,0");
    BigReal test6(test5);
    if ("0" != static_cast<std::string>(test6))
    {
        std::cout << "Error: " << "0,0" << std::endl;
        good = false;
    }

    ASSERT_TRUE(good);
}

TEST(Conversion, move_cot)
{
    bool good = true;
    BigReal test("123,45");
    BigReal test2(std::move(test));
    if ("123,45" != static_cast<std::string>(test2))
    {
        std::cout << "Error: " << "123,45" << std::endl;
        good = false;
    }

    BigReal test3("-123,45");
    BigReal test4(std::move(test3));
    if ("-123,45" != static_cast<std::string>(test4))
    {
        std::cout << "Error: " << "-123,45" << std::endl;
        good = false;
    }
    BigReal test5("0,0");
    BigReal test6(std::move(test5));
    if ("0" != static_cast<std::string>(test6))
    {
        std::cout << "Error: " << "0,0" << std::endl;
        good = false;
    }

    ASSERT_TRUE(good);
}