#include "structure/Graph.h"
#include "step/graph/SubgraphExtractionStep.h"

namespace gremlinxx {

    SubgraphExtractionStep::SubgraphExtractionStep(std::unordered_set<std::string> sg_names)
    : TraversalStep(SIDE_EFFECT, SUBGRAPH_EXTRACTION_STEP) {
        this->subgraph_names = sg_names;
    }

    void SubgraphExtractionStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        for(std::string name : this->subgraph_names) {
            auto edges = std::any_cast<maelstrom::vector>(traversal->removeTraversalProperty(SUBGRAPH_PREFIX + name));
            auto subgraph  = traversal->getGraph()->subgraph(edges);
            
            bool set = traversal->setTraversalProperty(name, std::move(subgraph));
            if(!set) {
                throw std::runtime_error("Unable to set subgraph traversal property for " + name);
            }
        }
    }

    std::string SubgraphExtractionStep::getInfo() {
        std::stringstream sx;
        sx << "SubgraphExtractionStep{";
        for(auto it = this->subgraph_names.begin(); it != this->subgraph_names.end(); ++it){
            sx << *it << ",";
        }
        
        std::string info = sx.str();
        info = info.substr(0, info.size() - 1) + "}";
        return info;
    }
}