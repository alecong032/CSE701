# bigint: Arbitrary-Precision Integer Class

## Overview

`bigint` is a C++ class that handle large numbers. It is implemented with vector. 


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

### Helper functions
 - negate
   - add
   - subtract
   - is_smaller

### Supported Operators

1. **Arithmetic**:
   - Addition: `+`, `+=`
   - Subtraction: `-`, `-=`
   - Multiplication: `*`, `*=`

2. **Unary Negation**:
   - Negates the value with `-`.

3. **Comparison**:
   - Equality: `==`, `!=`
   - Relational: `<`, `>`, `<=`, `>=`

4. **Stream Insertion**:
   - Print the value using `<<`.

5. **Increment and Decrement**:
   - Pre-increment (`++value`) and post-increment (`value++`).
   - Pre-decrement (`--value`) and post-decrement (`value--`).


## Internal Representation

- `bigint` uses a `std::vector<int8_t>` to store digits in **little-endian** order, where the least significant digit is at the start of the vector.
- The `bool is_negative` member tracks whether the number is negative.
- Helper functions ensure consistent handling of addition, subtraction, and negation.

## Limitations

- Only base-10 arithmetic is supported.
- Performance depends on the number of digits; operations on very large numbers can be slow.
- some error during conconsistancy check
- increment and decrement does not pass test

## Testing

The accompanying `test.cpp` thoroughly validates all functionality of the `bigint` class. It includes:

- Constructor tests for various inputs.
- Arithmetic tests for addition, subtraction, and multiplication.
- Comparison tests to verify relational operators.
- Increment and decrement tests.

Run the test suite to ensure correctness:
```bash
./test
```

## License

This project is provided as-is, without any specific license. Feel free to modify and use it for educational purposes.

