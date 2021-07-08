#include <stdint.h>
#include <iostream>
#include <stdio.h>

float f(float x) 
{.
    int i = (int)*&x;
    i = 0x5f3759df - (i >> 1);  
    i = i >> 2;
    

    return i;
}

int main() {
    float value = 1;

    int result  = f(value);
    std::cout << result << std::endl;
}