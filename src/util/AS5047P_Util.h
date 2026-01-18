/**
 * @file AS5047P_Util.h
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @brief Utility helpers for the AS5047P library (bit parity, optional string utils).
 *
 * @version 3.0.1
 * @date 2026-01-18
 *
 * @copyright
 * Copyright (c) 2026 Jonas Merkle.
 * This project is released under the GPL-3.0 License.
 */

#ifndef AS5047P_Util_h
#define AS5047P_Util_h

#include <inttypes.h>

#include "./util/AS5047P_Settings.h"

#if defined(AS5047P_STD_STRING_SUPPORT)
#include <string>
#include <sstream>
#endif

/**
 * @namespace AS5047P_Util
 * @brief Utility functions for the AS5047P sensor.
 */
namespace AS5047P_Util
{

    /**
     * @brief Check whether a 16-bit value contains an even number of set bits (1s).
     *
     * Uses a sequence of XOR folds to reduce the word down to a single parity bit.
     *
     * @param data 16-bit input value.
     * @return true  if the number of set bits is even,
     * @return false if the number of set bits is odd.
     */
    static inline bool hasEvenNoOfBits(uint16_t data)
    {
        // Fold upper bits into lower bits; after these XORs, LSB holds parity.
        data ^= data >> 8;
        data ^= data >> 4;
        data ^= data >> 2;
        data ^= data >> 1;

        // If LSB == 0 ⇒ even parity; if LSB == 1 ⇒ odd parity.
        return ((~data) & 1u) != 0u;
    }

    /**
     * @brief Verify the parity bit of a 16-bit AS5047P frame.
     *
     * AS5047P frames use **even parity** over the lower 15 bits.
     * The MSB (bit 15) carries the parity bit, which must equal
     * `!hasEvenNoOfBits(lower15)` to ensure overall even parity.
     *
     * @param rawData 16-bit frame (bit 15 = parity, bits 0..14 = payload/flags).
     * @return true  if the parity bit matches the computed parity over bits 0..14,
     * @return false otherwise.
     */
    static inline bool parityCheck(uint16_t rawData)
    {
        const uint16_t lower15 = rawData & 0x7FFFu;
        const uint16_t parityBit = (rawData >> 15) & 0x1u; // MSB (bit 15)
        const uint16_t expected = static_cast<uint16_t>(!hasEvenNoOfBits(lower15));

        return parityBit == expected;
    }

#if defined(AS5047P_STD_STRING_SUPPORT)

    /**
     * @brief Lightweight replacement for std::to_string (works with streams).
     *
     * @tparam T Value type with stream insertion operator.
     * @param value The value to convert.
     * @return std::string String representation of the value.
     */
    template <typename T>
    std::string to_string(const T &value)
    {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }

#endif
} // namespace AS5047P_Util

#endif // AS5047P_Util_h
