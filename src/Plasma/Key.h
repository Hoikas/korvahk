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

#include "Plasma/BitVector.h"
#include "Plasma/Types.h"

namespace Plasma
{
    class Location
    {
    public:
        enum LocFlags
        {
            kLocalOnly = 0x1,
            kVolatile = 0x2,
            kReserved = 0x4,
            kBuiltIn = 0x8,
            kItinerant = 0x10
        };

        enum
        {
            kGlobalFixedLocIdx = 0,
            kSceneViewerLocIdx = 1,
            kLocalLocStartIdx = 3,
            kLocalLocEndIdx = 0x20,
            kNormalLocStartIdx = 0x21,
            kReservedLocStart = 0xFF000000,
            kGlobalServerLocIdx = 0xFF000000,
            kReservedLocAvailableStart = 0xFF000001,
            kReservedLocEnd = 0xFFFFFFFE,
            kInvalidLocIdx = 0xFFFFFFFF
        };

    public:
        unsigned int fSequenceNumber;
        unsigned int fFlags;

    public:
        Location()
            : fSequenceNumber(kInvalidLocIdx),
              fFlags()
        { }
    };

    class LoadMask
    {
    public:
        enum
        {
            kMaxCap = 0x1,
        };

    public:
        union {
            unsigned char fQuality[2];
            unsigned short fMask;
        };

    public:
        LoadMask() : fMask(0xFFFF) { }
    };

    class NetGroupId
    {
    public:
        enum NetGroupConstants
        {
            kNetGroupConstant = 0x1,
            kNetGroupLocal = 0x2
        };

        Location fId;
        unsigned char fFlags;
        LegacyStdString fDesc;
    };

    class Key
    {
    public:
        class KeyData* fKeyData;

    public:
        Key() : fKeyData() { }

        operator bool() const { return fKeyData != nullptr; }
        KeyData* operator ->() const { return fKeyData; }
        KeyData& operator *() const { return *fKeyData; }
    };

    enum FixedKeyId
    {
        kFirst_Fixed_KEY, kLOSObject_KEY, kTimerCallbackManager_KEY,
        kConsoleObject_KEY, kAudioSystem_KEY, kInput_KEY, kClient_KEY,
        kNetClientMgr_KEY, kListenerMod_KEY, kTransitionMgr_KEY,
        kLinkEffectsMgr_KEY, kGameGUIMgr_KEY, kGameGUIDynamicDlg_KEY,
        kVirtualCamera1_KEY, kDefaultCameraMod1_KEY, kKIGUIGlue_KEY,
        kClothingMgr_KEY, kInputInterfaceMgr_KEY, kAVIWriter_KEY,
        kResManagerHelper_KEY, kAvatarMgr_KEY, kSimulationMgr_KEY,
        kTransitionCamera_KEY, kCCRMgr_KEY, kNetClientCloneRoom_KEY,
        kMarkerMgr_KEY, kAutoProfile_KEY, kGlobalVisMgr_KEY, kFontCache_KEY,
        kRelevanceMgr_KEY, kJournalBookMgr_KEY, kAgeLoader_KEY,
        kBuiltIn3rdPersonCamera_KEY, kSecurePreloader_KEY, kLast_Fixed_KEY,
    };

    struct KeySeed
    {
        FixedKeyId feFixedKey;
        unsigned short fType;
        const char* fObj;
    };

