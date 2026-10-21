#ifndef __CAPACITY_MODE_HPP__
#define __CAPACITY_MODE_HPP__

    #include <stdint.h>

    enum struct Capacity_Mode : uint8_t
    {
        STATIC = 0U,
        LINEAR = 1U,
        MULTIPLY = 2U,
        QUADRATIC = 3U
    };

#endif