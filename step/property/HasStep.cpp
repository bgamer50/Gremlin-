#include "step/property/HasStep.h"
#include "traversal/GraphTraversal.h"
#include "traversal/GraphTraversalSource.h"

#include "structure/Vertex.h"
#include "structure/Graph.h"

#include "maelstrom/algorithms/intersection.h"
#include "maelstrom/algorithms/filter.h"
#include "maelstrom/algorithms/select.h"
#include "maelstrom/algorithms/arange.h"

namespace gremlinxx {

    // Initialize the default filter policy
    filter_policy_t HasStep::FILTER_POLICY = BY_ENTRY_COUNT;

    HasStep::HasStep(std::string property_key_or_label, P predicate)
    : TraversalStep(FILTER, HAS_STEP) {
        this->predicates.push_back(std::make_pair(
            property_key_or_label,
            predicate
        ));
    }

    void HasStep::join(HasStep* other) {
        this->predicates.insert(this->predicates.end(), other->predicates.begin(), other->predicates.end());
    }

    std::string	HasStep::getInfo() {
        std::stringstream sx;
        sx << "HasStep(";
        for(auto it = this->predicates.begin(); it != this->predicates.end(); ++it) {
            sx << it->first << " " << it->second.getInfo();
            if(it != this->predicates.end() - 1) sx << ", ";
        }
        sx << ")";

        return sx.str();
    }

    void HasStep::apply(GraphTraversal* trv, gremlinxx::traversal::TraverserSet& traversers) {
        GraphTraversalSource* g = trv->getTraversalSource();
        bool vertex = (traversers.getCurrentDataType() == g->getGraph()->get_vertex_dtype());
        if(!vertex && traversers.getCurrentDataType() != g->getGraph()->get_edge_dtype()) {
            throw std::domain_error("Can't get an element map for something other than a vertex or edge");
        }

        if(traversers.empty()) return;

        // sort to pick the property with the lowest number of entries
        auto filter_policy = HasStep::FILTER_POLICY;
        if(filter_policy != BY_SPECIFIED_ORDER) {
            std::sort(
                this->predicates.begin(),
                this->predicates.end(),
                [g, vertex, filter_policy](auto p, auto q){
                    const size_t first_size = vertex ? g->getGraph()->get_vertex_property_num_entries(p.first) : g->getGraph()->get_edge_property_num_entries(p.first);
                    const size_t second_size = vertex ? g->getGraph()->get_vertex_property_num_entries(q.first) : g->getGraph()->get_edge_property_num_entries(q.first);
                    return (filter_policy == BY_ENTRY_COUNT) ? std::less<size_t>()(first_size, second_size) : std::greater<size_t>()(first_size, second_size);
                }
            );
        }

        auto preds = this->predicates;
        traversers.advance([&g, preds, vertex](auto& traverser_data, auto& traverser_se, auto& traverser_path_info){
            auto ix_found = maelstrom::arange(traverser_data.get_mem_type(), traverser_data.size());

            for(auto& pred : preds) {
                maelstrom::vector found_values;
                maelstrom::vector ix_found_found;
                auto search_keys = maelstrom::select(traverser_data, ix_found);
                if(vertex) {
                    std::tie(
                        found_values,
                        ix_found_found
                    ) = g->getGraph()->get_vertex_properties(pred.first, search_keys, pred.second.operand.has_value());
                } else {
                    std::tie(
                        found_values,
                        ix_found_found
                    ) = g->getGraph()->get_edge_properties(pred.first, search_keys, pred.second.operand.has_value());
                }

                if(pred.second.operand.has_value()) {
                    // filter down found_vertices using found_values
                    auto ix_matches = maelstrom::filter(
                        found_values,
                        pred.second.comparison,
                        pred.second.operand
                    );
                    found_values.clear();

                    ix_found_found = maelstrom::select(ix_found_found, ix_matches);
                    ix_found = maelstrom::select(ix_found, ix_found_found);
                }
            }

            auto found_elements = maelstrom::select(traverser_data, ix_found);
            return std::make_pair(
                std::move(found_elements),
                std::move(ix_found)
            );
        });
    }

}