#pragma once

#include <string>
#include <optional>

namespace gremlinxx {

    class LimitSupportingStep {
        public:
            virtual void set_limit(size_t limit) = 0;
            virtual std::optional<size_t> get_limit() = 0;
    };

}