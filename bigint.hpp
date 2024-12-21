#include <vector>
#include <iostream>

class bigint 
{
public:  
    
    //Constructors 
    bigint();
    bigint(int64_t);            // constructor for processing int64_t
    bigint(const std::string &);     // constructor for processing string

    //Operators
    //subtraction
    bigint operator-(const bigint &); 
    bigint operator-=(const bigint &); 
    //addition 
    bigint operator+(const bigint &); 
    bigint operator+=(const bigint &); 
    
    
   
    //multiplication
    bigint operator*(const bigint &); 
    bigint operator*=(const bigint &);

    //negation
    bigint operator-();  

    //comparison
    bool operator==(const bigint&) const; 
    bool operator!=(const bigint&) const; 
    bool operator<(const bigint&) const; 
    bool operator<=(const bigint&) const; 
    bool operator>(const bigint&) const; 
    bool operator>=(const bigint&) const; 

    //insertion
    friend std::ostream &operator<<(std::ostream &, const bigint &);

    //increment and decrement
    //pre
    bigint& operator++();               
    bigint& operator--(); 
    //post
    bigint operator++(int);
    bigint operator--(int);
         
private: 
    std::vector<int8_t> digits;
    bool is_negative; 
    
    //helper functions + variables
    bigint negate(const bigint &) const;  
    bigint add(const bigint&, const bigint&);  
    bigint subtract(const bigint&, const bigint&);
    bool is_smaller(const bigint&, const bigint&) const;
};


//constructor
bigint::bigint()
{
    digits = {0};
    is_negative = false;
}

bigint::bigint(int64_t val)
{  
    is_negative = (val < 0);
    val = std::abs(val);

    if (val == 0)
    {
        digits = {0};
    } else {
        while (val > 0)
        {
            digits.push_back((int8_t)(val % 10));
            val /= 10;
        }
    } 
}

bigint::bigint(const std::string& str)
{
    if(str.empty())
    {
        throw std::invalid_argument("Input String is Empty");
    }

    is_negative = (str[0] == '-');

    
   for (int64_t i = (int64_t)str.size() - 1; i >= 0; i--)
    {
        if (str[(size_t)i] == '-')
        {
            continue;
        }
        if (str[(size_t)i] < '0' || str[(size_t)i] > '9')
        {
            throw std::invalid_argument("Invalid argument");
        }
        digits.push_back(str[(size_t)i] - '0');
    }
}


//helper
bigint bigint::negate(const bigint& num) const
{
    bigint result = num;
    result.is_negative = !result.is_negative;
    return result;
}

bigint bigint::add(const bigint& num1, const bigint& num2)
{
    bigint result;
    result.digits.clear(); // Remove leading zeros
    int8_t carry = 0;
    int64_t i = 0;
    const int8_t base = 10;

    // ferform the addition for each digits
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
    if (carry > 0) {
        result.digits.push_back(carry);
    }

    return result;
}


