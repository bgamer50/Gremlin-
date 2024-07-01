#pragma once

#define COUNT_STEP 0x61

#include "step/modulate/ReductionStep.h"
#include "traversal/Traverser.h"
#include <functional>

namespace gremlinxx {

    class CountStep : public ReductionStep {
        public:
            CountStep();

            using ReductionStep::getInfo;
            virtual std::string getInfo();

            using ReductionStep::apply_global;
            virtual void apply_global(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);
        
            using ReductionStep::apply_local;
            virtual void apply_local(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);
    };

}