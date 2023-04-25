#pragma once

#define MAP_STEP 0x3c

#include "step/TraversalStep.h"
#include "traversal/GraphTraversal.h"
#include "traversal/Traverser.h"

#include <vector>
#include <string>

class MapStep: public TraversalStep {
    private:
        GraphTraversal* map_traversal;
    
    public:
        MapStep(GraphTraversal* map_traversal);

        using TraversalStep::getInfo;
        virtual std::string getInfo();

        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers);
};
