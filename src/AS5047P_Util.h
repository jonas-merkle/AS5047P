#ifndef AS5047P_Util_h
#define AS5047P_Util_h

#include <inttypes.h>

namespace AS5047P_Util {

    /**
     * Checks if two bytes have an even number of ones or not.
     * @param data The two bytes of data.
     * @return True if the number of ones in the data is even, else false.
     */
    static bool isEven(uint16_t data);
}

#endif // AS5047P_Util_h