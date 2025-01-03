#include <iostream>
#include <random>
#include <cassert>
#include <stdexcept>
#include "bigint.hpp"

// global variables
bigint pass = 0; // used to count the number of tests passed
bigint fail = 0; // used to count the number of tests failed

/**
 * @brief generate a random number between INT64_MIN and INT64_MAX to test the constructor
 *
 * @return int64_t
 */
int64_t random_number_generator()
{
    std::random_device rd;
    std::mt19937_64 mt64(rd());
    std::uniform_int_distribution<int64_t> dis(INT64_MIN, INT64_MAX);
    return dis(mt64);
}

/**
 * @brief generate a random string to test the constructor
 *
 * @return std::string
 */
std::string random_string_generator()
{
    std::random_device rd;
    std::mt19937_64 mt64(rd());
    std::uniform_int_distribution<int64_t> dis(INT64_MIN, INT64_MAX);
    return std::to_string(dis(mt64));
}

/**
 * @brief test three constructors: default, int64_t, and string
 *
 * @param num a random int64_t number generated by random_number_generator()
 * @param str a random string generated by random_string_generator()
 */
void constructor_test(int64_t num, std::string str)
{
    // Default constructor
    bigint test;
    if (test == bigint())
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Default constructor test failed!" << std::endl;
    }

    // int64_t constructor
    bigint test1(num);
    if (test1 == bigint(num))
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "int64_t constructor test failed!" << std::endl;
    }

    // string constructor
    bigint test2(str);
    if (test2 == bigint(str))
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "String constructor test failed!" << std::endl;
    }

    // test constructing large invalid numbers from a string should fail
    try
    {
        bigint a("3092-4893240890238490435239482493024803294892349024");
        fail++;
        std::cout << "Invalid string test failed: exception not thrown!" << std::endl;
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        pass++;
    }

    // Empty string input
    try
    {
        bigint empty("");
        fail++;
        std::cout << "Empty string test failed: exception not thrown!" << std::endl;
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        pass++;
    }

    // Output test results
    if (fail == 0)
    {
        std::cout << "All constructor tests passed!" << std::endl;
    }
    else
    {
        std::cout << "Some constructor tests failed!" << std::endl;
    }
}

// arithmetic test - addition, subtraction, multiplication
/**
 * @brief test arithmetic operations: addition, subtraction, multiplication
 *  uses random int64_t numbers generated by random_number_generator()
 *
 */
