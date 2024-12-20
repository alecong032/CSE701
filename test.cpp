#include <iostream>
#include "bigint.hpp"

int main() {

    //test constructor
    //normal case
    bigint test; //default
    bigint test1(390432434333344); //string
    bigint test2("-022394847493");   //string
    cout << "default: " << test << ", int:" << test1 << ", string:" << test2 << endl;
    

}