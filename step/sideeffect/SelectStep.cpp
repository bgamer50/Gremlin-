#include "step/sideeffect/SelectStep.h"
#include <iostream>
#include <sstream>

namespace gremlinxx {

    SelectStep::SelectStep(std::string se_label)
    : TraversalStep(SIDE_EFFECT, SELECT_STEP) {
        this->sideEffectLabel = sideEffectLabel;
    }

    void SelectStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        std::string se_label = this->sideEffectLabel;

        traversers.advance([se_label](auto traverser_data, auto traverser_se, auto traverser_path_info){
            if(traverser_se.find(se_label) == traverser_se.end()) {
                std::stringstream sx;
                sx << "Invalid side effect key " << se_label;
                throw std::runtime_error(sx.str());
            }

            return std::make_pair(
                traverser_se[se_label],
                maelstrom::vector()
            );
        });
    }

    std::string SelectStep::getInfo() {
        return "SelectStep(" + this->sideEffectLabel + ")";
    }

}