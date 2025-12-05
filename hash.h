#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5] = {0, 0, 0, 0, 0};
        int len = static_cast<int>(k.size());
        int wIndex = 4;           
        int i = len - 1;          
        while(i >= 0 && wIndex >= 0)
        {
            unsigned long long value = 0;
            unsigned long long base  = 1;  

            for(int cnt = 0; cnt < 6 && i >= 0; ++cnt, --i)
            {
                char c = k[i];
                HASH_INDEX_T digit = letterDigitToNumber(c); 

                value += static_cast<unsigned long long>(digit) * base;
                base *= 36ULL;
            }

            w[wIndex] = value;
            --wIndex;
        }
        unsigned long long h = 0;
        for(int j = 0; j < 5; ++j)
        {
            h += static_cast<unsigned long long>(rValues[j]) * w[j];
        }
        return static_cast<HASH_INDEX_T>(h);

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if(letter >= 'A' && letter <= 'Z')
        {
            letter = letter - 'A' + 'a';
        }

        if(letter >= 'a' && letter <= 'z')
        {
            return static_cast<HASH_INDEX_T>(letter - 'a');
        }
        else if(letter >= '0' && letter <= '9')
        {
            return static_cast<HASH_INDEX_T>(26 + (letter - '0'));
        }
        else
        {
            return 0;
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
