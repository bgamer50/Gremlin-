#include "step/logic/UnfoldStep.h"

UnfoldStep::UnfoldStep()
: TraversalStep(MAP, UNFOLD_STEP) {}

std::string UnfoldStep::getInfo() {
    return std::string("UnfoldStep{}");
}

void UnfoldStep::apply(GraphTraversal* traversal, TraverserSet& traversers) {
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