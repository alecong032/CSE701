/**
 * @file bigint.hpp
 * @author Shihong Cong
 * @brief A class that represents a big integer and supports arithmetic operations
 * @version 0.1
 * @date 2024-12-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <vector>
#include <iostream>

class bigint
{
public:
    // Constructors
    bigint();                    // default constructor
    bigint(int64_t);             // constructor for processing int64_t
    bigint(const std::string &); // constructor for processing string

    // Operators
    // subtraction
    bigint operator-(const bigint &);  // subtraction
    bigint operator-=(const bigint &); // subtraction assignment
    // addition
    bigint operator+(const bigint &);  // addition
    bigint operator+=(const bigint &); // addition assignment

    // multiplication
    bigint operator*(const bigint &);  // multiplication
    bigint operator*=(const bigint &); // multiplication assignment

    // negation
    bigint operator-(); // unary negation

    // comparison
    bool operator==(const bigint &) const; // equal to
    bool operator!=(const bigint &) const; // not equal to
    bool operator<(const bigint &) const;  // less than
    bool operator<=(const bigint &) const; // less than or equal to
    bool operator>(const bigint &) const;  // greater than
    bool operator>=(const bigint &) const; // greater than or equal to

    // insertion
    friend std::ostream &operator<<(std::ostream &, const bigint &); // output stream

    // increment and decrement
    // pre + post
    bigint operator++(); // pre-increment
    bigint operator--(); // pre-decrement

    bigint operator++(int); // post-increment
    bigint operator--(int); // post-decrement

private:
    std::vector<int8_t> digits; // little endian
    bool is_negative;           // true if negative, false if positive

    // helper functions + variables
    bigint negate(const bigint &) const;                   // negate a bigint
    bigint add(const bigint &, const bigint &);            // addition logic for two positive numbers
    bigint subtract(const bigint &, const bigint &);       // subtraction logic for num1 > num2
    bool is_smaller(const bigint &, const bigint &) const; // compare two bigints
};

/**
 * @brief Construct a new bigint::bigint object with empty value
 *
 */
bigint::bigint()
{
    digits.push_back(0);
    is_negative = false;
}

/**
 * @brief Construct a new bigint object
 *
 * @param val a int64_t value to be converted to bigint
 */
bigint::bigint(int64_t val)
{
    is_negative = (val < 0);
    val = std::abs(val);

    if (val == 0)
    {
        bigint();
        return;
    }
    else
    {
        while (val > 0)
        {
            digits.push_back((int8_t)(val % 10)); // retrieve the last digit
            val /= 10;                            // remove the last digit
        }
    }
}

/**
 * @brief Construct a new bigint object
 *
 * @param str a string value to be converted to bigint
 */
bigint::bigint(const std::string &str)
{
    if (str.empty())
    {
        throw std::invalid_argument("Input String is Empty");
    }

    if (str == "0")
    {
        bigint();
        return;
    }

    is_negative = (str[0] == '-');

    for (int64_t i = (int64_t)str.size() - 1; i >= 0; i--)
    {
        if (str[(size_t)i] == '-' && i == 0)
        {
            continue;
        }

        if (str[(size_t)i] < '0' || str[(size_t)i] > '9')
        {
            throw std::invalid_argument("Invalid argument: " + str);
        }
        digits.push_back(str[(size_t)i] - '0'); // convert char to int
    }
}

/**
 * @brief a helper function to negate of a bigint
 *
 * @param num a bigint to be negated
 * @return bigint the negated bigint
 */
bigint bigint::negate(const bigint &num) const
{
    bigint result = num;
    result.is_negative = !result.is_negative;
    return result;
}

/**
 * @brief a helper function contains the logic for addition of two bigints
 *
 * @param num1 a bigint that is always positive
 * @param num2 a bigint that is always positive
 * @return bigint the result of the addition
 */
