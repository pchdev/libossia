#pragma once

#include "ossia_obj_base.hpp"
#include "device.hpp"
#include "model.hpp"

namespace ossia { namespace pd {

struct t_param : ossia_obj_base
{
    bool register_node(ossia::net::node_base* node);
    bool do_registration(ossia::net::node_base* node);
    bool unregister();

    t_symbol* x_type;
    t_atom x_default;
    // TODO use optional for range
    float x_range[2];
    t_symbol* x_bounding_mode;
    t_symbol* x_access_mode;
    t_float x_repetition_filter=0;
    t_symbol* x_unit;
    t_symbol* x_tags;
    t_symbol* x_description;

    static std::vector<t_param*>& quarantine(){
        static std::vector<t_param*> quarantine;
        return quarantine;
    }
};

} } // namespace
