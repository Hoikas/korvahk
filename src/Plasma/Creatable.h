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

#include <type_traits>

#include "Plasma/CreatableIDs.h"
#include "Plasma/RefCount.h"
#include "Plasma/TArray.h"
#include "Plasma/Types.h"

namespace Plasma
{
    class ResMgr;
    class Stream;
};

#define PLASMA_CREATABLE(name) \
    static constexpr unsigned short Index() { return Plasma::k##name; } \
    \
    name() {} \
    virtual ~name() {} \
    \
    virtual const char* ClassName() const; \
    virtual Plasma::Creatable* GetInterface(unsigned short idx); \
    virtual const Plasma::Creatable* GetConstInterface(unsigned short idx) const; \
    virtual unsigned short ClassIndex() const;

#define PLASMA_CREATABLE_RW(name) \
    PLASMA_CREATABLE(name) \
    virtual void Read(Plasma::Stream*, Plasma::ResMgr*); \
    virtual void Write(Plasma::Stream*, Plasma::ResMgr*);

#define PLASMA_CREATABLE_RWVER(name) \
    PLASMA_CREATABLE_RW(name) \
    virtual void ReadVersion(Plasma::Stream*, Plasma::ResMgr*); \
    virtual void WriteVersion(Plasma::Stream*, Plasma::ResMgr*);

namespace Plasma
{
    class Creatable : public RefCount
    {
    public:
        PLASMA_CREATABLE_RWVER(Creatable)
    };

    class Creator
    {
    public:
        Creator() {};
        virtual ~Creator() {};

        virtual Creatable* Create() const = 0;
        virtual unsigned short ClassIndex() = 0;
        virtual char const* ClassName() const = 0;
        virtual Boolean HasBaseClass(unsigned short hBase) = 0;
    };

    class Factory : public RefCount
    {
        TArray<Creator*> fCreators;

    public:
        Factory() {};
        virtual ~Factory() {};

        template<typename T>
        T* Create()
        {
            static_assert(std::is_base_of_v<Creatable, T>, "Can only create Creatables");
            return fCreators[T::Index()]->Create();
        }

        void Register(Creator* worker)
        {
            Ref();
            fCreators[worker->ClassIndex()] = worker;
        }

        void UnRegister(Creator* worker)
        {
            fCreators[worker->ClassIndex()] = nullptr;
            UnRef();
        }

        Creator* GetCreator(unsigned short hClass) const
        {
            return fCreators[hClass];
        }

        template<typename T>
        T* Convert(Creatable* pCre) const
        {
            static_assert(std::is_base_of_v<Creatable, T>, "pCre can only be a Creatable");

            unsigned short pCreIdx = pCre->ClassIndex();
            if (pCreIdx == T::Index())
                return static_cast<T*>(pCre);
            if (fCreators[pCreIdx]->HasBaseClass(T::Index()))
                return static_cast<T*>(pCre);
            return nullptr;
        }
    };
};
