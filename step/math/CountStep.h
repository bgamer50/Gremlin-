#pragma once

#define COUNT_STEP 0x61

#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include <functional>

namespace gremlinxx {

    class CountStep : public TraversalStep {
        public:
            CountStep();

            using TraversalStep::getInfo;
            virtual std::string getInfo();

            virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);
        
    };

}