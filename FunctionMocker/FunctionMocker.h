// ----------------------------------------------------------------------------
//
// Copyright(c) 2024 Clifford Thompson
//
// This program is free software : you can redistribute it and /or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.If not, see < http://www.gnu.org/licenses/>.
//
// ---------------------------------------------------------------------------

#ifndef _FUNCTIONMOCKER_H_
#define _FUNCTIONMOCKER_H_

#include <cstdint>

#ifndef _DEBUG
#error "Only debug builds currently supported."
#endif

#ifndef _WIN64
#error "Only Windows (64-bit) is currently supported."
#endif

#ifndef _AMD64_
#error "Only x64 builds currently currently supported."
#endif

class FunctionMocker
{
public:
    FunctionMocker(void* originalFuncPtr, void* mockFuncPtr);
    ~FunctionMocker(void);

private:
    FunctionMocker(FunctionMocker&) = delete;
    FunctionMocker(FunctionMocker&&) = delete;
    FunctionMocker& operator=(const FunctionMocker&) = delete;
    FunctionMocker& operator=(const FunctionMocker&&) = delete;

    uint8_t* const m_originalFuncPtr;
    uint8_t* const m_mockFuncPtr;

    // For now, only the E9 JMP instruction:
    // |--------------------------------|
    // | E9 (1-byte) | offset (4-bytes) |
    // |--------------------------------|
    static const uint8_t JMP_OPCODE = 0xe9;
    static const uint8_t JMP_ADDRESS_LENGTH = sizeof(uint32_t);

    // Pointers to the offsets for the JMPO instruction
    uint32_t* const m_originalJmpOffsetPtr;
    uint32_t* const m_mockJmpOffsetPtr;

    uint32_t m_originalJmpOffsetValue = { 0 };
};

#endif _FUNCTIONMOCKER_H_