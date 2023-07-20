#pragma once

#define INJECT_STEP 0x74

#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include <vector>
#include <any>

namespace gremlinxx {

class GraphTraversal;

    class InjectStep : public TraversalStep {
        private:
            std::vector<std::any> objects;
            
        public:
            InjectStep(std::vector<std::any>& injects);

            InjectStep(std::any& b);

            virtual void apply(GraphTraversal* trv, gremlinxx::traversal::TraverserSet& traversers);
    };

}