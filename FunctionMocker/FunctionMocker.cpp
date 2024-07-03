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

#include <memoryapi.h>
#include <cassert>

#include "FunctionMocker.h"

FunctionMocker::FunctionMocker(void* originalFuncPtr, void* mockFuncPtr) :
    m_originalFuncPtr(static_cast<uint8_t*>(originalFuncPtr)),
    m_mockFuncPtr(static_cast<uint8_t*>(mockFuncPtr)),
    m_originalJmpOffsetPtr(reinterpret_cast<uint32_t*>(m_originalFuncPtr + 1)),
    m_mockJmpOffsetPtr(reinterpret_cast<uint32_t*>(m_mockFuncPtr + 1)),
    m_originalJmpOffsetValue(*m_originalJmpOffsetPtr)
{
    // Currently only supporting the E9 JMP instruction
    assert(*m_originalFuncPtr == JMP_OPCODE);
    assert(*m_mockFuncPtr == JMP_OPCODE);

    DWORD originalMemoryProtectionValue;
    VirtualProtect(m_originalJmpOffsetPtr, JMP_ADDRESS_LENGTH, PAGE_EXECUTE_READWRITE, &originalMemoryProtectionValue);

    const uint32_t addressDifference = m_mockFuncPtr - m_originalFuncPtr;
    *m_originalJmpOffsetPtr = *m_mockJmpOffsetPtr + addressDifference;

    // Return the memory protection to its previous state
    VirtualProtect(m_originalJmpOffsetPtr, JMP_ADDRESS_LENGTH, originalMemoryProtectionValue, &originalMemoryProtectionValue);
    return;
}

FunctionMocker::~FunctionMocker(void)
{
    DWORD originalMemoryProtectionValue;
    VirtualProtect(m_originalJmpOffsetPtr, JMP_ADDRESS_LENGTH, PAGE_EXECUTE_READWRITE, &originalMemoryProtectionValue);

    *m_originalJmpOffsetPtr = m_originalJmpOffsetValue;

    // Return the memory protection to its previous state
    VirtualProtect(m_originalJmpOffsetPtr, JMP_ADDRESS_LENGTH, originalMemoryProtectionValue, &originalMemoryProtectionValue);
    return;
}