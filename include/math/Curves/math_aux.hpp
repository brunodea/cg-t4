#ifndef _BRUNODEA_MATH_AUX_HPP_
#define _BRUNODEA_MATH_AUX_HPP_

inline int factorial(unsigned int num)
{
    int result = 1;
    for(unsigned int i = 1; i <= num; i++)
        result *= i;
    return result;
}

#endif
