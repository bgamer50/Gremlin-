#include "step/controlflow/CoalesceStep.h"

#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"
#include "step/TraversalStep.h"

namespace gremlinxx {
    CoalesceStep::CoalesceStep(std::vector<GraphTraversal>& traversals)
        : TraversalStep(MAP, COALESCE_STEP) {
            for(GraphTraversal& trv : traversals) {
                this->traversals.push_back(GraphTraversal(trv));
            }
    }

    std::vector<GraphTraversal>& CoalesceStep::get_traversals() {
        return this->traversals;
    }

    void CoalesceStep::apply(GraphTraversal* parent_traversal, gremlinxx::traversal::TraverserSet& traversers) {
        for(auto it = this->traversals.begin(); it != this->traversals.end(); ++it) {
            GraphTraversal current_coalesce_traversal = *it;
            GraphTraversal executing_traversal(parent_traversal->getTraversalSource(), current_coalesce_traversal);
            
            executing_traversal.setInitialTraversers(traversers);
            executing_traversal.iterate();
            
            gremlinxx::traversal::TraverserSet& new_traverser_set = executing_traversal.getTraverserSet();

            if(new_traverser_set.size() > 0) {
                traversers.clear();
                traversers.addTraversers(new_traverser_set);
                new_traverser_set.clear();
                return;
            }
        }

        // If all coalesce traversals return nothing, the traverser set should be empty.
        traversers.clear();
    }
}