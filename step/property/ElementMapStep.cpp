#include "step/property/ElementMapStep.h"

#include "traversal/GraphTraversal.h"
#include "step/TraversalStep.h"
#include "structure/Property.h"
#include "structure/Vertex.h"
#include "structure/Edge.h"
#include "structure/Graph.h"
#include "util/gremlin_utils.h"

#include "maelstrom/algorithms/intersection.h"
#include "maelstrom/algorithms/select.h"

namespace gremlinxx {
        
    ElementMapStep::ElementMapStep(std::vector<std::string>& keys)
    : TraversalStep(MAP, ELEMENTMAP_STEP) {
        this->keys = std::vector<std::string>(keys.begin(), keys.end());
    }

    void ElementMapStep::modulate_by(std::any arg) { 
        this->by_traversal = std::any_cast<GraphTraversal*>(arg);
    }

    std::string ElementMapStep::getInfo() {
        std::string s = "ElementMapStep{";
        for(std::string key : this->keys) s += key + ",";
        s += "}";
        return s;
    }

    void ElementMapStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        if(traversers.empty()) return;

        auto graph = traversal->getGraph();
        auto& prop_keys = this->keys;

        auto traverser_data = traversers.getTraverserData();

        std::vector<maelstrom::vector> values;
        maelstrom::vector origin;

        bool vertex = (traverser_data.get_dtype() == graph->get_vertex_dtype());
        if(!vertex && traverser_data.get_dtype() != graph->get_edge_dtype()) {
            throw std::domain_error("Can't get an element map for something other than a vertex or edge");
        }

        for(std::string key : prop_keys) {
            maelstrom::vector next_values;
            maelstrom::vector ix;

            if(vertex) {
                std::tie(next_values, ix) = graph->get_vertex_properties(key, traverser_data, true);
            } else {
                std::tie(next_values, ix) = graph->get_edge_properties(key, traverser_data, true);
            }

            traverser_data = std::move(maelstrom::select(traverser_data, ix));

            if(origin.empty()) {
                origin = std::move(ix);
            } else {
                origin = maelstrom::select(origin, ix);
                for(maelstrom::vector& v : values) v = maelstrom::select(v, ix);
            }

            values.push_back(std::move(next_values));
        }

        // Use advance to reorder the traversers
        traversers.advance([&origin, &traverser_data](auto& old_traverser_data, auto& traverser_se, auto& traverser_paths){
            return std::make_pair(
                std::move(traverser_data),
                std::move(origin)
            );
        });

        traverser_data = std::move(traversers.getTraverserData());

        traversers.set_side_effects(ELEMENTMAP_ID_KEY, std::move(maelstrom::vector(traverser_data, false)));
        
        traversers.set_side_effects(
            ElEMENTMAP_LABEL_KEY,
            vertex ? std::move(graph->get_vertex_labels(traverser_data)) : std::move(graph->get_edge_labels(traverser_data))
        );
        
        for(size_t i = 0; i < prop_keys.size(); ++i) traversers.set_side_effects(prop_keys[i], std::move(values[i]));
        
    }
}