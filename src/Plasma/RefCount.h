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

#include <atomic>

#include "plConfig.h"

#ifdef PLASMA_ATOMIC_REFCOUNT
#   define PLASMA_REFCOUNT_UNREF_SIGNATURE int UnRef(const char* tag = nullptr)
#   define PLASMA_REFCOUNT_REF_SIGNATURE void Ref(const char* tag = nullptr)
#else
#   define PLASMA_REFCOUNT_UNREF_SIGNATURE int UnRef()
#   define PLASMA_REFCOUNT_REF_SIGNATURE void Ref()
#endif

namespace Plasma
{
    class RefCount
    {
    protected:
        // Variables
#ifdef PLASMA_ATOMIC_REFCOUNT
        std::atomic<int> fRefCount;
#else
        int fRefCount;
#endif

    public:
        // VFTable functions
        RefCount() : fRefCount(1) {}
        virtual ~RefCount() {}

        /**
         * \remarks This was renamed from `RefCount()` to prevent collisions with the ctor
         */
        virtual int GetRefCount() const
        {
            return fRefCount;
        }

        virtual PLASMA_REFCOUNT_UNREF_SIGNATURE
        {
            int refCount = --fRefCount;
            if (refCount == 0)
                delete this;
            return refCount;
        }

        virtual PLASMA_REFCOUNT_REF_SIGNATURE { fRefCount++; }
    };
};
