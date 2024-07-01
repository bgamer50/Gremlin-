#include "step/math/CountStep.h"
#include "traversal/GraphTraversal.h"

#include "maelstrom/algorithms/set.h"
#include "maelstrom/algorithms/sort.h"
#include "maelstrom/algorithms/arange.h"
#include "maelstrom/algorithms/reduce_by_key.h"
#include "maelstrom/algorithms/select.h"

namespace gremlinxx {

    CountStep::CountStep()
    : ReductionStep(COUNT_STEP) {}

    std::string CountStep::getInfo() {
        return std::string("CountStep{}");
    }

    void CountStep::apply_global(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        traversers.advance([](auto& traverser_data, auto& traverser_se, auto& traverser_paths){
            size_t sz = traverser_data.size();
            maelstrom::vector new_data(
                traverser_data.get_mem_type(),
                maelstrom::uint64,
                1
            );
            maelstrom::set(new_data, sz);

            if(sz > 0) {
                maelstrom::vector output_origin(
                    traverser_data.get_mem_type(),
                    maelstrom::uint64,
                    1
                );
                maelstrom::set(output_origin, static_cast<size_t>(0));

                return std::make_pair(
                    std::move(new_data),
                    std::move(output_origin)
                );
            }

            return std::make_pair(
                std::move(new_data),
                maelstrom::vector(traverser_data.get_mem_type(), maelstrom::uint64)
            );
        });
    }

    void CountStep::apply_local(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) { 
        if(traversers.empty()) return;

        std::string key = *this->scope_context.value().side_effect_key;
        traversers.advance([key](auto& traverser_data, auto& traverser_se, auto& traverser_paths){
            // count_unique doesn't work since the keys aren't guaranteed to be contiguous
            auto se = traverser_se[key];
            
            auto c = maelstrom::vector(se.get_mem_type(), maelstrom::uint64, se.size());
            maelstrom::set(c, 1);

            maelstrom::vector reduced_values;
            maelstrom::vector reduced_indices;
            std::tie(reduced_values, reduced_indices) = maelstrom::reduce_by_key(
                se,
                c,
                maelstrom::reductor::SUM,
                false // not sorted
            );
            c.clear();

            return std::make_pair(
                std::move(reduced_values),
                std::move(reduced_indices)
            );
        });
    }

}