#include "step/controlflow/UnionStep.h"
#include "traversal/Traverser.h"

namespace gremlinxx {

    std::string UnionStep::getInfo() { 
        std::string info = "UnionStep{}";

        return info;
    }

    UnionStep::UnionStep(std::vector<GraphTraversal>& traversals)
    : TraversalStep(MAP, UNION_STEP) {
        for(auto it = traversals.begin(); it != traversals.end(); ++it) this->traversals.push_back(GraphTraversal(*it));
    }

    std::vector<GraphTraversal>& UnionStep::get_traversals() {
        return this->traversals;
    }

    void UnionStep::apply(GraphTraversal* parent_traversal, gremlinxx::traversal::TraverserSet& traversers) {
        GraphTraversal bogus_traversal(parent_traversal->getTraversalSource());
        gremlinxx::traversal::TraverserSet& new_traversers = bogus_traversal.getTraverserSet();

        for(auto it = this->traversals.begin(); it != this->traversals.end(); ++it) {
            GraphTraversal& current_union_traversal = *it;

            GraphTraversal executing_traversal(parent_traversal->getTraversalSource(), current_union_traversal);
            executing_traversal.setInitialTraversers(traversers);
            executing_traversal.iterate();
            
            auto& output_traversers = executing_traversal.getTraverserSet();
            new_traversers.addTraversers(output_traversers);
            output_traversers.clear();
        }

        traversers.clear();
        traversers.addTraversers(new_traversers);
        new_traversers.clear();
    }

}