bigint bigint::add(const bigint &num1, const bigint &num2)
{
    bigint result;
    result.digits.clear(); // Remove leading zeros
    int8_t carry = 0;      // when the sum of two digits is greater than 10, carry +1
    int64_t i = 0;
    const int8_t base = 10; // constant base for the digits is always 10

    // perform the addition for each digits
    while (i < (int64_t)num1.digits.size() || i < (int64_t)num2.digits.size())
    {
        int8_t sum = carry;
        if (i < (int64_t)num1.digits.size())
        {
            sum += num1.digits[(size_t)i];
        }
        if (i < (int64_t)num2.digits.size())
        {
            sum += num2.digits[(size_t)i];
        }
        result.digits.push_back(sum % base);
        carry = sum / base;
        i++;
    }

    // add remaining carry
    if (carry > 0)
    {
        result.digits.push_back(carry);
    }

    return result;
}

/**
 * @brief a helper function contains the logic for subtraction of two bigints
 *
 * @param num1 a bigint that is larger than num2
 * @param num2 a bigint
 * @return bigint the result of the subtraction
 */
bigint bigint::subtract(const bigint &num1, const bigint &num2)
{
    bigint result;
    result.digits.clear(); // Remove leading zeros
    int8_t borrow = 0;     // when the difference of two digits is less than 0, borrow -1
    int64_t i = 0;

    bigint n1 = num1; // Create modifiable copies
    bigint n2 = num2;

    // If num2 is negative, convert to addition
    if (n2.is_negative)
    {
        n2 = negate(n2);
        return add(n1, n2);
    }

    // perform the subtraction for each digits
    while (i < (int64_t)n1.digits.size() || i < (int64_t)n2.digits.size())
    {
        int8_t diff = borrow; // Subtract the borrow
        if (i < (int64_t)n1.digits.size())
        {
            diff += n1.digits[(size_t)i];
        }
        if (i < (int64_t)n2.digits.size())
        {
            diff -= n2.digits[(size_t)i];
        }
        if (diff < 0)
        {
            diff += 10;  // borrow from the next digit
            borrow = -1; // reduce the next digit by 1
        }
        else
        {
            borrow = 0;
        }

        result.digits.push_back(diff);
        i++;
    }

    // Remove leading zeros
    while (result.digits.size() > 1 && result.digits.back() == 0)
    {
        result.digits.pop_back();
    }

    // Handle zero result
    if (result.digits.size() == 1 && result.digits[0] == 0)
    {
        result.is_negative = false;
    }

    return result;
}

/**
 * @brief a helper function to compare two bigints and determine if num1 is smaller than num2
 *
 * @param num1 a bigint
 * @param num2 a bigint
 * @return true if num1 is smaller than num2
 * @return false if num1 is larger than num2
 */
bool bigint::is_smaller(const bigint &num1, const bigint &num2) const
{
    if (num1.is_negative && num2.is_negative)
    { // Both negative, compare absolute values in reverse
        bigint n1 = negate(num1);
        bigint n2 = negate(num2);
        return is_smaller(n2, n1);
    }

    if (num1.is_negative && !num2.is_negative)
    {
        return true; // negative is always smaller than positive
    }

    if (!num1.is_negative && num2.is_negative)
    {
        return false; // positive is always larger than negative
    }

    if (num1.digits.size() < num2.digits.size())
    {
        return true; // fewer digits means smaller
    }

    if (num1.digits.size() > num2.digits.size())
    {
        return false; // more digits means larger
    }

    // if the number of digits are the same, compare each digit from the most significant digit
    for (int64_t i = (int64_t)num1.digits.size() - 1; i >= 0; i--)
    {
        // Compare each digit from the most significant digit
        if (num1.digits[(size_t)i] < num2.digits[(size_t)i])
        {
            return true;
        }
        if (num1.digits[(size_t)i] > num2.digits[(size_t)i])
        {
            return false;
        }
    }
    return false; // Numbers are equal
}

// operator logic
/**
 * @brief Overload the + operator to perform addition of two bigints using helper functions
 *
 * @param other a bigint to be added
 * @return bigint the result of the addition
 */
