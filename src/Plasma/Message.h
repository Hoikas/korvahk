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

#include <vector>

#include "Plasma/Creatable.h"
#include "Plasma/Key.h"

namespace Plasma
{
    class Message;
};

#define PLASMA_RECEIVER \
    virtual Plasma::Boolean MsgReceive(Plasma::Message*);

namespace Plasma
{
    class Receiver : public Creatable
    {
    public:
        PLASMA_CREATABLE(Receiver)
        PLASMA_RECEIVER
    };

    class Message : public Creatable
    {
    public:
        enum BCastFlags {
            kBCastNone = 0,
            kBCastByType = 0x1,
            kBCastUNUSED_0 = 0x2,
            kPropagateToChildren = 0x4,
            kBCastByExactType = 0x8,
            kPropagateToModifiers = 0x10,
            kClearAfterBCast = 0x20,
            kNetPropagate = 0x40,
            kNetSent = 0x80,
            kNetUseRelevanceRegions = 0x100,
            kNetForce = 0x200,
            kNetNonLocal = 0x400,
            kLocalPropagate = 0x800,
            kNetNonDeterministic = 0x200,
            kMsgWatch = 0x1000,
            kNetStartCascade = 0x2000,
            kNetAllowInterAge = 0x4000,
            kNetSendUnreliable = 0x8000,
            kCCRSendToAllPlayers = 0x10000,
            kNetCreatedRemotely = 0x20000,
        };

    private:
#ifdef PLASMA_MOUL
        bool dispatchBreak;
#endif
    public:
        Key fSender;
        TArray<Key> fReceivers;
        double fTimeStamp;
        unsigned int fBCastFlags;
        StlVector<unsigned int>* fNetRcvrPlayerIDs;

    public:
        PLASMA_CREATABLE(Message)
    };

    class ProxyDrawMsg : public Message
    {
    public:
        enum
        {
            kCreate = 0x1,
            kDestroy = 0x2,
            kDetach = 0x4,
            kToggle = 0x8,
            kLight = 0x10,
            kPhysical = 0x20,
            kOccluder = 0x40,
            kAudible = 0x80,
            kCoordinate = 0x100,
            kCamera = 0x200,
            kAllTypes = 0x3F0,
        };

    public:
        unsigned short fProxyFlags;

    public:
        PLASMA_CREATABLE(ProxyDrawMsg)
    };

    class RenderMsg : public Message
    {
    public:
        class Pipeline* fPipeline;

    public:
        PLASMA_CREATABLE_RW(RenderMsg)
    };
};
