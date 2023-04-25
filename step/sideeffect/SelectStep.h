#pragma once

#define SELECT_STEP 0x32

#include <string>
#include <typeindex>
#include <utility>

#include "step/TraversalStep.h"
#include "traversal/Traverser.h"

class SelectStep: public TraversalStep {
    private:
        std::string sideEffectLabel;

    public:
        SelectStep(std::string se_label);

        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers);

        using TraversalStep::getInfo;
        virtual std::string getInfo();
        
        inline std::string get_side_effect_label() { return this->sideEffectLabel; }
};

