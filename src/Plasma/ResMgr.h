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

#include "Plasma/Key.h"
#include "Plasma/RefCount.h"
#include "Plasma/Types.h"

namespace Plasma
{
    class Creatable;
    class DispatchBase;
    class KeyFinder;
    class KeyImp;
    class KeyedObject;
    class RefMsg;
    class Stream;

    class ResMgr : public RefCount
    {
    public:
        ResMgr() {};
        virtual ~ResMgr() {};

        virtual void Load(const Key&) = 0;
        virtual Boolean Unload(const Key&) = 0;

#ifdef PLASMA_TPOTS
        virtual void DoneLoading() = 0;
#endif

        virtual Key CloneKey(const Key&) = 0;

#ifdef PLASMA_TPOTS
        virtual Key NetClone(const Uoid&) = 0;
#endif

        virtual Key FindKey(const Uoid&) = 0;

#ifdef PLASMA_TPOTS
        virtual KeyFinder* GetKeyFinder() = 0;
#endif

        virtual Boolean AddViaNotify(RefMsg*, RefFlags::Type) = 0;
        virtual Boolean AddViaNotify(const Key&, RefMsg*, RefFlags::Type) = 0;

#ifdef PLASMA_TPOTS
        virtual Key ReadKeyNotifyMe(Stream*, RefMsg*, RefFlags::Type) = 0;
        virtual Key ReadKey(Stream*) = 0;
        virtual void WriteKey(Stream*, const Key&, unsigned char) = 0;
        virtual void WriteKey(Stream*, KeyedObject*, unsigned char) = 0;
#endif

        virtual Boolean SendRef(KeyedObject*, RefMsg*, RefFlags::Type) = 0;
        virtual Boolean SendRef(const Key&, RefMsg*, RefFlags::Type) = 0;

#ifdef PLASMA_MOUL
        virtual Key ReadKeyNotifyMe(Stream*, RefMsg*, RefFlags::Type) = 0;
        virtual Key ReadKey(Stream*) = 0;
        virtual void WriteKey(Stream*, const Key&, unsigned char) = 0;
        virtual void WriteKey(Stream*, KeyedObject*, unsigned char) = 0;
#endif

        virtual Creatable* ReadCreatable(Stream*) = 0;
        virtual void WriteCreatable(Stream*, Creatable*) = 0;
        virtual Creatable* ReadCreatableVersion(Stream*) = 0;
        virtual void WriteCreatableVersion(Stream*, Creatable*) = 0;
        virtual Key NewKey(Uoid&, KeyedObject*) = 0;
        virtual Key NewKey(ConstStringRef, KeyedObject*, const Location&, const LoadMask & = {}) = 0;

#ifdef PLASMA_TPOTS
        virtual Uoid* FindAlias(char const*, unsigned short) = 0;
        virtual void AddAlias(char const*, unsigned short, const Uoid&) = 0;
        virtual void RemoveAlias(char const*, unsigned short) = 0;
        virtual void Update() = 0;
        virtual void SaveState(Stream*) = 0;
        virtual void LoadState(Stream*) = 0;
        virtual void SaveResetState() = 0;
        virtual void LoadResetState() = 0;
#endif

        virtual DispatchBase* Dispatch() = 0;

#ifdef PLASMA_TPOTS
        virtual unsigned int GetNumKeysInLoc(const Location&) = 0;
        virtual unsigned int GetTotalLocSize(const Location&) = 0;
        virtual void SetProgressBarProc(void (*)(float, char const*)) = 0;
        virtual void IncProgressBar(float, char const*) = 0;
        virtual void PageInHoldList(char*) = 0;
        virtual void PageInHold(char*) = 0;
        virtual void GetPageVersion(unsigned short*, unsigned short*) = 0;
        virtual void VerifyAgeUnloaded(char const*, char const*);
#endif

        virtual void BeginShutdown() {};

#ifdef PLASMA_TPOTS
        virtual Key ReadKeyAndReg(Stream*) = 0;
#endif

        virtual Key ReRegister(char const*, const Uoid&) = 0;

#ifdef PLASMA_TPOTS
        virtual bool ReadObject(KeyImp*) = 0;
        virtual void IUnregistered(Key&) = 0;
        virtual void IRemoveKeyFromReg(KeyImp*) = 0;
#else
        virtual Boolean ReadObject(KeyImp*) = 0;
        virtual void IKeyReffed(KeyImp*) = 0;
        virtual void IKeyUnreffed(KeyImp*) = 0;
#endif

        virtual Boolean IReset() = 0;
        virtual Boolean IInit() = 0;
        virtual void IShutdown() = 0;
    };
};
