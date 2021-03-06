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

#include "application_options_mir_priv.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include <tuple>
#include <string>

namespace uam = ubuntu::application::mir;

UApplicationOptions* uam::Options::as_u_application_options()
{
    return static_cast<UApplicationOptions*>(this);
}
uam::Options* uam::Options::from_u_application_options(UApplicationOptions* options)
{
    return static_cast<uam::Options*>(options);
}

namespace
{

UAUiStage
string_to_stage(std::string const& s)
{
    if (s == "main_stage")
        return U_MAIN_STAGE;
    else if (s == "side_stage")
        return U_SIDE_STAGE;
    else if (s == "share_stage")
        return U_SHARE_STAGE;
}

UAUiFormFactor
string_to_form_factor(std::string const& s)
{
    if (s == "desktop")
        return U_DESKTOP;
    else if (s == "phone")
        return U_PHONE;
    else if (s == "tablet")
        return U_TABLET;
}

void print_help_and_exit()
{
    printf("Usage: executable "
           "[--form_factor_hint={desktop, phone, tablet}] "
           "[--stage_hint={main_stage, side_stage, share_stage}] "
           "[--desktop_file_hint=absolute_path_to_desktop_file]\n");
    exit(EXIT_SUCCESS);
}

}

extern "C"
{
UApplicationOptions*
u_application_options_new_from_cmd_line(int argc, char** argv)
{
    static const int uninteresting_flag_value = 0;
    static struct option long_options[] =
    {        
        {"form_factor_hint", required_argument, NULL, uninteresting_flag_value},
        {"stage_hint", required_argument, NULL, uninteresting_flag_value},
        {"desktop_file_hint", required_argument, NULL, uninteresting_flag_value},
        {"help", no_argument, NULL, uninteresting_flag_value},
        {0, 0, 0, 0}
    };

    static const int form_factor_hint_index = 0;
    static const int stage_hint_index = 1;
    static const int desktop_file_hint_index = 2;
    static const int help_index = 3;

    auto app_options = new uam::Options;

    while(true)
    {
        int option_index = 0;

        int c = getopt_long(argc,
                            argv,
                            "",
                            long_options,
                            &option_index);

        if (c == -1)
            break;

        switch (c)
        {
        case 0:
            // If this option set a flag, do nothing else now.
            if (long_options[option_index].flag != 0)
                break;
            if (option_index == help_index)
                print_help_and_exit();
            if (optarg)
            {
                switch(option_index)
                {
                case form_factor_hint_index:
                    app_options->form_factor = string_to_form_factor(std::string(optarg));
                    break;
                case stage_hint_index:
                    app_options->stage = string_to_stage(std::string(optarg));
                    break;
                case desktop_file_hint_index:
                    app_options->desktop_file = std::string(optarg);
                    break;                
                }
            }
            break;
        case '?':
            break;
        }
    }
    
    return app_options->as_u_application_options();
}

void
u_application_options_destroy(UApplicationOptions* u_options)
{
    auto options = uam::Options::from_u_application_options(u_options);
    delete options;
}

UApplicationOperationMode
u_application_options_get_operation_mode(UApplicationOptions *u_options)
{
    auto options = uam::Options::from_u_application_options(u_options);
    return options->operation_mode;
}

UAUiFormFactor
u_application_options_get_form_factor(UApplicationOptions* u_options)
{
    auto options = uam::Options::from_u_application_options(u_options);
    return options->form_factor;
}

UAUiStage
u_application_options_get_stage(UApplicationOptions* u_options)
{
    auto options = uam::Options::from_u_application_options(u_options);
    return options->stage;
}
}