void arithmetic_test()
{
    int64_t num1 = random_number_generator();
    int64_t num2 = random_number_generator();
    int64_t num3 = random_number_generator();

    bigint a(num1);
    bigint b(num2);
    bigint c(num3);

    // Addition

    if (a + b == bigint(num1) + bigint(num2))
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Addition test failed: a + b != bigint(num1) + bigint(num2)" << std::endl;
    }

    if (a + c == bigint(num1) + bigint(num3))
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Addition test failed: a + c != bigint(num1) + bigint(num3)" << std::endl;
    }

    if (a + b + c == bigint(num1) + bigint(num2) + bigint(num3))
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Multiple addition test failed: a + b + c != bigint(num1) + bigint(num2) + bigint(num3)" << std::endl;
    }

    // Subtraction
    if (a - b == bigint(num1) - bigint(num2))
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Subtraction test failed: a - b != bigint(num1) - bigint(num2)" << std::endl;
    }

    if (a - c == bigint(num1) - bigint(num3))
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Subtraction test failed: a - c != bigint(num1) - bigint(num3)" << std::endl;
    }

    if (a - b - c == bigint(num1) - bigint(num2) - bigint(num3))
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Multiple subtraction test failed: a - b - c != bigint(num1) - bigint(num2) - bigint(num3)" << std::endl;
    }

    // Multiplication
    if (a * b == bigint(num1) * bigint(num2))
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Multiplication test failed: a * b != bigint(num1) * bigint(num2)" << std::endl;
    }

    if (a * c == bigint(num1) * bigint(num3))
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Multiplication test failed: a * c != bigint(num1) * bigint(num3)" << std::endl;
    }

    if (a * b * c == bigint(num1) * bigint(num2) * bigint(num3))
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Multiple multiplication test failed: a * b * c != bigint(num1) * bigint(num2) * bigint(num3)" << std::endl;
    }

    // Consistency tests
    if ((a + b - c) == (a - c + b))
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Consistency test failed: (a + b - c) != (a - c + b)" << std::endl;
        std::cout << "a : " << a << std::endl;
        std::cout << "b : " << b << std::endl;
        std::cout << "c : " << c << std::endl;
        std::cout << "a + b - c: " << a + b - c << std::endl;
        std::cout << "a - c + b: " << a - c + b << std::endl;
    }

    if ((a + (b - c)) == ((a + b) - c))
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Consistency test failed: (a + (b - c)) != ((a + b) - c)" << std::endl;
        std::cout << "a : " << a << std::endl;
        std::cout << "b : " << b << std::endl;
        std::cout << "c : " << c << std::endl;
        std::cout << "a + (b - c): " << a + (b - c) << std::endl;
        std::cout << "(a + b) - c: " << (a + b) - c << std::endl;
    }

    if (((a - b) + c) == (a - (b - c)))
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Consistency test failed: ((a - b) + c) != (a - (b - c))" << std::endl;
        std::cout << "a : " << a << std::endl;
        std::cout << "b : " << b << std::endl;
        std::cout << "c : " << c << std::endl;
        std::cout << "(a - b) + c: " << (a - b) + c << std::endl;
        std::cout << "a - b: " << a - b << std::endl;
        std::cout << "a - (b - c): " << a - (b - c) << std::endl;
        std::cout << "b - c: " << b - c << std::endl;
    }

    // Output test results
    if (fail == 0)
    {
        std::cout << "All arithmetic tests passed!" << std::endl;
    }
    else
    {
        std::cout << "Some arithmetic tests failed!" << std::endl;
    }
}
/**
 * @brief test increment and decrement operations
 *
 */
void increment_test()
{
    int64_t num1 = -10;
    bigint a(num1);

    // Test post-increment
    bigint result = a++;
    // bigint a should be updated to -9 on next call of bigint a 
    if (result == bigint(num1))
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Post-increment test failed: a++ returned " << result
                  << ", expected " << bigint(num1) << std::endl;
    }

    if (a == bigint(num1) + 1)
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Post-increment test failed: a updated to " << a
                  << ", expected " << bigint(num1) + 1 << std::endl;
    }

    // Test pre-increment
    if (++a == bigint(num1) + 2)
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Pre-increment test failed: ++a returned " << a
                  << ", expected " << bigint(num1) + 2 << std::endl;
    }

    // Reset a
    a = bigint(num1);

    // Test post-decrement
    result = a--;
    if (result == bigint(num1))
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Post-decrement test failed: a-- returned " << result
                  << ", expected " << bigint(num1) << std::endl;
    }

    if (a == bigint(num1) - 1)
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Post-decrement test failed: a updated to " << a
                  << ", expected " << bigint(num1) - 1 << std::endl;
    }

    // Test pre-decrement
    if (--a == bigint(num1) - 2)
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Pre-decrement test failed: --a returned " << a
                  << ", expected " << bigint(num1) - 2 << std::endl;
    }

    // Output test results
    if (fail == 0)
    {
        std::cout << "All increment tests passed!" << std::endl;
    }
    else
    {
        std::cout << "Some increment tests failed!" << std::endl;
    }
}

/**
 * @brief test comparison operations: ==, !=, <, <=, >, >=
 *
 */
