#pragma once

#include "step/TraversalStep.h"
#include "step/graph/SubgraphStep.h"
#include "traversal/Traverser.h"

#include <unordered_set>

#define SUBGRAPH_EXTRACTION_STEP 0x65

namespace gremlinxx {

    class SubgraphExtractionStep : public TraversalStep {
        private:
            std::unordered_set<std::string> subgraph_names;

        public:
            SubgraphExtractionStep(std::unordered_set<std::string> sg_names);
    
            inline std::unordered_set<std::string> get_subgraph_names() { return this->subgraph_names; }

            virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);

            using TraversalStep::getInfo;
            virtual std::string getInfo();
    };

}