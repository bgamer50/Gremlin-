#include "step/graph/SubgraphStep.h"
#include "traversal/GraphTraversal.h"
#include "structure/Vertex.h"
#include "structure/Edge.h"

SubgraphStep::SubgraphStep(std::string name) : TraversalStep(SIDE_EFFECT, SUBGRAPH_STEP) {
    this->subgraph_name = name;
}

void SubgraphStep::apply(GraphTraversal* traversal, TraverserSet& traversers) {
    boost::any subgraph_property = traversal->getTraversalProperty(SUBGRAPH_PREFIX + subgraph_name);
    if(subgraph_property.empty()) subgraph_property = std::unordered_set<Edge*>();
    
    std::unordered_set<Edge*> subgraph_edges = boost::any_cast<std::unordered_set<Edge*>>(subgraph_property);
    for(Traverser& trv : traversers) {
        subgraph_edges.insert(boost::any_cast<Edge*>(trv.get()));
    }

    traversal->setTraversalProperty(SUBGRAPH_PREFIX + subgraph_name, subgraph_edges);
}