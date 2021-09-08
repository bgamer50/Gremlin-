#ifndef AS_STEP_H
#define AS_STEP_H

#define AS_STEP 0x31

#include <string>
#include "step/TraversalStep.h"

class AsStep: public TraversalStep {
    private:
        std::string sideEffectLabel;

    public:
        AsStep(std::string sideEffectLabel)
        : TraversalStep(SIDE_EFFECT, AS_STEP) {
            this->sideEffectLabel = sideEffectLabel;
        }

        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers);

        virtual std::string getInfo() { return "AsStep{" + sideEffectLabel + "}"; }
};

inline void AsStep::apply(GraphTraversal* traversal, TraverserSet& traversers) {
    for(Traverser& trv : traversers) {
        trv.get_side_effects()[sideEffectLabel] = trv.get();
    }
}

#endif