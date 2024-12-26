#include "strategy/BasicPatternExtractionStrategy.h"
#include "step/vertex/VertexStep.h"
#include "step/math/CountStep.h"
#include "step/vertex/DegreeStep.h"

namespace gremlinxx {

    TraversalStrategy BasicPatternExtractionStrategy = {
        OPTIMIZATION,
        "BasicPatternExtractionStrategy",
        [](std::vector<std::shared_ptr<TraversalStep>>& steps){
            for(auto it = steps.begin(); it != steps.end(); ++it) {
                // Degree Pattern
                if((*it)->uid == VERTEX_STEP) {
                    auto vertex_step = static_cast<VertexStep*>(it->get());
                    if(vertex_step->get_type() == VERTEX_TO_VERTEX || vertex_step->get_type() == VERTEX_TO_EDGE) {
                        if(it != steps.end() - 1 && (*(it+1))->uid == COUNT_STEP) {
                            auto count_step = static_cast<CountStep*>((it+1)->get());
                            if(count_step->get_scope_context().has_value() && count_step->get_scope_context().value().scope == local) {
                                // matched degree pattern
                                std::shared_ptr<TraversalStep> degree_step(
                                    new DegreeStep(vertex_step->get_direction(), vertex_step->get_labels())
                                );

                                // erase after accessing what could be the last shared pointer to the vertex step
                                it = steps.erase(it);
                                *it = degree_step;
                                it -= 1;
                            }
                        }
                    }
                }
            }
        }
    };

}