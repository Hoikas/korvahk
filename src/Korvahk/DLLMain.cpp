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

#include "Plugin.h"

#ifdef _WIN32
#   define WIN32_LEAN_AND_MEAN
#   define NOMINMAX
#   include <windows.h>

BOOL APIENTRY DllMain(HINSTANCE hInst, DWORD reason, LPVOID reserved)
{
    switch (reason) {
    case DLL_PROCESS_DETACH:
        if (reserved != nullptr)
            break;
        Korvahk::Plugin::Shutdown();
        break;
    }
    return TRUE;
}

#define DLLEXPORT __declspec(dllexport) // TODO: use CMake for this
#endif // _WIN32

extern "C"
{
    DLLEXPORT void InitGlobals(
        Plasma::ResMgr* mgr,
        Plasma::Factory* factory,
        Plasma::TimerCallbackManager* timerCallbackMgr,
        Plasma::TimerShare* timer,
        Plasma::NetClientApp* netApp
    )
    {
        Korvahk::Plugin::Initialize(mgr, factory, timerCallbackMgr, timer, netApp);
    }
};
