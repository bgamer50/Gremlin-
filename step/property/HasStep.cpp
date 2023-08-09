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
        if(traversers.getCurrentDataType() != g->getGraph()->get_vertex_dtype()) {
            throw std::runtime_error("can't apply has step to objects other than vertices!");
        }
        
        auto p = this->predicate;
        auto prop_name = this->property_key_or_label;
        traversers.advance([&g, p, prop_name](auto& traverser_data, auto& traverser_se, auto& traverser_path_info){
            maelstrom::vector ix_found;
            maelstrom::vector found_values;
            std::tie(
                found_values,
                ix_found
            ) = g->getGraph()->get_vertex_properties(prop_name, traverser_data, p.operand.has_value());

            auto found_vertices = maelstrom::select(traverser_data, ix_found);

            if(p.operand.has_value()) {
                // filter down found_vertices using found_values
                auto ix_matches = maelstrom::filter(
                    found_values,
                    p.comparison,
                    p.operand
                );
                found_values.clear();

                // TODO find a way to process multiple vectors at once
                found_vertices = maelstrom::select(found_vertices, ix_matches);
                ix_found = maelstrom::select(ix_found, ix_matches);
                ix_matches.clear();
            }

            return std::make_pair(
                std::move(found_vertices),
                std::move(ix_found)
            );
        });
    }

}