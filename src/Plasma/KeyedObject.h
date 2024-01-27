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

#include "Plasma/Key.h"
#include "Plasma/Message.h"

namespace Plasma
{
    class KeyedObject : public Receiver {
    protected:
        Key fpKey;

    public:
        PLASMA_CREATABLE_RW(KeyedObject)
        PLASMA_RECEIVER

        virtual void Validate();
        virtual bool IsFinal();
        virtual KeyedObject* GetSharedObject();
        virtual void SetKey(Key key)
        {
            fpKey = std::move(key);
            KeyImp::GetFromKey(fpKey)->fObjectPtr = this;
        }

    public:
        Key GetKey() const { return fpKey; }
    };
};
