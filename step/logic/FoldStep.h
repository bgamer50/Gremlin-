#ifndef FOLD_STEP_H
#define FOLD_STEP_H

#define FOLD_STEP 0x3f
#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"

#include <vector>
#include <list>

class FoldStep: public TraversalStep {
    public:
        FoldStep()
        : TraversalStep(MAP, FOLD_STEP) {}

        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers){
            TraverserSet new_traversers;

            size_t sz = traversers.size();
            std::vector<boost::any> vec(sz);
            for(size_t k = 0; k < sz; ++k) {
                vec[k] = traversers[k].get();
            }

            traversers.clear();
            traversers.push_back(Traverser(vec));
        }
};

#endif