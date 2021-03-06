/*
    Fast exponentiation
    -------------------
    Given the base (B) and exponent (E), this algorithm efficiently calculates the
    value of B^E using the method of exponentiation by squaring, i.e, it sqaures
    the base and halves the exponent in each step, until the exponent becomes 0.

    Time complexity
    ---------------
    O(log(E)), where E is the exponent.

    Space complexity
    ----------------
    O(log(N)), where N is the exponent.

*/

#include <cmath>
#include <climits>
#include <iostream>

using namespace std;

typedef unsigned long long ULL;


/*
    digits_required
    ---------------
    Returns the number of digits in the result of B^E.
*/

ULL digits_required(const ULL& base, const ULL& exponent) {
    return floor(exponent * log10(base)) + 1;
}


/*
    square
    ------
    Returns the square of the value passed.
*/

ULL square(const ULL& value) {
    return value * value;
}


/*
    fast_exp
    --------
    Returns the value of the base raised to the exponent (B^E).
    The result is modulo the third parameter passed.

    NOTE: If the third parameter is not passed, it is assumed to be the maximum
    value of a 64-bit integer, and the exact value of the result is returned.
    In case the result cannot be contained in a 64-bit integer, the result is
    automatically modulo 10^9+7.
*/

ULL fast_exp(ULL base, ULL exponent, ULL mod = ULLONG_MAX) {
    if (exponent == 0)
        return 1;

    // if the result cannot be contained in a 64-bit integer, it will be
    // modulo 10^9+7 to prevent incorrect result due to integer overflow
    if (mod == ULLONG_MAX and digits_required(base, exponent) > 19)
        mod = 1000000007;

    if (exponent % 2)   // the exponent is odd
        return (fast_exp(base, exponent-1, mod) * base) % mod;

    // the exponent is even
    return square(fast_exp(base, exponent/2, mod)) % mod;
}


#ifndef FAST_EXPONENTIATION_TEST
int main() {
    ULL base;
    cout << "Enter the base : ";
    cin >> base;

    ULL exponent;
    cout << "Enter the exponent : ";
    cin >> exponent;

    string result;
    if (base == 0 and exponent == 0)
        result = "undefined";
    else {
        result = to_string(fast_exp(base, exponent));

        if (digits_required(base, exponent) > 19)
            // the result will be modulo 10^9+7 to prevent integer overflow
            result += " (modulo 10^9+7)";
    }
    cout << "\n" << base << "^" << exponent << " = " << result << "\n";

    return 0;
}
#endif
