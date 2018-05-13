#include "lucky.h"

#include <iostream>
#include <cstring>
#include <stdexcept>
#include <math.h>
using namespace std;

const string USAGE =
"USAGE: ./lucky [NUM] [OPTIONS]\n"
"Finds the NUMth Lucky number.\n"
"If no flags set, default is naive recursive formula.\n"
"  -d      Use dynamic programming.\n"
"  -g      Use Golden ratio formula.\n";

unsigned long lucky(unsigned long n)
{
    if (n == 0)
        return 2;
    if (n == 1)
        return 1;
    return lucky(n-1) + lucky(n-2);
}

unsigned long dp_lucky(unsigned long n)
{
    unsigned long dp[n+1];
    dp[0] = 2;
    dp[1] = 1;
    
    for(unsigned long j = 1; j < n; j++)
    {
        dp[j+1] = dp[j] + dp[j-1];
    }
    
    return dp[n];
}

float recpow(float x, unsigned long n)
{
    if (n == 0)
        return 1;
    if (n == 1)
        return x;
    
    float half = recpow(x, n/2);
    if (n % 2 == 1)
        return x*half*half;
    
    return half*half;
}

unsigned long gold_lucky(unsigned long n)
{
    float gold = (1 + sqrt(5))/2;
    return recpow(gold, n) + recpow(1 - gold, n);
}

int main(int argc, char** argv) {
    unsigned long n = 0;
    bool use_dp = false;
    bool use_gold = false;
    if (argc == 1) {
        cerr << USAGE << endl;
        return -1;
    }

    for (int i = 1; i < argc; i++) {
        /* Which lucky function do we use? Defaults to
           recursive formula if no flag specified, 
           and last flag if multiple flags set */
        if (strcmp(argv[i], "-d") == 0) {
            use_dp = true;
            use_gold = false;
        } else if (strcmp(argv[i], "-g") == 0) {
            use_gold = true;
            use_dp = false;
        } else {
            /* stoi() will except for non-numeric values. */
            try {
                n = stoul(argv[i]);
            } catch (invalid_argument& e) {
                cerr << USAGE << endl;
                return -1;
            } catch (out_of_range& e) {
                cerr << "Number too large to take as input." << endl;
                return -1;
            }
        }
    }
    /* Function pointer points to either the naive recursive, the
    dynamic programming, or the golden ratio function */
    unsigned long (*lucky_func)(unsigned long);
    if (use_gold) {
        lucky_func = gold_lucky;
    } else if (use_dp) {
        lucky_func = dp_lucky;
    } else {
        lucky_func = lucky;
    }

    unsigned long result = lucky_func(n);
    cout << result << endl;
    
    return 0;
}
