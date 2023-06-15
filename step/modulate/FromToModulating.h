#pragma once

namespace gremlinxx {

    class FromToModulating {
        public:
            virtual void modulate_from(boost::any arg) = 0;
            virtual void modulate_to(boost::any arg) = 0;
    };

}