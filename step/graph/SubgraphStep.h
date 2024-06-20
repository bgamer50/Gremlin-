#pragma once

#define SUBGRAPH_STEP 0x82

#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include "structure/Graph.h"

#include <unordered_map>
#include <unordered_set>
#include <string>

#define SUBGRAPH_PREFIX std::string("TP_SUBGRAPH_")

namespace gremlinxx {

    class SubgraphStep: public TraversalStep {
        private:
            std::string subgraph_name;

        public:
            SubgraphStep(std::string name);

            inline std::string get_subgraph_name() { return this->subgraph_name; }

            virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);

            using TraversalStep::getInfo;
            virtual std::string getInfo();
    };

}