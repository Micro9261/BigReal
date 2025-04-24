#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <limits>
#include "BigReal.hpp"
#include <cstdlib>

TEST(Arithmetic, addition)
{
    bool good = true;

    std::cout << "Step 1" << std::endl;
    BigReal test3("2147483647");
    BigReal test4("-2147473648");
    if (test3 + test4 != BigReal("9999"))
    {
        std::cout << test3 << " + " << test4 << std::endl;
        std::cout << test3 + test4 << " != " << BigReal("9999") << std::endl;
        good = false;
        std::terminate();
    }
    std::cout << "Step 2" << std::endl;
    for (int i = INT_MIN; i < INT_MAX - 20000; i += 10000)
    {
        BigReal temp = BigReal(i) + BigReal(INT_MAX);
        if (temp != BigReal(static_cast<long long>(i) + static_cast<long long>(INT_MAX)))
        {
            std::cout << BigReal(i) << " + " << BigReal(INT_MAX) << std::endl;
            std::cout << temp << " != " << BigReal(static_cast<long long>(i) + static_cast<long long>(INT_MAX)) << std::endl;
            good = false;
            break;
        }
    }

    std::cout << "Step 3" << std::endl;
    for (int i = INT_MIN; i < INT_MAX - 20000; i += 10000)
    {
        BigReal temp =BigReal(INT_MAX) + BigReal(i);
        if (temp != BigReal(static_cast<long long>(i) + static_cast<long long>(INT_MAX)))
        {
            std::cout << BigReal(INT_MAX) << " + " << BigReal(i) << std::endl;
            std::cout << "(version 2)" << temp << " != " << BigReal(static_cast<long long>(i) + static_cast<long long>(INT_MAX)) << std::endl;
            good = false;
            break;
        }
    }

    std::cout << "Step 4" << std::endl;
    for (int i = INT_MIN; i < INT_MAX - 20000; i += 10000)
    {
        BigReal temp =BigReal("0") + BigReal(i);
        if (temp != BigReal(i))
        {
            std::cout << BigReal("0") << " + " << BigReal(i) << std::endl;
            std::cout << "(version with \'0\')" << temp << " != " << BigReal(i) << std::endl;
            good = false;
            break;
        }
    }

    std::cout << "Step 5" << std::endl;
    for (int i = INT_MIN; i < INT_MAX - 20000; i += 10000)
    {
        BigReal temp =BigReal(INT_MIN) + BigReal(i);
        if (temp != BigReal(static_cast<long long>(i) + static_cast<long long>(INT_MIN)))
        {
            std::cout << BigReal(INT_MIN) << " + " << BigReal(i) << std::endl;
            std::cout << "(version with \'-\')" << temp << " != " << BigReal(static_cast<long long>(i) + static_cast<long long>(INT_MIN)) << std::endl;
            good = false;
            break;
        }
    }

    std::cout << "Step 6" << std::endl;
    for (int i = INT_MIN; i < INT_MAX - 20000; i += 10000)
    {
        BigReal temp =BigReal(1) + BigReal(i);
        if (temp != BigReal(1 + static_cast<long long>(i)))
        {
            std::cout << BigReal(1) << " + " << BigReal(i) << std::endl;
            std::cout << "(version 1 + x)" << temp << " != " << BigReal(1 + static_cast<long long>(i)) << std::endl;
            good = false;
            break;
        }
    }

    std::cout << "Step 7" << std::endl;
    for (int i = INT_MIN; i < INT_MAX - 20000; i += 10000)
    {
        BigReal temp =BigReal(i) + BigReal(1);
        if (temp != BigReal(1 + static_cast<long long>(i)))
        {
            std::cout << BigReal(i) << " + " << BigReal(1) << std::endl;
            std::cout << "(version x + 1)" << temp << " != " << BigReal(1 + static_cast<long long>(i)) << std::endl;
            good = false;
            break;
        }
    }

    std::cout << "Step 8" << std::endl;
    for (int i = INT_MIN; i < INT_MAX - 20000; i += 10000)
    {
        BigReal temp =BigReal(-1) + BigReal(i);
        if (temp != BigReal(-1 + static_cast<long long>(i)))
        {
            std::cout << BigReal(-1) << " + " << BigReal(i) << std::endl;
            std::cout << "(version -1 + x)" << temp << " != " << BigReal(1 + static_cast<long long>(i)) << std::endl;
            good = false;
            break;
        }
    }

    std::cout << "Step 9" << std::endl;
    for (int i = INT_MIN; i < INT_MAX - 20000; i += 10000)
    {
        BigReal temp =BigReal(i) + BigReal(-1);
        if (temp != BigReal(-1 + static_cast<long long>(i)))
        {
            std::cout << BigReal(i) << " + " << BigReal(-1) << std::endl;
            std::cout << "(version x + -1)" << temp << " != " << BigReal(1 + static_cast<long long>(i)) << std::endl;
            good = false;
            break;
        }
    }

    std::cout << "Step 10" << std::endl;
    BigReal test1("5647353676,5656");
    BigReal test2("454542,54");
    if (test1 + test2 != BigReal("5647808219,1056"))
    {
        std::cout << test1 << " + " << test2 << std::endl;
        std::cout << test1 + test2 << " != " << BigReal("5647808219,1056") << std::endl;
        good = false;
    }

    test1 = "454542,54";
    test2 = "5647353676,5656";
    if (test1 + test2 != BigReal("5647808219,1056"))
    {
        std::cout << test1 << " + " << test2 << std::endl;
        std::cout << test1 + test2 << " != " << BigReal("5647808219,1056") << std::endl;
        good = false;
    }

    test1 = "0,12345";
    test2 = "12345";
    if (test1 + test2 != BigReal("12345,12345"))
    {
        std::cout << test1 << " + " << test2 << std::endl;
        std::cout << test1 + test2 << " != " << BigReal("12345,12345") << std::endl;
        good = false;
    }

    test2 = "0,12345";
    test1 = "12345";
    if (test1 + test2 != BigReal("12345,12345"))
    {
        std::cout << test1 << " + " << test2 << std::endl;
        std::cout << test1 + test2 << " != " << BigReal("12345,12345") << std::endl;
        good = false;
    }

    //negative
    test1 = "5647353676,5656";
    test2 = "-454542,54";
    if (test1 + test2 != BigReal("5_646_899_134,0256"))
    {
        std::cout << test1 << " + " << test2 << std::endl;
        std::cout << test1 + test2 << " != " << BigReal("5_646_899_134,0256") << std::endl;
        good = false;
    }

    test1 = "454542,54";
    test2 = "-5647353676,5656";
    if (test1 + test2 != BigReal("-5_646_899_134,0256"))
    {
        std::cout << test1 << " + " << test2 << std::endl;
        std::cout << test1 + test2 << " != " << BigReal("-5_646_899_134,0256") << std::endl;
        good = false;
    }

    test1 = "0,12345";
    test2 = "-12345";
    if (test1 + test2 != BigReal("-12344,87655"))
    {
        std::cout << test1 << " + " << test2 << std::endl;
        std::cout << test1 + test2 << " != " << BigReal("-12344,87655") << std::endl;
        good = false;
    }

    test2 = "-0,12345";
    test1 = "12345";
    if (test1 + test2 != BigReal("12344,87655"))
    {
        std::cout << test1 << " + " << test2 << std::endl;
        std::cout << test1 + test2 << " != " << BigReal("12344,87655") << std::endl;
        good = false;
    }

    
    ASSERT_TRUE(good);
}



