#pragma once

#include <any>

namespace gremlinxx {

    class ByModulating {
        public:
            virtual void modulate_by(std::any arg) = 0;
    };

}