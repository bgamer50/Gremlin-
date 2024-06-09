#include "step/filter/SampleStep.h"

#include "maelstrom/algorithms/randperm.h"
#include "maelstrom/algorithms/select.h"

namespace gremlinxx {

    SampleStep::SampleStep(size_t num_traversers)
    : TraversalStep(FILTER, SAMPLE_STEP) {
        this->count = num_traversers;
    }

    void SampleStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        size_t N = this->count;
        traversers.advance([N](auto& data, auto& side_effects, auto& paths){
            // FIXME properly set random seed
            auto perm = maelstrom::randperm(data.get_mem_type(), data.size(), N);

            auto new_data = maelstrom::select(data, perm);
            return std::make_pair(
                std::move(new_data),
                std::move(perm)
            );
        });
    }
    
    std::string SampleStep::getInfo() {
        std::stringstream sx;
        sx << "SampleStep{" << this->count << "}";
        return sx.str();
    }

}