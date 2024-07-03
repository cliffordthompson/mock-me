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

#include <iostream>
#include "FunctionMocker.h"

#ifndef _WIN64
#error "Only Windows (64-bit) is currently supported." // __FUNCSIG__
#endif

void testFunc1(void)
{
    std::cout << "In " << __FUNCSIG__ << std::endl;
}

void mockFunc1(void)
{
    std::cout << "In " << __FUNCSIG__ << std::endl;
}

void mockFunc2(int param)
{
    std::cout << "In " << __FUNCSIG__ << std::endl;
}

int mockFunc3(void)
{
    std::cout << "In " << __FUNCSIG__ << std::endl;
    return 99;
}

void testFunc2(void)
{
    std::cout << "In " << __FUNCSIG__ << std::endl;
}

void testFunc3(int param)
{
    std::cout << "In " << __FUNCSIG__ << std::endl;
}

int testFunc4(void)
{
    std::cout << "In " << __FUNCSIG__ << std::endl;
    return 42;
}

int main()
{
    std::cout << "|------------- Testing basic function mocking -------------|" << std::endl;
    testFunc1();
    {
        FunctionMocker mocker(testFunc1, mockFunc1);
        testFunc1();
    }
    testFunc1();

    std::cout << "|----- Testing basic function mocking (ordering test) -----|" << std::endl;
    testFunc2();
    {
        FunctionMocker mocker(testFunc2, mockFunc1);
        testFunc2();
    }
    testFunc2();

    std::cout << "|------- Testing parameter passing function mocking -------|" << std::endl;
    testFunc3(1);
    {
        FunctionMocker mocker(testFunc3, mockFunc2);
        testFunc3(2);
    }
    testFunc3(3);

    std::cout << "|--------- Testing return value function mocking ----------|" << std::endl;
    int result = testFunc4();
    std::cout << "Return of testFunc4(" << result << ")" << std::endl;
    {
        FunctionMocker mocker(testFunc4, mockFunc3);
        result = testFunc4();
        std::cout << "Return of mocked testFunc4(" << result << ")" << std::endl;
    }
    result = testFunc4();
    std::cout << "Return of testFunc4(" << result << ")" << std::endl;
    return 0;
}
