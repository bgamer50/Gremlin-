#pragma once

#define EMIT_STEP 0x44

#include "step/TraversalStep.h"
#include "traversal/GraphTraversal.h"

namespace gremlinxx {
    

    class EmitStep: public TraversalStep {

        private:
            GraphTraversal traversal;

        public:
            EmitStep(GraphTraversal traversal);

            GraphTraversal getTraversal();
    };

}