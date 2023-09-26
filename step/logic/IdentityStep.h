#pragma once

#define IDENTITY_STEP 0x01
#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"

namespace gremlinxx {

    class IdentityStep: public TraversalStep {
        public:
            IdentityStep();

            virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);

            using TraversalStep::getInfo;
            virtual std::string getInfo();
    };

}