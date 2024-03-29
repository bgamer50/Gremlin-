#pragma once

#define LOOPS_STEP 0x4c

#include "step/TraversalStep.h"
#include "traversal/GraphTraversal.h"
#include "traversal/Traverser.h"

namespace gremlinxx {
    class LoopsStep: public TraversalStep {
        private:
            GraphTraversal* traversal;

        public:
            LoopsStep();

            virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);
    };

}