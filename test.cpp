#include <iostream>
#include <random>
#include <cassert>
#include <stdexcept>
#include "bigint.hpp"

// random number generator
int64_t random_number_generator()
{
    std::random_device rd;
    std::mt19937_64 mt64(rd());
    std::uniform_int_distribution<int64_t> dis(INT64_MIN, INT64_MAX);
    return dis(mt64);
}
// random string generator
std::string random_string_generator()
{
    std::random_device rd;
    std::mt19937_64 mt64(rd());
    std::uniform_int_distribution<int64_t> dis(INT64_MIN, INT64_MAX);
    return std::to_string(dis(mt64));
}

// constructor test
void constructor_test(int64_t num, std::string str)
{
    // default constructor
    bigint test;
    assert(test == bigint());

    // int64_t constructor
    bigint test1(num);
    assert(test1 == bigint(num));

    // string constructor
    bigint test2(str);
    assert(test2 == bigint(str));

    // invalid string input
    try
    {
        bigint invalid("3092-4893240890238490435239482493024803294892349024");
        assert(false);
    }
    catch (const std::invalid_argument &)
    {
        assert(true);
    }

    try
    {
        bigint empty("");
        assert(false);
    }
    catch (const std::invalid_argument &)
    {
        assert(true);
    }

    std::cout << "All constructor tests passed!" << std::endl;
}

// arithmetic test - addition, subtraction, multiplication
void arithmetic_test()
{
    int64_t num1 = random_number_generator();
    int64_t num2 = random_number_generator();
    int64_t num3 = random_number_generator();

    bigint a(num1);
    bigint b(num2);
    bigint c(num3);

    // addition
    assert(a + b == bigint(num1) + bigint(num2));
    assert(a + c == bigint(num1) + bigint(num3));
    assert(a + b + c == bigint(num1) + bigint(num2) + bigint(num3));

    // subtraction
    assert(a - b == bigint(num1) - bigint(num2));
    assert(a - c == bigint(num1) - bigint(num3));
    assert(a - b - c == bigint(num1) - bigint(num2) - bigint(num3));

    // multiplication
    assert(a * b == bigint(num1) * bigint(num2));
    assert(a * c == bigint(num1) * bigint(num3));
    assert(a * b * c == bigint(num1) * bigint(num2) * bigint(num3));

    std::cout << "All arithmetic tests passed" << std::endl;
}

//increment test - increment and decrement
void increment_test()
{
    int64_t num1 = -546745654365463453;
    int64_t num2 = 345987632984346752;

    bigint a(num1);
    bigint b(num2);

    assert(++a == bigint(num1) + 1);
    assert(--b == bigint(num2) - 1);

    std::cout << "All increment tests passed!" << std::endl;
}
void comparison_test()
{
    int64_t num1 = -7605473406922487838;
    int64_t num2 = 7605473406922487838;
    int64_t num3 = -7605473406922487838;
    int64_t num4 = 7605473406922487837;

    assert(bigint(num1) == bigint(num3));
    assert(bigint(num1) != bigint(num2));
    assert(bigint(num1) < bigint(num2));
    assert(bigint(num2) > bigint(num1));
    assert(bigint(num2) > bigint(num1));
    assert(bigint(num1) <= bigint(num1));
    assert(bigint(num1) >= bigint(num1));
    assert(bigint(num1) <= bigint(num2));
    assert(bigint(num2) >= bigint(num1));
    assert(bigint(num4) < bigint(num2));

    std::cout << "All comparison tests passed!" << std::endl;
}

int main()
{
    try
    {
        int64_t rand_num = random_number_generator();
        std::string rand_str = random_string_generator();
        constructor_test(rand_num, rand_str);
        comparison_test();

        arithmetic_test();
        increment_test();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "All tests passed" << std::endl;

// used to generate examples
    // bigint num1;
    // bigint num2;

    // if (argc != 3)
    // {
    //     std::cout << "Usage: " << argv[0] << " <number1> <number2>" << std::endl;
    //     return 1;
    // }

    // try
    // {
    //     num1 = bigint(argv[1]);
    //     num2 = bigint(argv[2]);
    // }
    // catch (std::invalid_argument &e)
    // { // catch exceptions by reference
    //     std::cout << "Invalid argument: " << e.what() << std::endl;
    //     return 1;
    // }

    // bigint temp = num1;
    // // Display all the calculation results
    // std::cout << "Number 1 = " << num1 << std::endl;
    // std::cout << "Number 2 = " << num2 << std::endl
    //           << "\n";

    // std::cout << "Addition + +=" << std::endl;
    // std::cout << "Number 1 + Number 2 = " << num1 + num2 << std::endl;
    // num1 += num2;
    // std::cout << "Number 1 += Number 2 = " << num1 << std::endl;
    // num1 = temp;
    // std::cout << "Subtraction - -=" << std::endl;
    // std::cout << "Number 1 - Number 2 = " << num1 - num2 << std::endl;
    // num1 = temp;
    // num1 -= num2;
    // std::cout << "Number 1 -= Number 2 = " << num1 << std::endl;
    // num1 = temp;
    // std::cout << "Multiplication * *=" << std::endl;
    // std::cout << "Number 1 * Number 2 = " << num1 * num2 << std::endl;
    // num1 = temp;
    // num1 *= num2;
    // std::cout << "Number 1 *= Number 2 = " << num1 << std::endl;
    // num1 = temp;
    // std::cout << "Negation -" << std::endl;
    // num1 = temp;
    // num1 = -num1;
    // std::cout << "Number 1 = -Number 1 = " << num1 << std::endl;
    // num1 = temp;
    // std::cout << "Comparison" << std::endl;
    // std::cout << "Number 1 == Number 2 = " << (num1 == num2) << std::endl;
    // std::cout << "Number 1 != Number 2 = " << (num1 != num2) << std::endl;
    // std::cout << "Number 1 < Number 2 = " << (num1 < num2) << std::endl;
    // std::cout << "Number 1 <= Number 2 = " << (num1 <= num2) << std::endl;
    // std::cout << "Number 1 > Number 2 = " << (num1 > num2) << std::endl;
    // std::cout << "Number 1 >= Number 2 = " << (num1 >= num2) << std::endl;

    return 0;
}