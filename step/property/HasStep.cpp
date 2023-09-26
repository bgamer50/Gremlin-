#include "step/property/HasStep.h"
#include "traversal/GraphTraversal.h"
#include "traversal/GraphTraversalSource.h"

#include "structure/Vertex.h"
#include "structure/Graph.h"

#include "maelstrom/algorithms/intersection.h"
#include "maelstrom/algorithms/filter.h"
#include "maelstrom/algorithms/select.h"

namespace gremlinxx {

    HasStep::HasStep(std::string property_key_or_label, P predicate)
    : TraversalStep(FILTER, HAS_STEP) {
        this->predicate = predicate;
        this->property_key_or_label = property_key_or_label;
    }

    std::string	HasStep::getInfo() {
        return std::string("HasStep(") + property_key_or_label + " " + predicate.getInfo() + ")";
    }

    void HasStep::apply(GraphTraversal* trv, gremlinxx::traversal::TraverserSet& traversers) {
        GraphTraversalSource* g = trv->getTraversalSource();
        bool vertex = (traversers.getCurrentDataType() == g->getGraph()->get_vertex_dtype());
        if(!vertex && traversers.getCurrentDataType() != g->getGraph()->get_edge_dtype()) {
            throw std::domain_error("Can't get an element map for something other than a vertex or edge");
        }

        if(traversers.empty()) return;
        
        auto p = this->predicate;
        auto prop_name = this->property_key_or_label;
        traversers.advance([&g, p, prop_name, vertex](auto& traverser_data, auto& traverser_se, auto& traverser_path_info){
            maelstrom::vector ix_found;
            maelstrom::vector found_values;
            
            if(vertex) {
                std::tie(
                    found_values,
                    ix_found
                ) = g->getGraph()->get_vertex_properties(prop_name, traverser_data, p.operand.has_value());
            } else {
                std::tie(
                    found_values,
                    ix_found
                ) = g->getGraph()->get_edge_properties(prop_name, traverser_data, p.operand.has_value());
            }

            auto found_elements = maelstrom::select(traverser_data, ix_found);

            if(p.operand.has_value()) {
                // filter down found_vertices using found_values
                auto ix_matches = maelstrom::filter(
                    found_values,
                    p.comparison,
                    p.operand
                );
                found_values.clear();

                // TODO find a way to process multiple vectors at once
                found_elements = maelstrom::select(found_elements, ix_matches);
                ix_found = maelstrom::select(ix_found, ix_matches);
                ix_matches.clear();
            }

            return std::make_pair(
                std::move(found_elements),
                std::move(ix_found)
            );
        });
    }

}