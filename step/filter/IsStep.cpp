#include "step/filter/IsStep.h"
#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"
#include "traversal/GraphTraversalSource.h"

#include "maelstrom/storage/comparison.h"
#include "maelstrom/algorithms/filter.h"
#include "maelstrom/algorithms/select.h"

namespace gremlinxx {

    IsStep::IsStep(P predicate)
    : TraversalStep(FILTER, IS_STEP) {
        this->predicate = predicate;
    }

    std::string IsStep::getInfo() { 
        std::string info = "IsStep{}";

        return info;
    }

    void IsStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        boost::any val = this->predicate.operand;
        auto cmp = this->predicate.comparison;

        traversers.advance([cmp, val](auto& data, auto& se, auto& paths){
            maelstrom::vector ix;
            switch(cmp) {
                case P::Comparison::EQ: {
                    ix = maelstrom::filter(
                        data,
                        maelstrom::comparator::EQUALS,
                        val
                    );
                    break;
                }
                case P::Comparison::LT: {
                    ix = maelstrom::filter(
                        data,
                        maelstrom::comparator::LESS_THAN,
                        val
                    );
                    break;
                }
                case P::Comparison::LTE: {
                    ix = maelstrom::filter(
                        data,
                        maelstrom::comparator::LESS_THAN_OR_EQUAL,
                        val
                    );
                    break;
                }
                case P::Comparison::GT: {
                    ix = maelstrom::filter(
                        data,
                        maelstrom::comparator::GREATER_THAN,
                        val
                    );
                    break;
                }
                case P::Comparison::GTE: {
                    ix = maelstrom::filter(
                        data,
                        maelstrom::comparator::GREATER_THAN_OR_EQUAL,
                        val
                    );
                    break;
                }
                case P::Comparison::NEQ: {
                    ix = maelstrom::filter(
                        data,
                        maelstrom::comparator::NOT_EQUALS,
                        val
                    );
                    break;
                }
                case P::Comparison::BETWEEN: {
                    ix = maelstrom::filter(
                        data,
                        maelstrom::comparator::BETWEEN,
                        val
                    );
                    break;
                }
                default:
                    throw std::runtime_error("Invalid comparison type in IsStep");
            }
            
            return std::make_pair(
                std::move(maelstrom::select(data, ix)),
                std::move(ix)
            );
        });
    }

}