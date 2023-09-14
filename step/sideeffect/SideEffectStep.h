#pragma once

#include "step/TraversalStep.h"

#define SIDE_EFFECT_STEP 0x30

namespace gremlinxx {

    class SideEffectStep : public TraversalStep {
        private:
            std::string label;
            std::any value;

        public:
            SideEffectStep(std::string se_label, std::any se_value)
            : TraversalStep(SIDE_EFFECT, SIDE_EFFECT_STEP) {
                this->label = se_label;
                this->value = se_value;
            }

            virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);

            using TraversalStep::getInfo;
            virtual std::string getInfo();
    };

}