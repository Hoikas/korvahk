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

#include <string_theory/format>

#include "Plasma/KeyedObject.h"
#include "Plasma/NetApp.h"
#include "Plasma/Types.h"

namespace Plasma
{
    class Factory;
    class ResMgr;
    class TimerCallbackManager;
    class TimerShare;
};

namespace Korvahk
{
    class Plugin : public Plasma::KeyedObject
    {
    private:
        Plasma::ResMgr* fResMgr;
        Plasma::Factory* fFactory;
        Plasma::TimerCallbackManager* fTimerCallbackMgr;
        Plasma::TimerShare* fTimer;
        Plasma::NetClientApp* fNetApp;

    private:
        Plugin(
            Plasma::ResMgr* mgr,
            Plasma::Factory* factory,
            Plasma::TimerCallbackManager* timerCallbackMgr,
            Plasma::TimerShare* timer,
            Plasma::NetClientApp* netApp
        );
        ~Plugin() override;

    private:
        void IInitKey();

    public:
        PLASMA_REFCOUNT_UNREF_SIGNATURE override
        {
            // This exists to ensure that all Korvahk objects are deleted in this DLL.
            // Otherwise, Plasma may try to delete them inside plClient.exe, which could
            // cause cross-CRT problems.
            int refs = --fRefCount;
            if (refs == 0)
                delete this;

            return refs;
        }

        Plasma::Boolean MsgReceive(Plasma::Message* msg);

    private:
        void ILog(const ST::string& msg) const
        {
#ifdef PLASMA_HAVE_STRING_THEORY
            fNetApp->Log(msg);
#else
            fNetApp->Log(msg.to_latin_1.data());
#endif
        }

    public:
        template<typename... _FmtArgs>
        void LogF(const char* fmt, _FmtArgs&&... args)
        {
            Log(ST::format(fmt, std::forward<_FmtArgs>(args)...));
        }

        void Log(const ST::string& msg) const
        {
            ILog(ST::format("<<< Korvahk >>> {}", msg));
        }

        template<size_t _Sz>
        void Log(const char msg[_Sz]) const
        {
            Log(ST::string::from_utf8(msg, _Sz));
        }

    public:
        static void Initialize(
            Plasma::ResMgr* mgr,
            Plasma::Factory* factory,
            Plasma::TimerCallbackManager* timerCallbackMgr,
            Plasma::TimerShare* timer,
            Plasma::NetClientApp* netApp
        );
    };
};
