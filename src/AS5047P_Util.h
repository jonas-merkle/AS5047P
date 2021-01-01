#ifndef AS5047P_Util_h
#define AS5047P_Util_h

#include <inttypes.h>

namespace AS5047P_Util {

    /**
     * Checks if two bytes have an even number of ones or not.
     * @param data The two bytes of data.
     * @return True if the number of ones in the data (including the parity bit!!! (which must not be set yet)) is even, else false.
     */
    static bool isEven(uint16_t data) {
        uint16_t shift = data >> 8;
        data ^= data >> 8;      // example for 8-bir (this line scales it up to 16 bit)
        data ^= data >> 4;      // ( a b c d e f g h ) xor ( 0 0 0 0 a b c d ) = ( a b c d ae bf cg dh )
        data ^= data >> 2;      // ( a b c d ae bf cg dh ) xor ( 0 0 a b c d ae bf ) = ( a b ac bd ace bdf aceg bdfh )
        data ^= data >> 1;      // ( a b ac bd ace bdf aceg bdfh ) xor ( 0 a b ac bd ace bdf aceg ) = ( a ab abc abcd abcde abcdef abcdefg abcdefgh )
        return (data) & 1;      // if lsb of data is 0 -> data is even. if lsb of data is 1 -> data is odd. Don't invert (~data) result because parity bit gets added afterwards.
    }
}

#endif // AS5047P_Util_h
