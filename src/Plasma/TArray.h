/* This file is part of Korvahk.
 *
 * Korvahk is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Korvahk is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Korvahk.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "plConfig.h"

#include <vector>

namespace Plasma
{
    // Assumption: `std::vector` is basically always ABI compatible.
    // This seems fairly reasonable, but let's make this a type
    // so we can re-implement a "vector" for whatever MSVC we need to,
    // if it comes to that.
    template<typename T>
    using StlVector = std::vector<T>;

#ifdef PLASMA_TARRAY_IS_VECTOR
    template<typename T>
    using TArray = StlVector<T>;
#else
    template<typename T>
    class TArray
    {
        // Variables
        unsigned short fUseCount, fTotalCount;
        _T* fArray;

    public:
        // Functions
        hsTArray() : fUseCount(), fTotalCount(), fArray() {}
        ~hsTArray<T>() {}

        T* operator[] (size_t idx) const
        {
            return fArray[idx];
        }
    };
#endif
};
