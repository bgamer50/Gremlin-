#include "step/graph/SubgraphStep.h"
#include "traversal/GraphTraversal.h"
#include "structure/Vertex.h"
#include "structure/Edge.h"

#include "maelstrom/algorithms/sort.h"
#include "maelstrom/algorithms/unique.h"
#include "maelstrom/algorithms/select.h"

namespace gremlinxx {
    SubgraphStep::SubgraphStep(std::string name) : TraversalStep(SIDE_EFFECT, SUBGRAPH_STEP) {
        this->subgraph_name = name;
    }

    void SubgraphStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        auto traverser_data_copy = traversers.getTraverserData();
        if(traverser_data_copy.get_dtype() != traversal->getGraph()->get_edge_dtype()) {
            throw std::invalid_argument("subgraph() can only be called on edges");
        }

        std::any subgraph_property = traversal->removeTraversalProperty(SUBGRAPH_PREFIX + subgraph_name);
        if(subgraph_property.has_value()) {
            traverser_data_copy.insert(std::any_cast<maelstrom::vector&>(subgraph_property));
        }

        maelstrom::sort(traverser_data_copy);
        auto ix = maelstrom::unique(traverser_data_copy, true);
        bool set = traversal->setTraversalProperty(
            SUBGRAPH_PREFIX + subgraph_name,
            std::move(maelstrom::select(traverser_data_copy, ix))
        );

        if(!set) throw std::runtime_error("An error occured setting a traversal property for subgraph " + subgraph_name);
    }

    std::string SubgraphStep::getInfo() {
        return "SubgraphStep{" + this->subgraph_name + "}";
    }
}