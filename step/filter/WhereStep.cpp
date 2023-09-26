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

#include <sstream>

namespace gremlinxx {

    WhereStep::WhereStep(std::string label, P predicate)
    : TraversalStep(FILTER, WHERE_STEP) {
        this->label = label;
        this->predicate = predicate;
    }

    std::string WhereStep::getInfo() {
        std::stringstream sx;
        sx << "WhereStep{" << this->label << "; " << this->predicate.getInfo() << "}";
        return sx.str();
    }

    void WhereStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        if(traversers.empty()) return;

        GraphTraversalSource* src = traversal->getTraversalSource();

        auto label = this->label;
        auto predicate = this->predicate;
        traversers.advance([label, predicate](auto& traverser_data, auto& side_effects, auto& path_info){
            maelstrom::vector ix;
            if(predicate.operand.type() == typeid(std::string) && side_effects.find(std::any_cast<std::string>(predicate.operand)) != side_effects.end()) {
                std::string other_label = std::any_cast<std::string>(predicate.operand);
                ix = maelstrom::compare(
                    side_effects[label],
                    side_effects[std::any_cast<std::string>(predicate.operand)],
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