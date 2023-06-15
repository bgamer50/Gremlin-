#include "step/property/ElementMapStep.h"

#include "traversal/GraphTraversal.h"
#include "step/TraversalStep.h"
#include "structure/Property.h"
#include "structure/Vertex.h"
#include "structure/Edge.h"
#include "util/gremlin_utils.h"

#include "maelstrom/algorithms/intersection.h"
#include "maelstrom/algorithms/select.h"

namespace gremlinxx {
        
    ElementMapStep::ElementMapStep(std::vector<std::string>& keys)
    : TraversalStep(MAP, ELEMENTMAP_STEP) {
        this->keys = std::vector<std::string>(keys.begin(), keys.end());
    }

    void ElementMapStep::modulate_by(boost::any arg) { 
        this->by_traversal = boost::any_cast<GraphTraversal*>(arg);
    }

    std::string ElementMapStep::getInfo() {
        std::string s = "ElementMapStep{";
        for(std::string key : this->keys) s += key + ",";
        s += "}";
        return s;
    }

    void ElementMapStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        auto graph = traversal->getGraph();
        auto& prop_keys = this->keys;

        auto traverser_data = traversers.getTraverserData();

        std::vector<maelstrom::vector> values;
        maelstrom::vector origin;

        for(std::string key : prop_keys) {
            maelstrom::vector next_values;
            maelstrom::vector next_origin;
            std::tie(next_origin, next_values) = graph->getVertexProperties(key, traverser_data, true);

            auto ix = maelstrom::intersection(traverser_data, next_origin);
            next_origin.clear();
            traverser_data = maelstrom::select(traverser_data, ix);

            if(origin.empty()) {
                origin = ix;
            } else {
                origin = maelstrom::select(origin, ix);
                for(maelstrom::vector& v : values) v = maelstrom::select(v, ix);
            }

            values.push_back(std::move(next_values));
        }

        // Use advance to reorder the traversers
        traversers.advance([&origin, &traverser_data](auto old_traverser_data, auto traverser_se, auto traverser_paths){
            return std::make_pair(
                std::move(traverser_data),
                std::move(origin)
            );
        });

        traverser_data = traversers.getTraverserData();
        traversers.set_side_effects(ELEMENTMAP_ID_KEY, std::move(maelstrom::vector(traverser_data)));
        traversers.set_side_effects(ElEMENTMAP_LABEL_KEY, std::move(graph->getVertexLabels(traverser_data)));
        for(size_t i = 0; i < prop_keys.size(); ++i) traversers.set_side_effects(prop_keys[i], std::move(values[i]));
    }
}