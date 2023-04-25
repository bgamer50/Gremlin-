#include "step/controlflow/InjectStep.h"
#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"

InjectStep::InjectStep(std::vector<boost::any>& injects) : TraversalStep(SIDE_EFFECT, INJECT_STEP) {
    std::copy(injects.begin(), injects.end(), std::back_inserter(objects));
}

InjectStep::InjectStep(boost::any& b) : TraversalStep(SIDE_EFFECT, INJECT_STEP) {
    objects.push_back(b);
}

void InjectStep::apply(GraphTraversal* trv, TraverserSet& traversers) {
    std::for_each(objects.begin(), objects.end(), [&](boost::any obj){
        traversers.push_back(Traverser(obj));
    });
}