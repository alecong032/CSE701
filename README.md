# bigint: Arbitrary-Precision Integer Class

## Overview

The bigint class is designed to handle arbitrarily large integers and supports basic arithmetic operations (addition, subtraction, and multiplication) as well as comparison and negation. The implementation uses a std::vector<int8_t> `digits` to store individual digits of the integer, which enables efficient manipulation of very large numbers. The `is_negative` boolean value is used to store the sign of the bigint number.

## Internal Representation

- **Digits**: Stored as a `std::vector<int8_t>`. Each element representing a single digit of the number in reverse order (i.e., least significant digit at index 0).
- **Sign**: Stored as a `bool` (`is_negative`), where `true` indicates a negative number, and `false` indicates a positive number.

### Constructors

The `bigint` class includes three constructors:

1. **Default Constructor**:

   ```cpp
   bigint();
   ```
   Creates a `bigint` initialized to `0`.

2. **Integer Constructor**:

   ```cpp
   bigint(int64_t value);
   ```
   Converts a `signed 64-bit integer` to a `bigint`.

3. **String Constructor**:

   ```cpp
   bigint(const std::string& value);
   ```
   Converts a `string of digits` to a `bigint`.

### Supported Operators

1. **Arithmetic**:

   - **Addition:** `+`, `+=`
   - **Subtraction:** `-`, `-=`
   - **Multiplication:** `*`, `*=`

2. **Unary Negation**:

   - Negates the value with `-`.

3. **Comparison**:

   - **Equality:** `==`, `!=`
   - **Relational:**`<`, `>`, `<=`, `>=`

4. **Stream Insertion**:

   - Print the value using `<<`.

5. **Increment and Decrement**:
   - value++.
   - value--.

## Addition Logic

Addition involves summing two `bigint` numbers digit by digit. The helper function `add` contains the logic using long division to perform actual summing.

### Algorithm of operator+

1. **Same Sign Addition**:

   - If both numbers have the same sign, `add` function is called, their absolute values are added digit by digit.
   - A carry is propagated whenever the sum of two digits exceeds the base (10).

2. **Different Signs**:

   - If the numbers have different signs, the addition is converted to subtraction, the sign will be negated before passing into subtraction helper function:

        - num1+(−num2)=num1−num2
        - (−num1)+num2=num2−num1
     
3. **Carry Handling**:
   - When the sum of two digits exceeds the base (10), the carry is added to the next digit.

### Helper Function: `add`

The `add` function performs addition for only positive numbers, the logic for sign handling is in operator+

- removes leading zero introduced by constructor
- Iterates over the digits of both numbers and compute the following
    - sum = digit1 + digit2 + carry
    - result.digit = sum % base
    - carry=sum/base
- Stores the result in the `digits` vector of the resulting `bigint`.

---

## Subtraction Logic

Subtraction is performed by comparing the magnitudes of the numbers and subtracting their absolute values. The helper function `subtract` contains the logic using digit-by-digit subtraction.

### Algorithm

1. **Sign Handling**:

   - If the signs of the second numbers is negative, convert the subtraction into addition. Negated second number will be passed into `add` helper function. 
     - num1−(−num2)=num1+num2
     - −num1−(-num2)=−(num1+num2)

2. **Magnitude Comparison**:

   - If both numbers have the same sign, compare their magnitudes:
     - Subtract the smaller number from the larger one.
     - Assign the appropriate sign to the result.

3. **Borrow Handling**:

   - If a digit in the minuend is smaller than the corresponding digit in the subtrahend, borrow 10 from the next digit. This is handled in `subtract` helper function.

### Helper Function: `subtract`

The `subtract` function handles subtraction for positive numbers:

- If num2 is negative, the operation becomes an addition: num1 - (-num2) = num1 + num2
- Iterates over the digits of both numbers from least significant to most significant and compute the following:
    - diff=num1.digit−num2.digit+borrow
    - If diff is negative, borrow from the next digit:
        - diff=diff+10
        - borrow=−1
    - Append the computed diff to result.digits.
- Removes leading zeros from the result.
- If the result is exactly 0, set `is_negative = false` to ensure correct sign representation.
---

