#ifndef COALESCE_STEP_H
#define COALESCE_STEP_H

#define COALESCE_STEP 0x40

#include "TraversalStep.h"
#include "GraphTraversal.h"

class CoalesceStep: public TraversalStep {
    private:
        std::vector<GraphTraversal*> traversals;
    public:
        CoalesceStep(std::vector<GraphTraversal*>& traversals)
        : TraversalStep(MAP, COALESCE_STEP) {
            for(auto it = traversals.begin(); it != traversals.end(); ++it) this->traversals.push_back(*it);
        }

        std::vector<GraphTraversal*>& get_traversals() {
            return this->traversals;
        }
};

#endif