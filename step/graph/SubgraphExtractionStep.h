#ifndef SUBGRAPH_EXTRACTION_STEP_H
#define SUBGRAPH_EXTRACTION_STEP_H

#include "step/TraversalStep.h"
#include "step/graph/SubgraphStep.h"

#define SUBGRAPH_EXTRACTION_STEP 0x65

class SubgraphExtractionStep : public TraversalStep {
    private:
        std::string subgraph_name;

    public:
        SubgraphExtractionStep(std::string subgraph_name) : TraversalStep(MAP, SUBGRAPH_EXTRACTION_STEP) {
            this->subgraph_name = subgraph_name;
        }

        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers) {
            throw std::runtime_error("Cannot run from anonymous traversal!");
        }

        inline std::string get_subgraph_name() { return this->subgraph_name; }
};

#endif