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

    maelstrom::vector where_compare(maelstrom::vector& vec1, maelstrom::vector& vec2, P::Comparison cmp) {
        switch(cmp) {          
            case P::Comparison::EQ: {
                return maelstrom::compare(
                    vec1,
                    vec2,
                    maelstrom::comparator::EQUALS
                );
            }
            case P::Comparison::LT: {
                return maelstrom::compare(
                    vec1,
                    vec2,
                    maelstrom::comparator::LESS_THAN
                );
            }
            case P::Comparison::LTE: {
                return maelstrom::compare(
                    vec1,
                    vec2,
                    maelstrom::comparator::LESS_THAN_OR_EQUAL
                );
            }
            case P::Comparison::GT: {
                return maelstrom::compare(
                    vec1,
                    vec2,
                    maelstrom::comparator::GREATER_THAN
                );
            }
            case P::Comparison::GTE: {
                return maelstrom::compare(
                    vec1,
                    vec2,
                    maelstrom::comparator::GREATER_THAN_OR_EQUAL
                );
            }
            case P::Comparison::NEQ: {
                return maelstrom::compare(
                    vec1,
                    vec2,
                    maelstrom::comparator::NOT_EQUALS
                );
            }
        }

        throw std::runtime_error("Unsupported comparison type for where()");
    }

    maelstrom::vector where_filter(maelstrom::vector& vec, boost::any operand, P::Comparison cmp) {
        switch(cmp) {
            case P::Comparison::EQ:
                return maelstrom::filter(vec, maelstrom::comparator::EQUALS, operand);
            case P::Comparison::LT:
                return maelstrom::filter(vec, maelstrom::comparator::LESS_THAN, operand);
            case P::Comparison::LTE:
                return maelstrom::filter(vec, maelstrom::comparator::LESS_THAN_OR_EQUAL, operand);
            case P::Comparison::GT:
                return maelstrom::filter(vec, maelstrom::comparator::GREATER_THAN, operand);
            case P::Comparison::GTE:
                return maelstrom::filter(vec, maelstrom::comparator::GREATER_THAN_OR_EQUAL, operand);
            case P::Comparison::NEQ:
                return maelstrom::filter(vec, maelstrom::comparator::NOT_EQUALS, operand);
            case P::Comparison::BETWEEN:
                return maelstrom::filter(vec, maelstrom::comparator::BETWEEN, operand);
        }

        throw std::runtime_error("Unsupported comparison provided to where()");
    }

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
                ix = where_compare(
                    side_effects[label],
                    side_effects[boost::any_cast<std::string>(predicate.operand)],
                    predicate.comparison
                );
                ix = where_filter(ix, (uint8_t)1, P::Comparison::EQ);
            } else {
                ix = where_filter(
                    side_effects[label],
                    predicate.operand,
                    predicate.comparison
                );
            }

            return std::make_pair(
                std::move(maelstrom::select(traverser_data, ix)),
                std::move(ix)
            );
        });
    }

}