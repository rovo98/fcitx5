/*
 * Copyright (C) 2016~2016 by CSSlayer
 * wengxt@gmail.com
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see the file COPYING. If not,
 * see <http://www.gnu.org/licenses/>.
 */

#include "dbusmodule.h"
#include "fcitx-utils/dbus.h"
#include "fcitx/addonmanager.h"

#define FCITX_CONTROLLER_DBUS_INTERFACE "org.fcitx.Fcitx.Controller1"

using namespace fcitx::dbus;

namespace fcitx
{

class Controller : public ObjectVTable {
public:
    void exit();
    void restart();
    void configure();
    void configureAddon(const std::string &addon);
    void configureInputMethod(const std::string &imName);
    std::string currentUI();
    std::string addonForInputMethod(const std::string &imName);
    void activate();
    void deactivate();
    void toggle();
    void resetInputMethodList();
    int state();
    void reloadConfig();
    void reloadAddonConfig(const std::string &addonName);
    std::string currentInputMethod();
    void setCurrentInputMethod(std::string imName);

private:
    FCITX_OBJECT_VTABLE_METHOD(exit, "Exit", "", "");
    FCITX_OBJECT_VTABLE_METHOD(restart, "Restart", "", "");
    FCITX_OBJECT_VTABLE_METHOD(configure, "Configure", "", "");
    FCITX_OBJECT_VTABLE_METHOD(configureAddon, "ConfigureAddon", "s", "");
    FCITX_OBJECT_VTABLE_METHOD(configureInputMethod, "ConfigureIM", "s", "");
    FCITX_OBJECT_VTABLE_METHOD(currentUI, "CurrentUI", "", "s");
    FCITX_OBJECT_VTABLE_METHOD(addonForInputMethod, "AddonForIM", "s", "s");
    FCITX_OBJECT_VTABLE_METHOD(activate, "Activate", "", "");
    FCITX_OBJECT_VTABLE_METHOD(toggle, "Toggle", "", "");
    FCITX_OBJECT_VTABLE_METHOD(resetInputMethodList, "ResetIMList", "", "");
    FCITX_OBJECT_VTABLE_METHOD(state, "State", "", "i");
    FCITX_OBJECT_VTABLE_METHOD(reloadConfig, "ReloadConfig", "", "");
    FCITX_OBJECT_VTABLE_METHOD(reloadAddonConfig, "ReloadAddonConfig", "s", "");
    FCITX_OBJECT_VTABLE_METHOD(currentInputMethod, "CurrentInputMethod", "", "s");
    FCITX_OBJECT_VTABLE_METHOD(setCurrentInputMethod, "SetCurrentIM", "s", "");
};

DBusModule::DBusModule(Instance *instance) : m_bus(std::make_unique<dbus::Bus>(dbus::BusType::Session)) {
    m_bus->attachEventLoop(instance->eventLoop());
    if (!m_bus->requestName(FCITX_CONTROLLER_DBUS_INTERFACE, Flags<RequestNameFlag>{RequestNameFlag::AllowReplacement, RequestNameFlag::ReplaceExisting})) {
        throw std::runtime_error("Unable to request dbus name");
    }
    // m_bus->addObject();
}

AddonInstance *DBusModuleFactory::create(AddonManager *manager)
{
    return new DBusModule(manager->instance());
}


}
