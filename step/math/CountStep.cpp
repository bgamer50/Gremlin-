#include "step/math/CountStep.h"
#include "traversal/GraphTraversal.h"
#include "maelstrom/algorithms/set.h"

namespace gremlinxx {

    CountStep::CountStep()
    : TraversalStep(true, MAP, COUNT_STEP) {}

    std::string CountStep::getInfo() {
        return std::string("CountStep{}");
    }

    void CountStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        traversers.advance([](auto& traverser_data, auto& traverser_se, auto& traverser_paths){
            size_t sz = traverser_data.size();
            maelstrom::vector new_data(
                traverser_data.get_mem_type(),
                traverser_data.get_dtype(),
                1
            );
            maelstrom::set(new_data, sz);

            if(sz > 0) {
                maelstrom::vector output_origin(
                    traverser_data.get_mem_type(),
                    traverser_data.get_dtype(),
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

}