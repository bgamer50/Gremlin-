#include "step/property/HasNotStep.h"
#include "traversal/GraphTraversal.h"
#include "traversal/GraphTraversalSource.h"
#include "structure/Graph.h"

#include "maelstrom/algorithms/remove_if.h"
#include "maelstrom/algorithms/assign.h"
#include "maelstrom/algorithms/arange.h"
#include "maelstrom/algorithms/set.h"
#include "maelstrom/algorithms/select.h"

namespace gremlinxx {

    void HasNotStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        if(traversers.empty()) return;

        GraphTraversalSource* g = traversal->getTraversalSource();
        bool vertex = (traversers.getCurrentDataType() == g->getGraph()->get_vertex_dtype());
        if(!vertex && traversers.getCurrentDataType() != g->getGraph()->get_edge_dtype()) {
            throw std::domain_error("Can't get an element map for something other than a vertex or edge");
        }
        
        auto prop_name = this->property_key;
        traversers.advance([&g, prop_name, vertex](auto& traverser_data, auto& traverser_se, auto& traverser_path_info){
            maelstrom::vector ix_found;
            
            if(vertex) {
                std::tie(
                    std::ignore,
                    ix_found
                ) = g->getGraph()->get_vertex_properties(prop_name, traverser_data, false);
            } else {
                std::tie(
                    std::ignore,
                    ix_found
                ) = g->getGraph()->get_edge_properties(prop_name, traverser_data, false);
            }

            maelstrom::vector stencil(
                traverser_data.get_mem_type(),
                maelstrom::uint64,
                traverser_data.size()
            );
            maelstrom::set(stencil, (size_t)0);

            maelstrom::vector ones(
                traverser_data.get_mem_type(),
                maelstrom::uint64,
                ix_found.size()
            );
            maelstrom::set(ones, (size_t)1);

            maelstrom::assign(stencil, ix_found, ones);
            ix_found.clear();
            ones.clear();

            auto origin = maelstrom::arange(traverser_data.get_mem_type(), traverser_data.size());
            maelstrom::remove_if(origin, stencil);
            stencil.clear();

            auto found_elements = maelstrom::select(traverser_data, origin);

            return std::make_pair(
                std::move(found_elements),
                std::move(ix_found)
            );
        });
    }

    std::string HasNotStep::getInfo() {
        return "HasNotStep(" + this->property_key + ")";
    }

}