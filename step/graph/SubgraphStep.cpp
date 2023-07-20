#include "step/graph/SubgraphStep.h"
#include "traversal/GraphTraversal.h"
#include "structure/Vertex.h"
#include "structure/Edge.h"

namespace gremlinxx {

    struct edge_hash {
        size_t operator() (Edge e) {
            return e.id;
        }
    };

    SubgraphStep::SubgraphStep(std::string name) : TraversalStep(SIDE_EFFECT, SUBGRAPH_STEP) {
        this->subgraph_name = name;
    }

    void SubgraphStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        std::any subgraph_property = traversal->getTraversalProperty(SUBGRAPH_PREFIX + subgraph_name);
        if(subgraph_property.empty()) subgraph_property = std::unordered_set<Edge, edge_hash>();
        
        std::unordered_set<Edge> subgraph_edges = std::any_cast<std::unordered_set<Edge, edge_hash>>(subgraph_property);
        auto traverser_data_copy = traversers.getTraverserData();
        auto traverser_data_host = maelstrom::as_host_vector(traverser_data_copy);

        for(size_t k = 0; k < traverser_data_host.size(); ++k) {
            std::any e = traverser_data_host.get(k);
            subgraph_edges.insert(std::any_cast<Edge>(e));
        }

        traversal->setTraversalProperty(SUBGRAPH_PREFIX + subgraph_name, subgraph_edges);
    }

}