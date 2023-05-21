#pragma once

#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"

#include <optional>

#define REPEAT_STEP 0x42
#define LOOPS_TRAVERSAL_PROPERTY std::string("TRV_LOOPS")

namespace gremlinxx {
    
    class RepeatStep: public TraversalStep {
        private:
            // Will emit anything out of the loop that passes through this traversal.
            GraphTraversal* emitTraversal = nullptr;
            
            // Will end the loop when this traversal is completed.
            GraphTraversal* untilTraversal = nullptr;

            // The action to be repeated.
            GraphTraversal* actionTraversal = nullptr;

            // The # of times to run the loop
            std::optional<size_t> times;

        public:
            RepeatStep(GraphTraversal* actionTraversal);

            inline GraphTraversal* getActionTraversal() { return this->actionTraversal; }

            inline void setEmitTraversal(GraphTraversal* emitTraversal) { this->emitTraversal = emitTraversal; }
            inline GraphTraversal* getEmitTraversal() { return this->emitTraversal; }

            inline void setUntilTraversal(GraphTraversal* untilTraversal) { this->untilTraversal = untilTraversal; }
            inline GraphTraversal* getUntilTraversal() { return this->untilTraversal; }

            inline void setTimes(size_t times) { this->times = times; }

            virtual void apply(GraphTraversal* trv, gremlinxx::traversal::TraverserSet& traversers);

            using TraversalStep::getInfo;
            virtual std::string getInfo();
            

    };

}