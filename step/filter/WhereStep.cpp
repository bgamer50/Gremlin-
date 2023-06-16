#include "step/filter/WhereStep.h"
#include "traversal/Traverser.h"
#include "traversal/P.h"
#include "traversal/GraphTraversal.h"
#include "traversal/GraphTraversalSource.h"

#include "maelstrom/containers/vector.h"
#include "maelstrom/storage/comparison.h"
#include "maelstrom/algorithms/select.h"
#include "maelstrom/algorithms/filter.h"
#include "maelstrom/algorithms/compare.h"

namespace gremlinxx {

    WhereStep::WhereStep(std::string label, P predicate)
    : TraversalStep(FILTER, WHERE_STEP) {
        this->label = label;
        this->predicate = predicate;
    }

    void WhereStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        GraphTraversalSource* src = traversal->getTraversalSource();

        auto label = this->label;
        auto predicate = this->predicate;
        traversers.advance([label, predicate](auto& traverser_data, auto& side_effects, auto& path_info){
            maelstrom::vector ix;
            if(predicate.operand.type() == typeid(std::string) && side_effects.find(boost::any_cast<std::string>(predicate.operand)) != side_effects.end()) {
                ix = maelstrom::compare(
                    side_effects[label],
                    side_effects[boost::any_cast<std::string>(predicate.operand)],
                    predicate.comparison
                );

                ix = maelstrom::filter(ix, maelstrom::EQUALS, (uint8_t)1);
            } else {
                ix = maelstrom::filter(
                    side_effects[label],
                    predicate.comparison,
                    predicate.operand
                );
            }

            return std::make_pair(
                std::move(maelstrom::select(traverser_data, ix)),
                std::move(ix)
            );
        });
    }

}