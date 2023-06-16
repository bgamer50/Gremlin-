#include "step/math/MinStep.h"
#include <iostream>

#include "maelstrom/algorithms/reduce.h"
#include "maelstrom/algorithms/reduce_by_key.h"
#include "maelstrom/algorithms/set.h"
#include "maelstrom/algorithms/sort.h"
#include "maelstrom/algorithms/select.h"

namespace gremlinxx {

    MinStep::MinStep()
    : ReductionStep(MIN_STEP) {}

    void MinStep::apply_global(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        traversers.advance([](auto& traverser_data, auto& traverser_se, auto& traverser_path_info){
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
        std::string key = *this->scope_context.value().side_effect_key;

        traversers.advance([key](auto& traverser_data, auto& traverser_se, auto& traverser_path_info){
            // sort
            auto se = traverser_se[key];
            auto ix = maelstrom::sort(se);
            auto data_copy = maelstrom::select(traverser_data, ix);

            maelstrom::vector reduced_values;
            maelstrom::vector reduced_indices;
            std::tie(reduced_values, reduced_indices) = maelstrom::reduce_by_key(
                se,
                data_copy,
                maelstrom::reductor::MIN,
                true
            );
            data_copy.clear();

            reduced_indices = maelstrom::select(ix, reduced_indices);

            return std::make_pair(
                std::move(reduced_values),
                std::move(reduced_indices)
            );
        });
    }

    std::string MinStep::getInfo() { 
        std::string info = "MinStep{}";

        return info;
    }

}