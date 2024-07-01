#include "step/logic/OrderStep.h"
#include "step/modulate/ReductionStep.h"
#include "traversal/GraphTraversal.h"
#include "traversal/GraphTraversalSource.h"

#include "maelstrom/algorithms/arange.h"
#include "maelstrom/algorithms/sort.h"
#include "maelstrom/algorithms/select.h"
#include "maelstrom/algorithms/unique.h"
#include "maelstrom/algorithms/reverse.h"
#include "maelstrom/algorithms/randperm.h"

namespace gremlinxx {

    // This is a barrier step
    OrderStep::OrderStep()
    : TraversalStep(true, MAP, ORDER_STEP) {}


    void OrderStep::modulate_by(std::any arg) {
        if(arg.type() == typeid(std::pair<std::any, gremlinxx::Order>)) {
            auto p = std::any_cast<std::pair<std::any, gremlinxx::Order>>(arg);
            this->order_traversal.emplace(std::any_cast<GraphTraversal>(p.first));
            this->order.emplace(p.second);
        } else {
            this->order_traversal.emplace(std::any_cast<GraphTraversal>(arg));
        }
    }

    void update_reduction_steps(GraphTraversal& order_traversal) {
      for(auto& step : order_traversal.getSteps()) {
            auto reduction_step = dynamic_cast<ReductionStep*>(step.get());
            if(reduction_step != nullptr) {
                reduction_step->set_scope_context(ScopeContext{Scope::local, ORDER_STEP_SIDE_EFFECT_KEY});
            }
        }
    }

    void apply_with_traversal(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers, GraphTraversal& order_traversal, gremlinxx::Order sort_order) {
        update_reduction_steps(order_traversal);

        GraphTraversal exc_trv(traversal->getTraversalSource(), order_traversal);
		exc_trv.setInitialTraversers(traversers);

        // Need to initialize the scope context side effect
        auto indv = maelstrom::arange(traversers.getCurrentMemType(), traversers.size());
        exc_trv.getTraverserSet().set_side_effects(ORDER_STEP_SIDE_EFFECT_KEY, std::move(indv));

        // Iterate the traversal
        exc_trv.iterate();
        auto& retrieved_traversers = exc_trv.getTraverserSet();
        
        auto order_vals = retrieved_traversers.getTraverserData();
        auto output_origin = std::move(retrieved_traversers.getSideEffects()[ORDER_STEP_SIDE_EFFECT_KEY]);
        auto sort_ix = maelstrom::sort(output_origin);
        output_origin = std::move(maelstrom::select(output_origin, sort_ix));
        order_vals = std::move(maelstrom::select(order_vals, sort_ix));
        sort_ix.clear();
        
        traversers.advance([&output_origin, &order_vals, sort_order](auto& data, auto& se, auto& paths){
            // deduplicate (arbitrary deduplication)
            // TODO allow users to throw an exception instead of using arbitrary deduplication
            auto ix = maelstrom::unique(output_origin, true);

            // The output of unique() should be sorted since the input was sorted
            // It should be <= the # of traversers being ordered, or there is a problem.
            // Per Gremlin standard, traversers that evaluate to nothing get dropped.
            if(ix.size() > data.size()) {
                throw std::range_error("More keys than traversers were returned.");
            }

            output_origin = std::move(maelstrom::select(output_origin, ix));
            order_vals = std::move(maelstrom::select(order_vals, ix));

            if(sort_order == SHUFFLE) {
                output_origin = maelstrom::randperm(order_vals.get_mem_type(), order_vals.size(), order_vals.size());
            } else {
                ix = std::move(maelstrom::sort(order_vals));
                if(sort_order == DESC) {
                    maelstrom::reverse(ix);
                }
                order_vals.clear();
                
                output_origin = std::move(maelstrom::select(output_origin, ix));
                ix.clear();
            }

            return std::make_pair(
                std::move(maelstrom::select(data, output_origin)),
                std::move(output_origin)
            );
        });

        // Erase 1 level of paths (this is efficient chopping from the right like we're doing here)
        if(traversers.getPathLength() > 0) {
            traversers.trim_paths(0, traversers.getPathLength() - 1);
        }
    }

    void OrderStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        if(this->order_traversal) {
            return apply_with_traversal(traversal, traversers, *this->order_traversal, this->order.value_or(ASC));
        }

        auto sort_order = this->order.value_or(ASC);
        traversers.advance([sort_order](auto& traverser_data, auto& traverser_se, auto& traverser_paths){
            maelstrom::vector sorted_data(traverser_data);

            maelstrom::vector perm;
            if(sort_order == SHUFFLE) {
                perm = maelstrom::randperm(sorted_data.get_mem_type(), sorted_data.size(), sorted_data.size());
                sorted_data = std::move(maelstrom::select(sorted_data, perm));
            } else {
                perm = std::move(maelstrom::sort(sorted_data));
                if(sort_order == DESC) {
                    maelstrom::reverse(perm);
                    maelstrom::reverse(sorted_data);
                }
            }
            
            return std::make_pair(
                std::move(sorted_data),
                std::move(perm)
            );
        });

        // Erase 1 level of paths (this is efficient chopping from the right like we're doing here)
        if(traversers.getPathLength() > 0) {
            traversers.trim_paths(0, traversers.getPathLength() - 1);
        }
        
    }

    std::string OrderStep::getInfo(GraphTraversal* parent_traversal) {
        std::stringstream sx;
        sx << "OrderStep(";

        if(this->order_traversal.has_value()) {
            sx << this->order_traversal->info() << " -> ";
            GraphTraversal dt(parent_traversal->getTraversalSource(), this->order_traversal.value());
            update_reduction_steps(dt);
            dt.getInitialTraversal();
            sx << (dt.info());
            if(this->order.has_value()) sx << ", ";
        }

        if(this->order.has_value()) {
            sx << (this->order.value() == ASC) ? "ascending" : ((this->order.value() == DESC) ? "descending" : "shuffle");
        }
        sx << ")";

        return sx.str();
    }

    std::string OrderStep::getInfo() {
        std::stringstream sx;
        sx << "OrderStep(";

        if(this->order_traversal.has_value()) {
            sx << this->order_traversal->info();
            if(this->order.has_value()) sx << ", ";
        }

        if(this->order.has_value()) {
            sx << (this->order.value() == ASC) ? "ascending" : ((this->order.value() == DESC) ? "descending" : "shuffle");
        }
        sx << ")";

        return sx.str();
    }

}