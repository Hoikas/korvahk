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

#include "Plasma/Creatable.h"
#include "Plasma/Types.h"

namespace Plasma
{
    class Key;
    class Message;

    class DispatchBase : public Creatable
    {
    public:
        PLASMA_CREATABLE(DispatchBase)

        virtual void RegisterForType(unsigned short, const Key&) = 0;
        virtual void RegisterForExactType(unsigned short, const Key&) = 0;
        virtual void UnRegisterForType(unsigned short, const Key&) = 0;
        virtual void UnRegisterForExactType(unsigned short, const Key&) = 0;
        virtual void UnRegisterAll(const Key&) = 0;
        virtual Boolean MsgSend(Message*, Boolean) = 0;
        virtual void MsgQueue(Message*) = 0;
        virtual void MsgQueueProcess() = 0;
        virtual void MsgQueueOnOff(Boolean) = 0;
        virtual Boolean SetMsgBuffering(Boolean) = 0;
    };
};
