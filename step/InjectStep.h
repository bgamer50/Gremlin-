#ifndef INJECT_STEP_H
#define INJECT_STEP_H

#define INJECT_STEP 0x74

#include "traversal/Traverser.h"
#include <boost/any.hpp>
#include <vector>
#include <algorithm>

class InjectStep : public TraversalStep {
    private:
        std::vector<boost::any> objects;
        
    public:
        InjectStep(std::vector<boost::any>& injects) : TraversalStep(SIDE_EFFECT, INJECT_STEP) {
            std::copy(injects.begin(), injects.end(), std::back_inserter(objects));
        }

        InjectStep(boost::any& b) : TraversalStep(SIDE_EFFECT, INJECT_STEP) {
            objects.push_back(b);
        }

        virtual void apply(GraphTraversal* trv, TraverserSet& traversers) {
            std::for_each(objects.begin(), objects.end(), [&](boost::any obj){
                traversers.push_back(Traverser(obj));
            });
        }
};

#endif