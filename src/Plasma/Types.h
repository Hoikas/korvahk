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

#include <algorithm>
#include <string>
#include <string_theory/string>
#include <type_traits>

namespace Plasma
{
#ifdef PLASMA_WIN32_BOOLS
    using Boolean = int;
    static constexpr Boolean True = 1;
    static constexpr Boolean False = 0;
#else
    using Boolean = bool;
    static constexpr Boolean True = true;
    static constexpr Boolean False = false;
#endif

#ifdef PLASMA_HAVE_STRING_THEORY
    using String = ST::string;
    using ConstStringRef = const ST::string&;
    using LegacyStdString = ST::string;
#else
    using String = char*;
    using ConstStringRef = const char*;
    using LegacyStdString = std::string;
#endif

    template<bool _IsST = std::is_same_v<String, ST::string>>
    inline void StrNull(String& str) noexcept
    {
        if constexpr (_IsST) {
            str = ST::string{};
        } else {
            str[0] = 0;
        }
    }

    template<typename _SrcT, typename _DestT>
    inline void StrCopy(const _SrcT& src, _DestT dest) noexcept
    {
        static_assert(std::is_nothrow_convertible_v<_SrcT, String>, "src must be a string");
        static_assert(std::is_nothrow_convertible_v<_DestT, String>, "dest must be a string");

        if constexpr (std::is_same_v<String, ST::string>) {
            dest = src;
        } else if constexpr (std::is_bounded_array_v<_SrcT> && std::is_bounded_array_v<_DestT>) {
            size_t arrSize = std::min(std::size(src), std::size(dest));
            if (arrSize != 0)
                arrSize -= 1;
            std::char_traits::copy(dest, src, arrSize);
            src[arrSize] = 0;
        } else if constexpr (std::is_bounded_array_v<_SrcT>) {
            std::char_traits::copy(dest, src, std::size(src) - 1);
            dest[std::size(src) - 1] = 0;
        } else if constexpr (std::is_bounded_array_v<_DestT>) {
            size_t len = std::min(std::char_traits::length(src), std::size(dest) - 1);
            std::char_traits::copy(dest, src, len);
            dest[len] = 0;
        } else {
            throw "junk";
        }
    }

    template<bool _IsST = std::is_same_v<String, ST::string>>
    inline void StrDelete(String& str) noexcept
    {
        if constexpr (!_IsST) {
            delete[] str;
            str = nullptr;
        }
    }

    template<bool _IsST = std::is_same_v<String, ST::string>>
    inline String StrDup(const String& str)
    {
        if constexpr (_IsST) {
            return str;
        } else {
            using _CharT = std::remove_pointer_t<String>;
            size_t len = std::char_traits<_CharT>::length(str);
            String dest = new _CharT[len + 1];
            std::char_traits<_CharT>::copy(dest, str, len);
            dest[len] = 0;
            return dest;
        }
    }
};