bigint bigint::subtract(const bigint& num1, const bigint& num2)
{
    bigint result;
    result.digits.clear(); // Remove leading zeros
    int8_t borrow = 0;
    int64_t i = 0;
    constexpr int8_t base = 10;

    bigint n1 = num1; // Create modifiable copies
    bigint n2 = num2;

    // If num2 is negative, convert to addition
    
    // if (n2.is_negative) {
    //     n2 = negate(n2);
    //     return add(n1, n2);
    // }

    // Perform the subtraction
    while (i < (int64_t)n1.digits.size() || i < (int64_t)n2.digits.size())
    {
        int8_t diff = -borrow; //subtract the borrow
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
            diff += base; // Borrow from the next digit
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.digits.push_back(diff);
        i++;
    }

    // Remove leading zeros
    while (result.digits.size() > 1 && result.digits.back() == 0) {
        result.digits.pop_back();
    }

    // Handle zero result
    if (result.digits.size() == 1 && result.digits[0] == 0) {
        result.is_negative = false;
    }

    return result;
}


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
        return true; // Negative is always smaller than positive
    }

    if (!num1.is_negative && num2.is_negative)
    {
        return false; // Positive is always larger than negative
    }

    if (num1.digits.size() < num2.digits.size())
    {
        return true; // Fewer digits means smaller
    }

    if (num1.digits.size() > num2.digits.size())
    {
        return false; // More digits means larger
    }

    for (int64_t i = (int64_t)num1.digits.size() - 1; i >= 0; i--)
    { // Compare each digit from the most significant digit
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
bigint bigint::operator+(const bigint& other) 
{
    bigint result;

    // Case 1: Same sign -> Perform addition
    if (is_negative == other.is_negative) {
        result = add(*this, other);
        result.is_negative = is_negative; // Result takes the sign of the operands
    } 
    // Case 2: Different signs -> Perform subtraction
    else {
        if (is_smaller(*this, other)) {
            result = subtract(other, negate(*this)); // Ensure num1 > num2
            result.is_negative = false; // Result takes the sign of the larger operand
        } else {
            result = subtract(negate(other),*this);
            result.is_negative = true; // Result takes the sign of the larger operand
        }
    }

    return result;
}





bigint bigint::operator+=(const bigint& other)
{
    *this = *this + other;

    return *this;
}

bigint bigint::operator-(const bigint& other) 
{
    bigint result;
    // 
    if (is_negative != other.is_negative) {
        if(is_negative) {
            result = add(negate(*this), other);
            result.is_negative = true;
        }else{
            result = add(*this, negate(other));
            result.is_negative = false;
        }
    }else {
        if(is_negative){
            if(is_smaller(*this, other)) {
            result = subtract(negate(other), negate(*this));
            result.is_negative = true;
        }else{
            result = subtract(negate(other), negate(*this));
            result.is_negative = false;
        }
        }
        

    }

  

    return result;
}




bigint bigint::operator-=(const bigint& other)
{
    *this = *this - other;
    return *this;
}

bigint bigint::operator*(const bigint& other)
{
    bigint result;

    if ((digits.size() == 1 && digits[0] == 0) || (other.digits.size() == 1 && other.digits[0] == 0)) 
    {   
        result.is_negative = false;
        return result;
    }

    for (int64_t i = 0; i < (int64_t)digits.size(); i++) 
    {
        bigint temp;         
        int8_t carry = 0; 
        temp.digits.clear();    //remove leading zeros
        constexpr int8_t base = 10;

        for (int64_t j = 0; j < (int64_t)other.digits.size(); j++) 
        {
            int8_t product = (digits[(size_t)i]) * (other.digits[(size_t)j]) + carry;
            temp.digits.push_back((product % base));
            carry = product / base;
                                              
        }

        if (carry > 0) 
        {
            temp.digits.push_back(carry);
        }

        for (int64_t j = 0; j < i; j++)
        {
            temp.digits.insert(temp.digits.begin(), 0); // Insert zeros at the beginning
        }

      

        result += temp; 
    }

    result.is_negative = is_negative ^ other.is_negative;
    return result;
}


bigint bigint::operator*=(const bigint& other)
{
    *this = *this * other;
    return *this;
}


bigint bigint::operator-()
{
    bigint result = *this;
    result.is_negative = !is_negative;
    return result;
}

bool bigint::operator==(const bigint& other) const
{   

    if (is_negative != other.is_negative || digits.size() != other.digits.size()){
        return false;
    }
    for (size_t i = 0; i < digits.size(); i++){
        int8_t digit1 = digits[i];
        int8_t digit2 = other.digits[i];
        if(digit1!=digit2){
            return false;
        }
    }
    return true;
}

bool bigint::operator!=(const bigint& other) const
{
    return !(*this == other);
}   

bool bigint::operator<(const bigint &other) const
{
   return is_smaller(*this, other);
}


bool bigint::operator<=(const bigint& other) const
{
    if(*this == other )
    {
        return true;
    }
    return is_smaller(*this, other);
}
bool bigint::operator>(const bigint& other) const
{
    return is_smaller(other, *this);
}
bool bigint::operator>=(const bigint& other) const
{
    if(*this == other )
    {
        return true;
    }
    return is_smaller(other, *this);
}

std::ostream& operator<<(std::ostream& os, const bigint& num)
{
    if(num.is_negative)
    {
        os << '-';
    }
    if (num.digits.size() == 1 && num.digits[0] == 0)
    {
        os << '0';
        return os;
    } else {
        for (size_t i = num.digits.size(); i > 0; i--)

        {
            os << std::to_string(num.digits[i-1]);
        }
    }

    return os;
    
    
}

bigint& bigint::operator++()
{
    *this += bigint(1);
    return *this;
}
bigint& bigint::operator--()
{
    *this -= bigint(1);
    return *this;
}

bigint bigint::operator++(int) {
    bigint temp = *this;  
    ++(*this);            
    return temp;          
}

bigint bigint::operator--(int) {
    bigint temp = *this; 
    --(*this);            
    return temp;          
}