void comparison_test()
{
    int64_t num1 = -7605473406922487838;
    int64_t num2 = 7605473406922487838;
    int64_t num3 = -7605473406922487838;
    int64_t num4 = 7605473406922487837;

    if (bigint(num1) == bigint(num3))
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Comparison test failed: bigint(num1) != bigint(num3)" << std::endl;
    }

    if (bigint(num1) != bigint(num2))
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Comparison test failed: bigint(num1) == bigint(num2)" << std::endl;
    }

    if (bigint(num1) < bigint(num2))
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Comparison test failed: bigint(num1) >= bigint(num2)" << std::endl;
    }

    if (bigint(num2) > bigint(num1))
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Comparison test failed: bigint(num2) <= bigint(num1)" << std::endl;
    }

    if (bigint(num4) <= bigint(num2))
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Comparison test failed: bigint(num4) > bigint(num2)" << std::endl;
    }

    if (bigint(num2) >= bigint(num4))
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Comparison test failed: bigint(num2) < bigint(num4)" << std::endl;
    }

    // Output test results
    if (fail == 0)
    {
        std::cout << "All comparison tests passed!" << std::endl;
    }
    else
    {
        std::cout << "Some comparison tests failed!" << std::endl;
    }
}
/**
 * @brief test all operations for very large numbers 
 *
 */
void large_number_test()
{
    // Generate very large numbers
    std::string num1 = "1";
    num1.append(1000, '0');      // Creates a string start with 1 and follows with 1000 '0' characters
    std::string num2(1000, '9'); // Creates a string with 1000 '9' characters

    bigint a(num1); // Initialize bigint with num1
    bigint b(num2); // Initialize bigint with num2

    // Test Addition
    bigint addition_result = a + b; // 1000...000 + 999...999
    std::string expected_addition_result_str("1");
    expected_addition_result_str.append(1000, '9');
    bigint expected_addition_result(expected_addition_result_str);
    if (addition_result == expected_addition_result)
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Addition test failed for very large numbers." << std::endl;
        std::cout << "Expected: " << expected_addition_result << ", Got: " << addition_result << std::endl;
    }

    // Test Subtraction
    bigint subtraction_result = a - b;       // 1000...000 - 999...999
    bigint expected_subtraction_result("1"); // The result should be 1
    if (subtraction_result == expected_subtraction_result)
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Subtraction test failed for very large numbers." << std::endl;
        std::cout << "Expected: " << expected_subtraction_result << ", Got: " << subtraction_result << std::endl;
    }

    // Test Multiplication
    bigint multiplication_result = a * b;                 // 1000...000 * 999...999 = 1000 of 9 followed by 1000 of 0
    std::string expected_multiplication_result_str = ""; 
    expected_multiplication_result_str.append(1000, '9'); // Append 1000 of 9
    expected_multiplication_result_str.append(1000, '0'); // Append 1000 of 0
    bigint expected_multiplication_result(expected_multiplication_result_str);
    if (multiplication_result == expected_multiplication_result)
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Multiplication test failed for very large numbers." << std::endl;
        std::cout << "Expected: " << expected_multiplication_result << ", Got: " << multiplication_result << std::endl;
    }

    // Test Increment
    bigint increment_test = b;
    ++increment_test;                       // Increment 999...999
    bigint expected_increment_result(num1); // Increment makes it 1000...000
    if (increment_test == expected_increment_result)
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Increment test failed for very large numbers." << std::endl;
        std::cout << "Expected: " << expected_increment_result << ", Got: " << increment_test << std::endl;
    }

    // Test Decrement
    bigint decrement_test = a;
    --decrement_test;                       // Decrement 1000...000
    bigint expected_decrement_result(num2); // Decrement makes it 999...999
    if (decrement_test == expected_decrement_result)
    {
        pass++;
    }
    else
    {
        fail++;
        std::cout << "Decrement test failed for very large numbers." << std::endl;
        std::cout << "Expected: " << expected_decrement_result << ", Got: " << decrement_test << std::endl;
    }

    // Output test results
    if (fail == 0)
    {
        std::cout << "All large number tests passed!" << std::endl;
    }
    else
    {
        std::cout << "Some large number tests failed!" << std::endl;
    }
}

int main()
{

    int64_t rand_num = random_number_generator();
    std::string rand_str = random_string_generator();
    constructor_test(rand_num, rand_str);
    arithmetic_test();
    increment_test();
    comparison_test();
    large_number_test();

    if (fail == 0)
    {
        std::cout << "==================================" << std::endl;
        std::cout << "All tests for Bigint class passed!" << std::endl;
    }
    else
    {
        std::cout << "==================================" << std::endl;
        std::cout << "Some tests for Bigint class failed!" << std::endl;
    }

    return 0;
}