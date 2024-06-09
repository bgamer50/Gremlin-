#pragma once

#define SAMPLE_STEP 0x50

#include "step/TraversalStep.h"

namespace gremlinxx {

    class SampleStep: public TraversalStep {
        private:
            size_t count;

        public:
            SampleStep(size_t num_traversers);

            virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);
            
            using TraversalStep::getInfo;
            virtual std::string getInfo();
    };

}