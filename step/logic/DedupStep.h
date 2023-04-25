#pragma once

#define DEDUP_STEP 0x49

#include <string>
#include <functional>
#include <optional>

#include "step/TraversalStep.h"
#include "step/modulate/ByModulating.h"
#include "traversal/Traverser.h"

// In the future this may get optimized away for most traversals by moving
// the barrier to the left of the step and testing each element upon appearance
class DedupStep: public TraversalStep, virtual public ByModulating {
    private:
        std::optional<std::string> dedup_by_key; // TODO make this actually do something

    public:
        // This is a barrier step
        DedupStep();

        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers);

        using TraversalStep::getInfo;
        virtual std::string getInfo();

        virtual void modulate_by(boost::any arg);
};


