#pragma once

#define LIMIT_STEP 0x48

#include <string>
#include "step/TraversalStep.h"
#include "traversal/Traverser.h"

namespace gremlinxx {

    class LimitStep: public TraversalStep {
        private:
            uint64_t limit;

        public:
            LimitStep(uint64_t limit);

            virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);
            
            using TraversalStep::getInfo;
            virtual std::string getInfo();
            
            inline uint64_t get_limit() { return this->limit; }
    };


}