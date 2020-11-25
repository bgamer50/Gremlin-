#ifndef SELECT_STEP_H
#define SELECT_STEP_H

#define SELECT_STEP 0x32

#include <string>
#include "step/TraversalStep.h"

class SelectStep: public TraversalStep {
    private:
        std::string sideEffectLabel;

    public:
        SelectStep(std::string sideEffectLabel)
        : TraversalStep(SIDE_EFFECT, SELECT_STEP) {
            this->sideEffectLabel = sideEffectLabel;
        }

        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers);
};

inline void SelectStep::apply(GraphTraversal* traversal, TraverserSet& traversers) {
    for(Traverser& trv : traversers) trv.replace_data(trv.get_side_effects()[sideEffectLabel]);
}

#endif