TEST(Arithmetic, substraction)
{
    bool good = true;

    std::cout << "Step 1" << std::endl;
    BigReal test3("2147483647");
    BigReal test4("-2147473648");
    if (test3 - test4 != BigReal("4_294_957_295"))
    {
        std::cout << test3 << " - " << test4 << std::endl;
        std::cout << test3 - test4 << " != " << BigReal("4_294_957_295") << std::endl;
        good = false;
        // std::terminate();
    }
    std::cout << "Step 2" << std::endl;
    for (int i = INT_MIN; i < INT_MAX - 20000; i += 10000)
    {
        BigReal temp = BigReal(i) - BigReal(INT_MAX);
        if (temp != BigReal(static_cast<long long>(i) - static_cast<long long>(INT_MAX)))
        {
            std::cout << BigReal(i) << " - " << BigReal(INT_MAX) << std::endl;
            std::cout << temp << " != " << BigReal(static_cast<long long>(i) - static_cast<long long>(INT_MAX)) << std::endl;
            good = false;
            break;
        }
    }

    std::cout << "Step 3" << std::endl;
    for (int i = INT_MIN; i < INT_MAX - 20000; i += 10000)
    {
        BigReal temp =BigReal(INT_MAX) - BigReal(i);
        if (temp != BigReal(static_cast<long long>(INT_MAX) - static_cast<long long>(i)))
        {
            std::cout << BigReal(INT_MAX) << " - " << BigReal(i) << std::endl;
            std::cout << "(version 2)" << temp << " != " << BigReal(static_cast<long long>(INT_MAX) - static_cast<long long>(i)) << std::endl;
            good = false;
            break;
        }
    }

    std::cout << "Step 4" << std::endl;
    for (int i = INT_MIN; i < INT_MAX - 20000; i += 10000)
    {
        BigReal temp =BigReal("0") - BigReal(i);
        if (temp != BigReal( 0 - static_cast<long long>(i)))
        {
            std::cout << BigReal("0") << " - " << BigReal(i) << std::endl;
            std::cout << "(version with \'0\')" << temp << " != " << BigReal(0 - static_cast<long long>(i)) << std::endl;
            good = false;
            break;
        }
    }

    std::cout << "Step 5" << std::endl;
    for (int i = INT_MIN; i < INT_MAX - 20000; i += 10000)
    {
        BigReal temp =BigReal(INT_MIN) - BigReal(i);
        if (temp != BigReal(static_cast<long long>(INT_MIN) - static_cast<long long>(i)))
        {
            std::cout << BigReal(INT_MIN) << " - " << BigReal(i) << std::endl;
            std::cout << "(version with \'-\')" << temp << " != " << BigReal(static_cast<long long>(INT_MIN) - static_cast<long long>(i)) << std::endl;
            good = false;
            break;
        }
    }

    std::cout << "Step 6" << std::endl;
    for (int i = INT_MIN; i < INT_MAX - 20000; i += 10000)
    {
        BigReal temp =BigReal(1) - BigReal(i);
        if (temp != BigReal(1 - static_cast<long long>(i)))
        {
            std::cout << BigReal(1) << " - " << BigReal(i) << std::endl;
            std::cout << "(version 1 + x)" << temp << " != " << BigReal(1 - static_cast<long long>(i)) << std::endl;
            good = false;
            break;
        }
    }

    std::cout << "Step 7" << std::endl;
    for (int i = INT_MIN; i < INT_MAX - 20000; i += 10000)
    {
        BigReal temp =BigReal(i) - BigReal(1);
        if (temp != BigReal(static_cast<long long>(i) - 1))
        {
            std::cout << BigReal(i) << " - " << BigReal(1) << std::endl;
            std::cout << "(version x + 1)" << temp << " != " << BigReal(static_cast<long long>(i) - 1) << std::endl;
            good = false;
            break;
        }
    }

    std::cout << "Step 8" << std::endl;
    for (int i = INT_MIN; i < INT_MAX - 20000; i += 10000)
    {
        BigReal temp =BigReal(-1) - BigReal(i);
        if (temp != BigReal(-1 - static_cast<long long>(i)))
        {
            std::cout << BigReal(-1) << " - " << BigReal(i) << std::endl;
            std::cout << "(version -1 - x)" << temp << " != " << BigReal(-1 - static_cast<long long>(i)) << std::endl;
            good = false;
            break;
        }
    }

    std::cout << "Step 9" << std::endl;
    for (int i = INT_MIN; i < INT_MAX - 20000; i += 10000)
    {
        BigReal temp =BigReal(i) - BigReal(-1);
        if (temp != BigReal(static_cast<long long>(i) - (-1)))
        {
            std::cout << BigReal(i) << " - " << BigReal(-1) << std::endl;
            std::cout << "(version x + -1)" << temp << " != " << BigReal(static_cast<long long>(i) - (-1)) << std::endl;
            good = false;
            break;
        }
    }

    std::cout << "Step 10" << std::endl;
    BigReal test1("5647353676,.5656");
    BigReal test2("454542.54");
    if (test1 - test2 != BigReal("5_646_899_134,0256"))
    {
        std::cout << test1 << " - " << test2 << std::endl;
        std::cout << test1 + test2 << " != " << BigReal("5_646_899_134,0256") << std::endl;
        good = false;
    }

    test1 = "454542,54";
    test2 = "5647353676,5656";
    if (test1 - test2 != BigReal("-5_646_899_134,0256"))
    {
        std::cout << test1 << " + " << test2 << std::endl;
        std::cout << test1 + test2 << " != " << BigReal("-5_646_899_134,0256") << std::endl;
        good = false;
    }

    test1 = "0,12345";
    test2 = "12345";
    if (test1 - test2 != BigReal("-12344,87655"))
    {
        std::cout << test1 << " + " << test2 << std::endl;
        std::cout << test1 + test2 << " != " << BigReal("-12345,12345") << std::endl;
        good = false;
    }

    test2 = "0,12345";
    test1 = "12345";
    if (test1 - test2 != BigReal("12344,87655"))
    {
        std::cout << test1 << " + " << test2 << std::endl;
        std::cout << test1 + test2 << " != " << BigReal("12344,87655") << std::endl;
        good = false;
    }

    //negative
    test1 = "5647353676,5656";
    test2 = "-454542,54";
    if (test1 - test2 != BigReal("5647808219,1056"))
    {
        std::cout << test1 << " + " << test2 << std::endl;
        std::cout << test1 + test2 << " != " << BigReal("5647808219,1056") << std::endl;
        good = false;
    }

    test1 = "454542,54";
    test2 = "-5647353676,5656";
    if (test1 - test2 != BigReal("5647808219,1056"))
    {
        std::cout << test1 << " + " << test2 << std::endl;
        std::cout << test1 + test2 << " != " << BigReal("5647808219,1056") << std::endl;
        good = false;
    }

    test1 = "0,12345";
    test2 = "-12345";
    if (test1 - test2 != BigReal("12345,12345"))
    {
        std::cout << test1 << " + " << test2 << std::endl;
        std::cout << test1 + test2 << " != " << BigReal("12345,12345") << std::endl;
        good = false;
    }

    test2 = "-0,12345";
    test1 = "12345";
    if (test1 - test2 != BigReal("12345,12345"))
    {
        std::cout << test1 << " + " << test2 << std::endl;
        std::cout << test1 + test2 << " != " << BigReal("12345,12345") << std::endl;
        good = false;
    }

    ASSERT_TRUE(good);
}

