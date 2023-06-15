#pragma once

#include <boost/any.hpp>
#include <optional>
#include <string>
#include <inttypes.h>

namespace gremlinxx {
    
    enum Scope {local, global};

    typedef struct ScopeContext {
        Scope scope;
        std::optional<std::string> side_effect_key;
    } ScopeContext;

    typedef int64_t scope_group_t;

    scope_group_t group_id_from_any(boost::any a);

    boost::any any_from_group_id(scope_group_t group_id, const std::type_info& out_type);

}