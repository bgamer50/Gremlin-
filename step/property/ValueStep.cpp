#include "step/property/ValueStep.h"

#include "traversal/GraphTraversal.h"
#include "traversal/GraphTraversalSource.h"

#include "maelstrom/algorithms/intersection.h"
#include "maelstrom/algorithms/sort.h"
#include "maelstrom/algorithms/select.h"

#include "structure/Vertex.h"
#include "structure/Edge.h"
#include "structure/Graph.h"

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

        traversers.advance([&g, &prop_names](auto& traverser_data, auto& traverser_se, auto& traverser_path_info){
            // TODO efficiently get multiple properties at once
            // TODO sort

            // Sort a copy of the traverser data
            auto traverser_data_copy = maelstrom::vector(traverser_data, false);
            auto original_unsorted_ix = maelstrom::sort(traverser_data_copy);

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
                    traverser_data_copy,
                    true
                );

                auto current_vertices_sorted_ix = maelstrom::sort(current_vertices);
                current_values = maelstrom::select(current_values, current_vertices_sorted_ix);
                current_vertices_sorted_ix.clear();

                // the intersection index is the output origin for the current property
                auto intersection_ix = maelstrom::intersection(traverser_data_copy, current_vertices, true);
                intersection_ix = maelstrom::select(original_unsorted_ix, intersection_ix);
                
                if(values.empty()) {
                    values = std::move(current_values);
                    output_origin = std::move(intersection_ix);
                } else {
                    if(values.get_dtype() != current_values.get_dtype()) {
                        auto current_dtype = current_values.get_dtype();
                        auto global_dtype = values.get_dtype();
                        // Promote to larger dtype, up to user to make sure this is ok
                        auto new_dtype = (maelstrom::size_of(global_dtype) < maelstrom::size_of(current_dtype)) ? current_dtype : global_dtype;
                        if(current_dtype != new_dtype) current_values = current_values.astype(new_dtype);
                        if(global_dtype != new_dtype) values = values.astype(new_dtype);
                    }

                    values.insert(values.size(), current_values);
                    output_origin.insert(values.size(), intersection_ix);
                }
                
            }                

            return std::make_pair(
                std::move(values),
                std::move(output_origin)
            );
        });
    }

}