TEST(Arithmetic, multiplication)
{
    bool good = true;
    
    std::cout << "Step 1" << std::endl;
    for (int i = -10000; i < 10001; i++)
    {
        BigReal temp = BigReal(i) * BigReal(1);
        if (temp != BigReal(i))
        {
            std::cout << BigReal(i) << " * " << BigReal(1) << std::endl;
            std::cout << "Error: " << temp << " != " << BigReal(i) << std::endl;
            good = false;
            break;
        }
    }

    std::cout << "Step 2" << std::endl;
    for (int i = -10000; i < 10001; i++)
    {
        BigReal temp = BigReal(i) * BigReal(0);
        if (temp != BigReal(0))
        {
            std::cout << BigReal(i) << " * " << BigReal(0) << std::endl;
            std::cout << "Error: " << temp << " != " << BigReal(0) << std::endl;
            good = false;
            break;
        }
    }

    std::cout << "Step 3" << std::endl;
    for (int i = INT_MIN; i < INT_MAX - 20000; i += 10000)
    {
        BigReal temp = BigReal(i) * BigReal(i);
        if (temp != BigReal(static_cast<long long>(i) * static_cast<long long>(i)))
        {
            std::cout << BigReal(i) << " * " << BigReal(123.45f) << std::endl;
            std::cout << "Error: " << temp << " != " << BigReal(static_cast<long long>(i) * static_cast<long long>(i)) << std::endl;
            good = false;
            break;
        }
    }
    
    std::cout << "Step 4" << std::endl;
    BigReal test1("12,50");
    BigReal test2("181,35");
    if (test1 * test2 != BigReal("2266,875"))
    {
        std::cout << test1 << " * " << test2 << std::endl;
        std::cout << "Error: " << test1 * test2 << " != " << BigReal("2266,875") << std::endl;
        good = false;
    }

    test1 = "181,35";
    test2 = "12,50";
    if (test1 * test2 != BigReal("2266,875"))
    {
        std::cout << test1 << " * " << test2 << std::endl;
        std::cout << "Error: " << test1 * test2 << " != " << BigReal("2266,875") << std::endl;
        good = false;
    }

    test1 = "-181,35";
    test2 = "12,50";
    if (test1 * test2 != BigReal("-2266,875"))
    {
        std::cout << test1 << " * " << test2 << std::endl;
        std::cout << "Error: " << test1 * test2 << " != " << BigReal("-2266,875") << std::endl;
        good = false;
    }

    test1 = "181,35";
    test2 = "-12,50";
    if (test1 * test2 != BigReal("-2266,875"))
    {
        std::cout << test1 << " * " << test2 << std::endl;
        std::cout << "Error: " << test1 * test2 << " != " << BigReal("-2266,875") << std::endl;
        good = false;
    }
    

    test1 = "-181,35";
    test2 = "-12,50";
    if (test1 * test2 != BigReal("2266,875"))
    {
        std::cout << test1 << " * " << test2 << std::endl;
        std::cout << "Error: " << test1 * test2 << " != " << BigReal("2266,875") << std::endl;
        good = false;
    }

    test1 = "1,8135";
    test2 = "12,50";
    if (test1 * test2 != BigReal("22,66875"))
    {
        std::cout << test1 << " * " << test2 << std::endl;
        std::cout << "Error: " << test1 * test2 << " != " << BigReal("22,66875") << std::endl;
        good = false;
    }

    test1 = "181,35";
    test2 = "0,1250";
    if (test1 * test2 != BigReal("22,66875"))
    {
        std::cout << test1 << " * " << test2 << std::endl;
        std::cout << "Error: " << test1 * test2 << " != " << BigReal("22,66875") << std::endl;
        good = false;
    }

    test2 = "181,35";
    test1 = "0,1250";
    if (test1 * test2 != BigReal("22,66875"))
    {
        std::cout << test1 << " * " << test2 << std::endl;
        std::cout << "Error: " << test1 * test2 << " != " << BigReal("22,66875") << std::endl;
        good = false;
    }

    ASSERT_TRUE(good);
}

TEST(Arithmetic, division)
{
    bool good = true;

    std::cout << "Step 1" << std::endl;
    BigReal test("230023");
    BigReal test0("23");
    if ( (test/test0) != BigReal(10001))
    {
        std::cout << test << " / " << test0 << std::endl;
        std::cout << (test/test0) << " != " << BigReal(10001) << std::endl;
        good = false;
        std::terminate();
    }

    std::cout << "Step 2" << std::endl;
    BigReal test1("1256");
    BigReal test2("12,5");
    if ((test1 / test2) != BigReal("100,48"))
    {
        std::cout << test1 << " / " << test2 << std::endl;
        std::cout << (test1 / test2) << " != " << BigReal("100,48") << std::endl;
        good = false;
        std::terminate();
    }

    ASSERT_TRUE(good);
}