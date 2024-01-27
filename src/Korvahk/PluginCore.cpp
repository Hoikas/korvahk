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
#include "Plasma/Dispatch.h"
#include "Plasma/Message.h"
#include "Plasma/Pipeline.h"
#include "Plasma/ResMgr.h"

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

        Plasma::Creatable* Create() const override { return new Plugin(); };
        unsigned short ClassIndex() override { return Plugin::Index(); }
        const char* ClassName() const override { return "Korvahk::Plugin"; }
        Plasma::Boolean HasBaseClass(unsigned short hBase) override
        {
            constexpr unsigned short hKO = Plasma::KeyedObject::Index();
            if (hBase == hKO)
                return Plasma::True;
            return fFactory->GetCreator(hKO)->HasBaseClass(hBase);
        }
    };
};

// ==========================================================================

static std::unique_ptr<Korvahk::PluginCreator> s_creator;
static Plasma::Ref<Korvahk::Plugin> s_plugin;

// ==========================================================================

Plasma::Creatable* Korvahk::Plugin::GetInterface(unsigned short hClass)
{
    if (hClass == Index())
        return this;
    if (s_creator && s_creator->HasBaseClass(hClass))
        return this;
    return nullptr;
}

const Plasma::Creatable* Korvahk::Plugin::GetConstInterface(unsigned short hClass) const
{
    if (hClass == Index())
        return this;
    if (s_creator && s_creator->HasBaseClass(hClass))
        return this;
    return nullptr;
}

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
    IInitKey();
}

// ==========================================================================

void Korvahk::Plugin::IInitKey()
{
    Log("Creating plugin's Key...");
    Plasma::Location globalLoc{ Plasma::Location::kGlobalFixedLocIdx };
    Plasma::Key key = fResMgr->NewKey("Korvahk", this, globalLoc);
    Log("... Done!");
}

void Korvahk::Plugin::SetKey(Plasma::Key key)
{
    Plasma::KeyedObject::SetKey(std::move(key));

    fResMgr->Dispatch()->RegisterForExactType(Plasma::RenderMsg::Index(), GetKey());
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
    if (s_plugin) {
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

void Korvahk::Plugin::Shutdown()
{
    s_plugin->Log("Shutting down...");

    s_creator.reset();
    s_plugin.Reset();
}

// ==========================================================================

Plasma::Boolean Korvahk::Plugin::MsgReceive(Plasma::Message* msg)
{
    if (auto* pRenderMsg = fFactory->Convert<Plasma::RenderMsg>(msg)) {
        LogF("First render message received for {}", pRenderMsg->fPipeline->ClassName());
        fResMgr->Dispatch()->UnRegisterForExactType(Plasma::RenderMsg::Index(), GetKey());
        return Plasma::True;
    }

    return Plasma::False;
}
