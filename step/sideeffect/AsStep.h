#pragma once

#define AS_STEP 0x31

#include <string>
#include "step/TraversalStep.h"
#include "traversal/Traverser.h"

namespace gremlinxx {

    class AsStep: public TraversalStep {
        private:
            std::string sideEffectLabel;

        public:
            AsStep(std::string se_label);

            virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);

            using TraversalStep::getInfo;
            virtual std::string getInfo();
    };

}