#pragma once

#include "step/TraversalStep.h"
#include "step/graph/SubgraphStep.h"
#include "traversal/Traverser.h"

#define SUBGRAPH_EXTRACTION_STEP 0x65

class SubgraphExtractionStep : public TraversalStep {
    private:
        std::string subgraph_name;

    public:
        SubgraphExtractionStep(std::string sg_name);
 
        inline std::string get_subgraph_name() { return this->subgraph_name; }

        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers);

};
