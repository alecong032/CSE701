#include <vector>
#include <iostream>

using namespace std;

class bigint 
{
public: 
    bigint();
    bigint(int64_t);            // constructor for processing int64_t
    bigint(const string &);     // constructor for processing string

private: 
    vector<uint8_t> digits;
    bool is_negative;
};

bigint::bigint()
{
    digits = {0};
    is_negative = false;
}

bigint::bigint(int64_t num)
{

}