bigint bigint::operator+(const bigint &other)
{
    bigint result;

    // Case 1: Same sign -> Perform addition
    if (is_negative == other.is_negative)
    {
        result = add(*this, other);       // add takes two positive numbers and returns a positive number
        result.is_negative = is_negative; // assign the sign of the result based on the sign of either number
    }
    // Case 2: Different signs -> Perform subtraction
    else
    {
        // num1 < num2, calculate num2 - (+num)
        if (is_smaller(*this, other))
        {
            bigint n1 = negate(*this);
            bigint n2 = other;
            result = n2 - n1; // pass to operator- to perform subtraction and handle the sign
        }
        // num1 > num2, calculate num1 - (+num2)
        else
        {
            bigint n2 = negate(other);
            result = *this - n2; // pass to operator- to perform subtraction and handle the sign
        }
    }

    return result;
}

/**
 * @brief Overload the += operator to perform addition of two bigints use operator+()
 *
 * @param other a bigint to be added
 * @return bigint the result of the addition
 */
bigint bigint::operator+=(const bigint &other)
{
    *this = *this + other;
    return *this;
}

/**
 * @brief Overload the - operator to perform subtraction of two bigints using helper functions
 *
 * @param other a bigint to be subtracted
 * @return bigint the result of the subtraction
 */
bigint bigint::operator-(const bigint &other)
{
    bigint result;

    // second number is negative, convert to addition
    if (other.is_negative)
    {
        bigint n2 = negate(other);
        result = *this + n2; // pass to operator+ to perform addition and handle the sign
    }
    else
    {
        // equivalent to addition
        if (is_negative)
        {
            // −num1−(-num2)=−(num1+num2)
            bigint n1 = negate(*this);
            result = add(n1, other);
            result.is_negative = true; // num1 < num2, result is negative
        }
        // when both numbers have same sign
        else
        {
            // num1 < num2, calculate num2 - num1
            if (is_smaller(*this, other))
            {
                result = subtract(other, *this);
                result.is_negative = true; // num1 < num2, result is negative
            }
            // num1 > num2, calculate num1 - num2
            else
            {
                result = subtract(*this, other);
            }
        }
    }
    return result;
}

/**
 * @brief Overload the -= operator to perform subtraction of two bigints use  operator-()
 * @param other a bigint to be subtracted
 * @return bigint the result of the subtraction
 */
bigint bigint::operator-=(const bigint &other)
{
    *this = *this - other;
    return *this;
}

/**
 * @brief Overload the * operator to perform multiplication of two bigints using long multiplication method
 *
 * @param other
 * @return bigint the result of the multiplication
 */
bigint bigint::operator*(const bigint &other)
{
    bigint result;

    if ((digits.size() == 1 && digits[0] == 0) || (other.digits.size() == 1 && other.digits[0] == 0))
    {
        result.is_negative = false;
        return result;
    }

    for (int64_t i = 0; i < (int64_t)digits.size(); i++)
    {
        bigint temp;                // temporary bigint to store the result of each digit multiplication
        int8_t carry = 0;           // carry from the previous digit multiplication
        temp.digits.clear();        // remove leading zeros
        constexpr int8_t base = 10; // constant base for the digits is always 10

        // perform the multiplication for each digit
        for (int64_t j = 0; j < (int64_t)other.digits.size(); j++)
        {
            int8_t product = int8_t(digits[(size_t)i] * other.digits[(size_t)j] + carry);
            temp.digits.push_back(product % base);
            carry = (product / base);
        }

        // add remaining carry
        if (carry > 0)
        {
            temp.digits.push_back(carry);
        }

        // shift the digits in temp based on the current position in the first number
        for (int64_t j = 0; j < i; j++)
        {
            temp.digits.insert(temp.digits.begin(), 0); // Insert zeros at the beginning
        }

        result += temp;
    }

    result.is_negative = is_negative ^ other.is_negative;
    return result;
}

/**
 * @brief Overload the *= operator to perform multiplication of two bigints use operator*()
 *
 * @param other a bigint to be multiplied
 * @return bigint the result of the multiplication
 */
bigint bigint::operator*=(const bigint &other)
{
    *this = *this * other;
    return *this;
}

