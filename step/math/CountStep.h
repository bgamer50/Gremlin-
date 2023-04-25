#pragma once

#define COUNT_STEP 0x61

#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include <functional>

class CountStep : public TraversalStep {
    public:
        CountStep();

        using TraversalStep::getInfo;
        virtual std::string getInfo();

        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers);
    
};

