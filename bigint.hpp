#include <vector>
#include <iostream>

using namespace std;

class bigint 
{
public: 
    //Constructors 
    bigint();
    bigint(int64_t);            // constructor for processing int64_t
    bigint(const string &);     // constructor for processing string

    //Operators
    //addition 
    bigint operator+(const bigint &); 
    bigint operator+=(const bigint &); 
    
    //subtraction
    bigint operator-(const bigint &); 
    bigint operator-=(const bigint &); 
   
    //multiplication
    bigint operator*(const bigint &); 
    bigint operator*=(const bigint &);

    //negation
    bigint operator-();  

    //comparison
    bigint operator==(const bigint &);
    bigint operator!=(const bigint &); 
    bigint operator<(const bigint &); 
    bigint operator<=(const bigint &);
    bigint operator>(const bigint &); 
    bigint operator>=(const bigint &); 

    //insertion
    friend ostream &operator<<(ostream &, const bigint &);

    //increment and decrement
    bigint operator++();               
    bigint operator--(); 

         
private: 
    vector<uint8_t> digits;
    bool is_negative;


    //helper functions
    bigint negate(const bigint &);  
    bigint add(const bigint&, const bigint&);  
    bigint subtract(const bigint&, const bigint&);
};


//constructor
bigint::bigint()
{
    digits = {};
    is_negative = false;
}

bigint::bigint(int64_t val)
{  
    is_negative = (val < 0);
    val = abs(val);

    if (val == 0)
    {
        digits = {0};
    } else {
        while (val > 0)
        {
            digits.push_back(val % 10);
            val /= 10;
        }
    } 
}

bigint::bigint(const string& str)
{
    if(str.empty())
    {
        throw invalid_argument("Input String is Empty");
    }

    is_negative = (str[0] == '-');
    size_t start = (str[0] == '-' || str[0] == '+') ? 1 : 0;
    
   for (size_t i = str.size(); i > start; --i) 
   {
        char ch = str[i - 1]; 
        if (ch < '0' || ch > '9') 
        {
            throw invalid_argument("Invalid character in input string.");
        }
        digits.push_back(ch - '0'); 
    }

}


//helper
bigint bigint::negate(const bigint& num)
{
    bigint result = num;
    result.is_negative = !result.is_negative;
    return result;
}

bigint bigint::add(const bigint& num1, const bigint& num2)
{
    bigint result;
    uint8_t carry = 0;

    size_t size1 = num1.digits.size();
    size_t size2 = num2.digits.size();
    size_t size = max(size1, size2);  //take the larger size for for loop 

    for(size_t i = 0; i < size; i++) {
            //if i exceeds the size of digits, set it to 0
            uint8_t digit1 = (i < size1) ? num1.digits[i] : 0;       
            uint8_t digit2 = (i < size2) ? num2.digits[i] : 0;

            uint8_t sum = digit1 + digit2 + carry; 
            result.digits.push_back(sum % 10);
            //prepare carry for next addition
            carry = sum / 10;
    }
    //push remaining carry to result
    if(carry > 0) {
        result.digits.push_back(carry);
    }

    return result;
}

bigint bigint::subtract(const bigint& num1, const bigint& num2)
{
    bigint result;
    uint8_t borrow = 0;

    size_t size1 = num1.digits.size();
    size_t size2 = num2.digits.size();
    size_t max_size = max(size1, size2); 

    for (size_t i = 0; i < max_size; i++) {
        uint8_t digit1 = (i < size1) ? num1.digits[i] : 0;       
        uint8_t digit2 = (i < size2) ? num2.digits[i] : 0;

        uint8_t diff = digit1 - digit2 - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.digits.push_back(diff);
    }

    // Remove leading zeros
    while (result.digits.size() > 1 && result.digits.back() == 0) {
        result.digits.pop_back();
    }

    return result;
}

// operator logic 
bigint bigint::operator+(const bigint& other) 
{   
    bigint result;
    if(is_negative ==other.is_negative) 
    {
        result = add(*this, other);

        result.is_negative = is_negative;
        return result;
    } else {
        // if signs are different, perform subtraction
        if (is_negative) 
        {
            bigint positive_this = negate(*this); 
            return other - positive_this;
        } 
        else 
        {
            bigint positive_other = negate(other); 
            return *this - positive_other;
        }
    }
}

bigint bigint::operator+=(const bigint& other)
{
    *this = *this + other;
    return *this;
}

bigint bigint::operator-(const bigint& other) 
{   
    bigint result;
    
    // same sign, subtration 
    if (is_negative == other.is_negative) 
    {
        if(*this < other) 
        {
            //use other to subtract this, set is_negative to true
            result = subtract(other, *this); 
            result.is_negative = true;

        } else {
             //use this to subtract other, set is_negative to false
            result = subtract(*this, other); 
            result.is_negative = false;
        }
    } else {     
        result = add(*this, other);
        result.is_negative = is_negative;
    
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
    bigint result = bigint(0);

    // If one of the numbers is zero, return zero
    if (digits.size() == 1 && digits[0] == 0 || other.digits.size() == 1 && other.digits[0] == 0)
    {
        return result;
    }

    for (size_t i = 0; i < digits.size(); i++) 
    {
        bigint temp; // Temporary bigint to store intermediate results
        uint8_t carry = 0;

        // Shift the digits in temp based on the current position in the first number
        for (size_t j = 0; j < i; j++) 
        {
            temp.digits.push_back(0); 
        }
        
        for (size_t j = 0; j < other.digits.size(); j++) 
        {
            uint16_t product = digits[i] * other.digits[j] + carry; 
            temp.digits.push_back(product % 10); 
            carry = product / 10; 
        }

        // for any carry left, add it to temp
        if (carry > 0) 
        {
            temp.digits.push_back(carry);
        }

        result = add(result, temp);
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












