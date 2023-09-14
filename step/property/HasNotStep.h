#pragma once

#define HAS_NOT_STEP 0x84

#include "step/TraversalStep.h"

namespace gremlinxx {

    class HasNotStep : public TraversalStep {
        private:
            std::string property_key;
        public:
            HasNotStep(std::string key)
            : TraversalStep(FILTER, HAS_NOT_STEP) {
                this->property_key = key;
            }

            virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);

            using TraversalStep::getInfo;
            std::string getInfo();
    };

}