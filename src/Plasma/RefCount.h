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
#include <type_traits>

#include "plConfig.h"

namespace Plasma
{
    class RefCount
    {
    protected:
#ifdef PLASMA_ATOMIC_REFCOUNT
        std::atomic<int> fRefCount;
#else
        int fRefCount;
#endif

    public:
        RefCount() : fRefCount(1) {}
        virtual ~RefCount() {}

        /**
         * \remarks This was renamed from `RefCount()` to prevent collisions with the ctor
         */
        virtual int GetRefCount() const { return fRefCount; }

#ifdef PLASMA_ATOMIC_REFCOUNT
        virtual int DecRef(const char* tag = nullptr)
        {
            int refCount = --fRefCount;
            if (refCount == 0)
                delete this;
            return refCount;
        }
#else

#endif

#ifdef PLASMA_ATOMIC_REFCOUNT
        virtual void IncRef(const char* tag = nullptr)
#else
        virtual void IncRef()
#endif
        {
            fRefCount++;
        }

#ifndef PLASMA_ATOMIC_REFCOUNT
        int DecRef(const char* tag) { DecRef(); }
        void IncRef(const char* tag) { IncRef(); }
#endif
    };

    struct Ref_NewType {};
    constexpr Ref_NewType NewRef{};

    template<typename _RefT>
    class Ref final
    {
        static_assert(std::is_base_of_v<RefCount, _RefT>);

        _RefT* fRef;

    public:
        Ref() : fRef() {}
        Ref(const Ref& r)
            : fRef(r.fRef)
        {
            if (fRef)
                fRef->Ref();
        }
        Ref(Ref&& r) : fRef(std::move(r.fRef)) {}
        Ref(_RefT* r) : fRef(r) {}
        Ref(_RefT* r, Ref_NewType)
            : fRef(r)
        {
            if (fRef)
                fRef->IncRef();
        }

        ~Ref()
        {
            if (fRef)
                fRef->DecRef();
        }

        _RefT* Get() const { return fRef; }

        _RefT* Release()
        {
            _RefT* ref = fRef;
            fRef = nullptr;
            return ref;
        }

        void Reset()
        {
            if (fRef) {
                fRef->DecRef();
                fRef = nullptr;
            }
        }

        _RefT* operator ->() const { return fRef; }
        operator bool() const { return fRef != nullptr; }

        void operator =(_RefT* r)
        {
            if (fRef)
                fRef->DecRef();
            fRef = r;
        }
    };
};
