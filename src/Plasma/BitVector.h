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

namespace Plasma
{
    class BitVector
    {
        unsigned long* fBitVectors;
        unsigned long  fNumBitVectors;

    public:
        BitVector() {}
        virtual ~BitVector() {}

        bool operator [](size_t idx) const
        {
            return (fBitVectors[idx / 32] & (1 << (idx & 0x1F))) != 0;
        }
    };
};
