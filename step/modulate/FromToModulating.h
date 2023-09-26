#pragma once

namespace gremlinxx {

    class GraphTraversal;

    class FromToModulating {
        public:
            virtual void modulate_from(GraphTraversal trv) = 0;
            virtual void modulate_to(GraphTraversal trv) = 0;
    };

}