## Multiplication Logic

Multiplication uses the **long multiplication** method, which is similar to manual multiplication.

### Algorithm

1. **Zero Multiplication Check**:

   - If either number is zero, the result is zero.

2. **Digit-by-Digit Multiplication**:

   - For each digit in the first number, multiply it by every digit in the second number.
   - Store the partial results in a temporary `bigint`.

3. **Carry Handling**:

   - When the product of two digits exceeds the base (10), the carry is propagated to the next digit.

4. **Result Accumulation**:

   - Shift each partial result based on its position in the first number.
   - Add the shifted partial result to the final result.

5. **Sign Assignment**:
   - The result is negative if the signs of the two numbers differ.

---

# Example Outputs for `bigint` Operations

Below are detailed examples of operations performed on various input numbers using the `bigint` class. Each example demonstrates addition, subtraction, multiplication, negation, and comparison.

---

## Example 1: Large Positive Numbers

### Input

Number 1 = 1234567890123456789012345678901234567890
Number 2 = 9876543210987654321098765432109876543210

### Output

Addition + +=
Number 1 + Number 2 = 11111111101111111110111111111011111111100
Number 1 += Number 2 = 11111111101111111110111111111011111111100

Subtraction - -=
Number 1 - Number 2 = -8641975320864197532086419753208641975320
Number 1 -= Number 2 = -8641975320864197532086419753208641975320

Multiplication * *=
Number 1 _ Number 2 = 12193263113702179522618503273386678859448712086533622923332237463801111263526900
Number 1 *= Number 2 = 12193263113702179522618503273386678859448712086533622923332237463801111263526900

Negation -
Number 1 = -Number 1 = -1234567890123456789012345678901234567890

Comparison
Number 1 == Number 2 = 0
Number 1 != Number 2 = 1
Number 1 < Number 2 = 1
Number 1 <= Number 2 = 1
Number 1 > Number 2 = 0
Number 1 >= Number 2 = 0

## Example 2: Large Negative and Positive Numbers

### Input

- Number 1 = -9876543210987654321098765432109876543210
- Number 2 = 1234567890123456789012345678901234567890

### Output

Addition + +=
- Number 1 + Number 2 = -8641975320864197532086419753208641975320
- Number 1 += Number 2 = -8641975320864197532086419753208641975320

Subtraction - -=
- Number 1 - Number 2 = -11111111101111111110111111111011111111100
- Number 1 -= Number 2 = -11111111101111111110111111111011111111100

Multiplication * *=
- Number 1 * Number 2 = -12193263113702179522618503273386678859448712086533622923332237463801111263526900
- Number 1 *= Number 2 = -12193263113702179522618503273386678859448712086533622923332237463801111263526900

Negation -
- Number 1 = -Number 1 = 9876543210987654321098765432109876543210

Comparison
- Number 1 == Number 2 = 0
- Number 1 != Number 2 = 1
- Number 1 < Number 2 = 1
- Number 1 <= Number 2 = 1
- Number 1 > Number 2 = 0
- Number 1 >= Number 2 = 0

## Example 3: Equal Numbers

### Input

- Number 1 = 999
- Number 2 = 999

### Output

Addition + +=
- Number 1 + Number 2 = 1998
- Number 1 += Number 2 = 1998

Subtraction - -=
- Number 1 - Number 2 = 0
- Number 1 -= Number 2 = 0

Multiplication * *=
- Number 1 * Number 2 = 998001
- Number 1 *= Number 2 = 998001

Negation -
- Number 1 = -Number 1 = -999

Comparison
- Number 1 == Number 2 = 1
- Number 1 != Number 2 = 0
- Number 1 < Number 2 = 0
- Number 1 <= Number 2 = 1
- Number 1 > Number 2 = 0
- Number 1 >= Number 2 = 1


## Example 4: Increment and Decrement

### Input

- Number 1 = -10 

## Output

Post-increment
- Number 1++ = -10, Number 1 = -9 (increment on second call)

Post-decrement 
- Number 1-- = -10, Number 1 = -11 (decrement on second call)

Pre-increment 
- ++Number 1 = -9

pre-decrement 
- --Number1 = -11

