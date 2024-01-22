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

#include <memory>

#include "Plasma/Creatable.h"

// ==========================================================================

static constexpr unsigned short kKorvahkPluginID = 500;

// ==========================================================================

namespace Korvahk
{
    class PluginCreator : public Plasma::Creator
    {
        Plasma::Factory* fFactory;

    public:
        PluginCreator(Plasma::Factory* f) : fFactory(f)
        {
            fFactory->Register(this);
        }

        ~PluginCreator()
        {
            fFactory->UnRegister(this);
        }

        Plasma::Creatable* Create() const override { return nullptr; };
        unsigned short ClassIndex() override { return kKorvahkPluginID; }
        const char* ClassName() const override { return "Korvahk::Plugin"; }
        Plasma::Boolean HasBaseClass(unsigned short hBase) override
        {
            if (hBase == Plasma::kKeyedObject)
                return Plasma::True;
            return fFactory->GetCreator(Plasma::kKeyedObject)->HasBaseClass(hBase);
        }
    };
};

// ==========================================================================

static std::unique_ptr<Korvahk::PluginCreator> s_creator;
static Korvahk::Plugin* s_plugin{};

// ==========================================================================

Korvahk::Plugin::Plugin(
    Plasma::ResMgr* mgr,
    Plasma::Factory* factory,
    Plasma::TimerCallbackManager* timerCallbackMgr,
    Plasma::TimerShare* timer,
    Plasma::NetClientApp* netApp
)
    : fResMgr(mgr),
      fFactory(factory),
      fTimerCallbackMgr(timerCallbackMgr),
      fTimer(timer),
      fNetApp(netApp)
{
    Log("I'm back! ... in the saddle again...");
}

Korvahk::Plugin::~Plugin()
{
    s_plugin = nullptr;
}

// ==========================================================================

void Korvahk::Plugin::Initialize(
    Plasma::ResMgr* mgr,
    Plasma::Factory* factory,
    Plasma::TimerCallbackManager* timerCallbackMgr,
    Plasma::TimerShare* timer,
    Plasma::NetClientApp* netApp
)
{
    if (s_plugin != nullptr) {
        s_plugin->Log("Duplicate call to Plugin::Initialize() debounced!");
        return;
    }

    // Register our external creatable with the Plasma factory
    // so that life doesn't get too weird. Any attempts for
    // the engine to create the plugin will fail.
    s_creator = std::make_unique<PluginCreator>(factory);

    // The plugin constructor will carry forward from here.
    s_plugin = new Plugin(mgr, factory, timerCallbackMgr, timer, netApp);
    s_plugin->Log("Plugin::Initialize() complete!");
}
