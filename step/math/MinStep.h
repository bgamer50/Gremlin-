#pragma once

#define MIN_STEP 0x60

#include "step/TraversalStep.h"
#include "step/modulate/ReductionStep.h"
#include "traversal/Traverser.h"
#include "traversal/Scope.h"
#include "traversal/Comparison.h"

#include <optional>

namespace gremlinxx {

    class MinStep : public ReductionStep {
        public:
            MinStep();

            using ReductionStep::apply_global;
            virtual void apply_global(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);

            using ReductionStep::apply_local;
            virtual void apply_local(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);

            using ReductionStep::getInfo;
            virtual std::string getInfo();
    };

}