// Copyright (C) 2019 Luxoft Sweden AB
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#ifndef TEMPLATE_DBUS_SERVICE_DAEMON_DBUS_SERVICE_H
#define TEMPLATE_DBUS_SERVICE_DAEMON_DBUS_SERVICE_H

#include <glibmm.h>

#include "generated/dbus/template_common.h"
#include "generated/dbus/template_stub.h"

namespace TemplateDBusService::Daemon
{
    class DBusService
    {
    public:
        explicit DBusService(const Glib::RefPtr<Glib::MainLoop> &main_loop);
        ~DBusService();

        DBusService(const DBusService &other) = delete;
        DBusService(DBusService &&other) = delete;
        DBusService &operator=(const DBusService &other) = delete;
        DBusService &operator=(DBusService &&other) = delete;

        void own_name();
        void unown_name();

    private:
        class Template : public com::luxoft::TemplateStub
        {
        public:
            void RemoveMeFoo(guint32 number, MethodInvocation &invocation) override;

            bool RemoveMeBaz_setHandler(bool value) override;
            bool RemoveMeBaz_get() override;

        private:
            bool remove_me_baz_ = false;
        };

        void bus_acquired(const Glib::RefPtr<Gio::DBus::Connection> &connection,
                          const Glib::ustring &name);
        void name_acquired(const Glib::RefPtr<Gio::DBus::Connection> &connection,
                           const Glib::ustring &name);
        void name_lost(const Glib::RefPtr<Gio::DBus::Connection> &connection,
                       const Glib::ustring &name);

        Glib::RefPtr<Glib::MainLoop> main_loop_;
        guint connection_id_ = 0;

        Template template_;
    };
}

#endif // TEMPLATE_DBUS_SERVICE_DAEMON_DBUS_SERVICE_H
