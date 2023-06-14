#include "step/property/ValueStep.h"
#include "structure/Vertex.h"
#include "structure/Edge.h"
#include "structure/VertexProperty.h"
#include "traversal/GraphTraversal.h"

#include "maelstrom/algorithms/intersection.h"
#include "maelstrom/algorithms/sort.h"
#include "maelstrom/algorithms/select.h"

#include <sstream>

namespace gremlinxx {
        
    ValueStep::ValueStep(std::vector<std::string> property_keys)
    : TraversalStep(MAP, VALUE_STEP) {
        this->keys = property_keys;
    }

    std::string ValueStep::getInfo() {
        std::stringstream sx;
        sx << "ValueStep{";
        for(std::string s : this->keys) sx << s << ", ";
        sx << "}";

        return sx.str();
    }

    void ValueStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        auto g = traversal->getTraversalSource();
        auto& prop_names = this->keys;

        traversers.advance([&g, &prop_names](auto traverser_data, auto traverser_se, auto traverser_path_info){
            // TODO efficiently get multiple properties at once
            // TODO sort

            maelstrom::vector values;
            maelstrom::vector output_origin;

            for(std::string key : prop_names) {
                maelstrom::vector current_vertices;
                maelstrom::vector current_values;

                std::tie(
                    current_vertices,
                    current_values
                ) = g->getGraph()->getVertexProperties(
                    key,
                    traverser_data,
                    true
                );

                // the intersection index is the output origin for the current property
                auto intersection_ix = maelstrom::intersection(traverser_data, current_vertices);
                
                if(values.empty())
                    // do something
                
                if(output_origin())
                    // do something
            }
            

            return std::make_pair(
                maelstrom::vector(),
                maelstrom::vector()
            );
        });
    }

}