    static const KeySeed SeedList[] = {
        { kFirst_Fixed_KEY, 0x0001, "kFirst_Fixed_KEY" },
        { kLOSObject_KEY, 0x00F8, "kLOSObject_KEY" },
        { kTimerCallbackManager_KEY, 0x0033, "kTimerCallbackManager_KEY" },
        { kConsoleObject_KEY, 0x0252, "kConsoleObject_KEY" },
        { kAudioSystem_KEY, 0x004B, "kAudioSystem_KEY" },
        { kInput_KEY, 0x004E, "kInput_KEY" },
        { kClient_KEY, 0x005B, "kClient_KEY" },
        { kNetClientMgr_KEY, 0x0052, "kNetClientMgr_KEY" },
        { kListenerMod_KEY, 0x0063, "kListenerMod_KEY" },
        { kTransitionMgr_KEY, 0x0080, "kTransitionMgr_KEY" },
        { kLinkEffectsMgr_KEY, 0x0083, "kLinkEffectsMgr_KEY" },
        { kGameGUIMgr_KEY, 0x0097, "kGameGUIMgr_KEY" },
        { kGameGUIDynamicDlg_KEY, 0x0000, "kGameGUIDynamicDlg_KEY" },
        { kVirtualCamera1_KEY, 0x009A, "kVirtualCamera_KEY" },
        { kDefaultCameraMod1_KEY, 0x009B, "kDefaultCameraMod1_KEY" },
#if defined(PLASMA_MOUL)
        { kKIGUIGlue_KEY, 0x034F, "kKIGUIGlue_KEY" },
#elif defined(PLASMA_TPOTS)
        { kKIGUIGlue_KEY, 0x034A, "kKIGUIGlue_KEY" },
#else
#   error "Unsupported Plasma version"
#endif
        { kClothingMgr_KEY, 0x00B8, "kClothingMgr_KEY" },
        { kInputInterfaceMgr_KEY, 0x00BF, "kInputInterfaceMgr_KEY" },
        { kAVIWriter_KEY, 0x00C7, "kAVIWriter_KEY" },
        { kResManagerHelper_KEY, 0x00E1, "kResManagerHelper_KEY" },
        { kAvatarMgr_KEY, 0x00F4, "kAvatarMgr_KEY" },
        { kSimulationMgr_KEY, 0x00FA, "kSimulationMgr_KEY" },
        { kTransitionCamera_KEY, 0x009B, "kTransitionCamera_KEY" },
        { kCCRMgr_KEY, 0x0100, "kCCRMgr_KEY" },
        { kNetClientCloneRoom_KEY, 0x0000, "kNetClientCloneRoom_KEY" },
        { kMarkerMgr_KEY, 0x00CE, "kMarkerMgr_KEY" },
        { kAutoProfile_KEY, 0x00C5, "kAutoProfile_KEY" },
        { kGlobalVisMgr_KEY, 0x0117, "kGlobalVisMgr_KEY" },
        { kFontCache_KEY, 0x011D, "kFontCache_KEY" },
        { kRelevanceMgr_KEY, 0x011F, "kRelevanceMgr_KEY" },
        { kJournalBookMgr_KEY, 0x0120, "kJournalBookMgr_KEY" },
        { kAgeLoader_KEY, 0x0125, "kAgeLoader_KEY" },
        { kBuiltIn3rdPersonCamera_KEY, 0x009B, "kBuiltIn3rdPersonCamera_KEY" },
        { kLast_Fixed_KEY, 0x0001, "kLast_Fixed_KEY" }
    };

    class Uoid
    {
    public:
        enum ContentsFlags
        {
            kHasCloneIDs = 0x1,
            kHasLoadMask = 0x2,
        };

    public:
#if defined(PLASMA_MOUL)
        unsigned long fObjectID;
        unsigned long fClonePlayerID;
        unsigned short fCloneID;
        unsigned short fClassType;
        String fObjectName;
        Location fLocation;
        LoadMask fLoadMask;
#elif defined(PLASMA_TPOTS)
        plLocation fLocation;
        plLoadMask fLoadMask;
        unsigned short fClassType;
        char* fObjectName;
        unsigned int fClonePlayerID, fCloneID;
#else
#   error "unsupported Plasma version"
#endif

        Uoid()
        {
#ifdef PLASMA_MOUL
            fObjectID = 0;
#endif
            fClonePlayerID = 0;
            fCloneID = 0;
            fClassType = 0;
        }

        Uoid(FixedKeyId id)
        {
#ifdef PLASMA_MOUL
            fObjectID = 0;
#endif
            fCloneID = 0;
            fClonePlayerID = 0;
            const KeySeed& seed = SeedList[id];
            fClassType = seed.fType;
            fObjectName = StrDup(seed.fObj);
        }

        ~Uoid()
        {
            StrDelete(fObjectName);
        }
    };

    namespace RefFlags
    {
        enum Type { kActiveRef, kPassiveRef };
    };

    class KeyData
    {
    private:
        unsigned short fRefCount;

    public:
        virtual Uoid const& GetUoid() const = 0;
        virtual String GetName() const = 0;
        virtual class KeyedObject* GetObjectPtr() = 0;
        virtual class KeyedObject* ObjectIsLoaded() const = 0;
        virtual class KeyedObject* VerifyLoaded() = 0;
        virtual class KeyedObject* RefObject(RefFlags::Type) = 0;
        virtual void UnRefObject(RefFlags::Type) = 0;
        virtual void Release(Key) = 0;
        virtual unsigned short GetActiveRefs() const = 0;
        virtual unsigned short GetNumNotifyCreated() const = 0;
        virtual class RefMsg* GetNotifyCreated(int) const = 0;
        virtual BitVector& GetActiveBits() const = 0;

        KeyData() : fRefCount() { }
        virtual ~KeyData(){}
    };
};