/**
 * @brief Overload the - operator to negate a bigint
 *
 * @return bigint the negated bigint
 */
bigint bigint::operator-()
{
    bigint result = *this;
    result.is_negative = !is_negative;
    return result;
}

/**
 * @brief Overload the == operator to compare two bigints
 *
 * @param other a bigint to be compared
 * @return true if the two bigints are equal
 * @return false if the two bigints are not equal
 */
bool bigint::operator==(const bigint &other) const
{

    if (is_negative != other.is_negative || digits.size() != other.digits.size())
    {
        return false;
    }

    // compare each digit
    for (size_t i = 0; i < digits.size(); i++)
    {
        int8_t digit1 = digits[i];
        int8_t digit2 = other.digits[i];

        if (digit1 != digit2)
        {
            return false;
        }
    }
    return true;
}

/**
 * @brief Overload the != operator to compare two bigints
 *
 * @param other a bigint to be compared
 * @return true if the two bigints are not equal
 * @return false if the two bigints are equal
 */
bool bigint::operator!=(const bigint &other) const
{
    return !(*this == other);
}

/**
 * @brief Overload the < operator to compare two bigints
 *
 * @param other a bigint to be compared
 * @return true if the first bigint is smaller than the second bigint
 * @return false if the first bigint is larger than the second bigint
 */
bool bigint::operator<(const bigint &other) const
{
    return is_smaller(*this, other);
}

/**
 * @brief Overload the <= operator to compare two bigints
 *
 * @param other a bigint to be compared
 * @return true if the first bigint is smaller than or equal to the second bigint
 * @return false if the first bigint is larger than the second bigint
 */
bool bigint::operator<=(const bigint &other) const
{
    if (*this == other)
    {
        return true;
    }
    return is_smaller(*this, other);
}

/**
 * @brief Overload the > operator to compare two bigints
 *
 * @param other a bigint to be compared
 * @return true if the first bigint is larger than the second bigint
 * @return false if the first bigint is smaller than the second bigint
 */
bool bigint::operator>(const bigint &other) const
{
    return is_smaller(other, *this);
}

/**
 * @brief Overload the >= operator to compare two bigints
 *
 * @param other a bigint to be compared
 * @return true if the first bigint is larger than or equal to the second bigint
 * @return false if the first bigint is smaller than the second bigint
 */
bool bigint::operator>=(const bigint &other) const
{
    if (*this == other)
    {
        return true;
    }
    return is_smaller(other, *this);
}

/**
 * @brief Overload the << operator to print a bigint to an output stream
 *
 * @param os an output stream
 * @param num a bigint to be inserted
 * @return std::ostream& the output stream
 */
std::ostream &operator<<(std::ostream &os, const bigint &num)
{
    if (num.is_negative)
    {
        os << '-';
    }
    if (num.digits.size() == 1 && num.digits[0] == 0)
    {
        os << '0';
        return os;
    }
    else
    {
        for (size_t i = num.digits.size(); i > 0; i--)

        {
            os << std::to_string(num.digits[i - 1]);
        }
    }

    return os;
}

/**
 * @brief Overload the ++ operator to increment a bigint
 *
 * @return bigint the pre-incremented bigint
 */
bigint bigint::operator++()
{
    *this = *this + 1; // Add 1 to the current object
    return *this;
}

/**
 * @brief Overload the ++ operator to increment a bigint
 *
 * @param int
 * @return bigint the post-incremented bigint
 */
bigint bigint::operator++(int)
{
    bigint temp = *this;
    ++(*this); // Use pre-increment to modify the object
    return temp;
}

/**
 * @brief Overload the -- operator to decrement a bigint
 *
 * @return bigint the pre-decremented bigint
 */
bigint bigint::operator--()
{
    *this = *this - 1; // Subtract 1 from the current object
    return *this;
}

/**
 * @brief Overload the -- operator to decrement a bigint
 *
 * @param int
 * @return bigint the post-decremented bigint
 */
bigint bigint::operator--(int)
{
    bigint temp = *this; // Save the current state
    --(*this);           // Use pre-decrement to modify the object
    return temp;
}
