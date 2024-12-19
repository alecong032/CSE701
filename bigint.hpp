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

    //helper functions
    bigint negate(const bigint &);             
private: 
    vector<uint8_t> digits;
    bool is_negative;


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


bigint bigint::operator+(const bigint& other) 
{   
    bigint result;
    if(is_negative ==other.is_negative) 
    {
        
        uint8_t carry = 0;

        size_t size1 = digits.size();
        size_t size2 = other.digits.size();
        size_t size = max(size1, size2);  //take the larger size for for loop 

        for(size_t i = 0; i < size; i++) {
            //if i exceeds the size of digits, set it to 0
            uint8_t digit1 = (i < size1) ? digits[i] : 0;       
            uint8_t digit2 = (i < size2) ? other.digits[i] : 0;

            uint8_t sum = digit1 + digit2 + carry; 
            result.digits.push_back(sum % 10);
            //prepare carry for next addition
            carry = sum / 10;
        }

        //push remaining carry to result
        if(carry > 0) {
            result.digits.push_back(carry);
        }

        result.is_negative = is_negative;
        return result;
    } else {
        if(is_negative)
        {
            bigint positive_this = *this;
            positive_this.is_negative = false;
            return other-positive_this;
        } else{
            bigint positive_other = other;
            positive_other.is_negative = false;
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
        } else {
             //use this to subtract other, set is_negative to false
        }
    } else {     
        //different sign, addition
    }
}













