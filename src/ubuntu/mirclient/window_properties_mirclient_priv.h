/*
 * Copyright (C) 2013 Canonical Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Robert Carr <robert.carr@canonical.com>
 */

#ifndef UBUNTU_APPLICATION_UI_WINDOW_PROPERTIES_MIRCLIENT_PRIV_H_
#define UBUNTU_APPLICATION_UI_WINDOW_PROPERTIES_MIRCLIENT_PRIV_H_

#include <ubuntu/application/ui/window.h>
#include <ubuntu/application/ui/window_type.h>
#include <mir_toolkit/mir_client_library.h>

#include <stddef.h>

#include <string>

namespace ubuntu
{
namespace application
{
namespace mir
{
namespace client
{

class WindowProperties
{
public:
    WindowProperties();
    ~WindowProperties() = default;

    UAUiWindowProperties* as_u_window_properties();
    static WindowProperties* from_u_window_properties(UAUiWindowProperties* u_properties);
    
    void set_title(char const* title, size_t length);
    void set_input_cb_and_ctx(UAUiWindowInputEventCb cb, void* ctx);
    void set_role(UAUiWindowRole role);    
    
    MirSurfaceParameters const& surface_parameters() const;
    MirSurfaceType surface_type() const;
    UAUiWindowInputEventCb input_cb() const;
    void* input_context() const;
    
protected:
    WindowProperties(WindowProperties const&) = delete;
    WindowProperties& operator=(WindowProperties const&) = delete;

private:
    MirSurfaceParameters parameters;
    MirSurfaceType type;

    std::string title;

    UAUiWindowInputEventCb cb;
    void *input_ctx;
};
    
}
}
}
}

#endif // UBUNTU_APPLICATION_UI_WINDOW_PROPERTIES_MIRCLIENT_PRIV_H_
