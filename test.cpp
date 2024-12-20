#include <iostream>
#include <random>
#include <cassert>
#include "bigint.hpp"

//random number generator
int64_t random_number_generator() {
    std::random_device rd;
    std::mt19937_64 mt64(rd());
    std::uniform_int_distribution<int64_t> dis(INT64_MIN, INT64_MAX);
    return dis(mt64);
}
//random string generator
std::string random_string_generator(){
    std::random_device rd;
    std::mt19937_64 mt64(rd());
    std::uniform_int_distribution<int64_t> dis(INT64_MIN, INT64_MAX);
    return std::to_string(dis(mt64));
}

//constructor test
void constructor_test(int64_t num, std::string str) 
{
    //default constructor 
    bigint test;
    assert(test == bigint(0));
    
    //int64_t constructor
    bigint test1(num);
    assert(test1 == bigint(num));

    //string constructor
    bigint test2(str);
    assert(test2 == bigint(str));

    // invalid string input
    try {
        bigint invalid("-22230ii293293o");
        assert(false);
    } catch (const std::invalid_argument&) {
        assert(true);
    }

    try {
        bigint empty("");
        assert(false);
    } catch (const std::invalid_argument&) {
        assert(true);
    }

    std::cout << "All constructor tests passed!" << std::endl;
}

//arithmetic test - addition, subtraction, multiplication
void arithmetic_test() 
{
    // int64_t num1 = random_number_generator();
    // int64_t num2 = random_number_generator();
    // int64_t num3 = random_number_generator();

    int64_t num1 = -1111111111111111111;
    int64_t num2 = -1111111111111111111;
    int64_t num3 = -2222222222222222222;
    bigint a(num1);
    bigint b(num2);



    bigint c(num3);
    std::cout << "1:"<< num1 <<"|2:"<< num2<<"|3: " << num3<< std::endl;
    std::cout << "a:"<< a<<"|b:"<< b<<"|c: " << c << std::endl;
    std::cout << "a*b:"<< a*b<<std::endl;
    std::cout << "1*2:"<< num1*num2<<std::endl;
    //addition




    assert(a + b == bigint(num1 + num2));
    
    assert(a + c == bigint(num1 + num3));
    assert((a + b) + c == bigint((num1 + num2) + num3));
    //subtraction
    assert(a - b == bigint(num1 - num2));
    assert(a - c == bigint(num1 - num3));
    assert((a - b) - c == bigint((num1 - num2) - num3));
    //multiplication
    assert(a * b == bigint(num1 * num2));
    assert(a * c == bigint(num1 * num3));
    assert(a * b * c == bigint(num1 * num2 * num3));
    //consistency 
    assert(a + b - c == a - c + b && a - c + b ==bigint(num1 + num2 - num3));



    
    std::cout << "All aritmetic tests passed" << std::endl;
}


int main() {
    try {
        int64_t rand_num = random_number_generator();
        std::string rand_str = random_string_generator();
        constructor_test(rand_num, rand_str);
        arithmetic_test();
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
    
    
    std::cout << "All tests passed" << std::endl;
    return 0;
    
    

    

}