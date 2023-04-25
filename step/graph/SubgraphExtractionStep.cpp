#include "step/graph/SubgraphExtractionStep.h"

SubgraphExtractionStep::SubgraphExtractionStep(std::string sg_name) : TraversalStep(MAP, SUBGRAPH_EXTRACTION_STEP) {
    this->subgraph_name = sg_name;
}

void SubgraphExtractionStep::apply(GraphTraversal* traversal, TraverserSet& traversers) {
    throw std::runtime_error("Cannot run from anonymous traversal!");
}