#include "step/math/MinStep.h"
#include <iostream>

#include "maelstrom/algorithms/reduce.h"
#include "maelstrom/algorithms/set.h"

namespace gremlinxx {

    MinStep::MinStep()
    : TraversalStep(true, MAP, MIN_STEP) {}

    void MinStep::apply_global(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        traversers.advance([](auto traverser_data, auto traverser_se, auto traverser_path_info){
            boost::any min;
            size_t ix;

            std::tie(min, ix) = maelstrom::reduce(traverser_data, maelstrom::reductor::MIN);
            
            maelstrom::vector output_result(
                traverser_data.get_mem_type(),
                traverser_data.get_dtype(),
                1
            );
            maelstrom::set(output_result, min);

            maelstrom::vector output_origin(
                traverser_data.get_mem_type(),
                maelstrom::uint64,
                1
            );
            maelstrom::set(output_origin, ix);

            return std::make_pair(
                std::move(output_result),
                std::move(output_origin)
            );
        });
    }

    void MinStep::apply_local(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        this->scope_context.value().side_effect_key;
    }

    std::string MinStep::getInfo() { 
        std::string info = "MinStep{}";

        return info;
    }

    void MinStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        if(!scope_context || scope_context->scope == global) apply_global(traversal, traversers);
        else apply_local(traversal, traversers);
    }

}