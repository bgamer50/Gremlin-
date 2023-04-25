#include "step/sideeffect/SelectStep.h"
#include <stdexcept>

SelectStep::SelectStep(std::string se_label)
: TraversalStep(SIDE_EFFECT, SELECT_STEP) {
    this->sideEffectLabel = sideEffectLabel;
}

void SelectStep::apply(GraphTraversal* traversal, TraverserSet& traversers) {
    //std::cout << traversers.size() << " traversers." << std::endl;
    //std::for_each(traversers[0].get_side_effects().begin(), traversers[0].get_side_effects().end(), [](std::pair<std::string, boost::any> r){std::cout << r.first << "\t" << (r.second.type() == typeid(Vertex*)) << std::endl;});
    for(Traverser& trv : traversers) {
        auto p = trv.get_side_effects().find(this->sideEffectLabel);
        if(p == trv.get_side_effects().end()) {
            throw std::runtime_error("Side effect " + this->sideEffectLabel + " does not exist!");
        }

        trv.replace_data(p->second);
    }
}

std::string SelectStep::getInfo() {
    return "SelectStep(" + this->sideEffectLabel + ")";
}