#ifndef UNION_STEP_H
#define UNION_STEP_H

#define UNION_STEP 0x4a

#include <vector>

class TraversalStep;
class GraphTraversal;

class UnionStep: public TraversalStep {
    private:
        std::vector<GraphTraversal*> traversals;
    public:
        UnionStep(std::vector<GraphTraversal*>& traversals);
        std::vector<GraphTraversal*>& get_traversals();
        virtual void apply(GraphTraversal* parent_traversal, TraverserSet& traversers);
};

#include "traversal/GraphTraversal.h"
#include "step/TraversalStep.h"

UnionStep::UnionStep(std::vector<GraphTraversal*>& traversals)
    : TraversalStep(MAP, UNION_STEP) {
        for(auto it = traversals.begin(); it != traversals.end(); ++it) this->traversals.push_back(*it);
}

std::vector<GraphTraversal*>& UnionStep::get_traversals() {
    return this->traversals;
}

void UnionStep::apply(GraphTraversal* parent_traversal, TraverserSet& traversers) {
            size_t num_traversers = traversers.size();
            TraverserSet new_traversers;

            for(auto it = this->traversals.begin(); it != this->traversals.end(); ++it) {
                GraphTraversal* current_union_traversal = *it;

                GraphTraversal executing_traversal(parent_traversal->getTraversalSource(), current_union_traversal);
                TraverserSet temp_traversers(traversers.begin(), traversers.end());
                executing_traversal.setInitialTraversers(temp_traversers);
                
                executing_traversal.forEachRemaining([&](boost::any& obj){
                    new_traversers.push_back(Traverser(obj));
                });
            }

            traversers.swap(new_traversers);
        }

#endif