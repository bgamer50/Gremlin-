#ifndef UNFOLD_STEP_H
#define UNFOLD_STEP_H

#define UNFOLD_STEP 0x41
#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"

#include <vector>
#include <list>

class UnfoldStep: public TraversalStep {
    public:
        UnfoldStep()
        : TraversalStep(MAP, UNFOLD_STEP) {}

        // Currently supports list, vector
        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers){
            TraverserSet new_traversers;

            for(Traverser& t: traversers) {
                auto& type = t.get().type();
                if(typeid(std::list<boost::any>) == type) {
                    auto l = boost::any_cast<std::list<boost::any>>(t.get());
                    new_traversers.insert(new_traversers.end(), l.begin(), l.end());
                } else if(typeid(std::vector<boost::any>) == type) {
                    auto v = boost::any_cast<std::vector<boost::any>>(t.get());
                    new_traversers.insert(new_traversers.end(), v.begin(), v.end());
                } else {
                    new_traversers.push_back(t);
                }
            }

            traversers.swap(new_traversers);
        }
};

#endif