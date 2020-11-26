#ifndef COALESCE_STEP_H
#define COALESCE_STEP_H

#define COALESCE_STEP 0x40

#include <vector>

class TraversalStep;
class GraphTraversal;

class CoalesceStep: public TraversalStep {
    private:
        std::vector<GraphTraversal*> traversals;
    public:
        CoalesceStep(std::vector<GraphTraversal*>& traversals);
        std::vector<GraphTraversal*>& get_traversals();
        virtual void apply(GraphTraversal* parent_traversal, TraverserSet& traversers);
};

#include "traversal/GraphTraversal.h"
#include "step/TraversalStep.h"
#include "step/InjectStep.h"

CoalesceStep::CoalesceStep(std::vector<GraphTraversal*>& traversals)
    : TraversalStep(MAP, COALESCE_STEP) {
        for(auto it = traversals.begin(); it != traversals.end(); ++it) this->traversals.push_back(*it);
}

std::vector<GraphTraversal*>& CoalesceStep::get_traversals() {
    return this->traversals;
}

void CoalesceStep::apply(GraphTraversal* parent_traversal, TraverserSet& traversers) {
            size_t num_traversers = traversers.size();
            TraverserSet new_traversers;

            for(auto it = this->traversals.begin(); it != this->traversals.end(); ++it) {
                GraphTraversal* current_coalesce_traversal = *it;
                
                std::vector<boost::any> objects(num_traversers);
                for(size_t k = 0; k < num_traversers; ++k) objects[k] = traversers[k].get();

                GraphTraversal executing_traversal(parent_traversal->getTraversalSource(), current_coalesce_traversal);
                InjectStep inject_step(objects);
                executing_traversal.insertStep(0, &inject_step);
                
                executing_traversal.forEachRemaining([&](boost::any& obj){
                    new_traversers.push_back(Traverser(obj));
                });

                if(new_traversers.size() > 0) break;
            }

            traversers.swap(new_traversers);
        }

#endif