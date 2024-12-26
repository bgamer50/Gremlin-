#include "step/vertex/DegreeStep.h"
#include "traversal/GraphTraversal.h"
#include "structure/Graph.h"

#include <sstream>

namespace gremlinxx {

    DegreeStep::DegreeStep(Direction dir, std::set<std::string> edge_labels_arg)
    : TraversalStep(MAP, DEGREE_STEP) {
        this->direction = dir;
        this->edge_labels = edge_labels_arg;
    }

    std::string DegreeStep::getInfo() {
        std::string dir_string = (this->direction == IN ? "IN" : this->direction == OUT ? "OUT" : "BOTH");
        std::stringstream sx;
        sx << "DegreeStep(" << dir_string << ", " << "[";
        
        if(this->edge_labels.empty()) {
            return sx.str() + "])";
        } else {
            for(std::string s : this->edge_labels) sx << s << ", ";
            auto output_str = sx.str();
            return output_str.substr(0, output_str.size() - 2) + "])";
        }
    }

    void DegreeStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        std::vector label_vec(this->edge_labels.begin(), this->edge_labels.end());
        auto dir = this->direction;

        traversers.advance([&label_vec, traversal, dir](auto data, auto side_effects, auto paths){
            maelstrom::vector degrees;
            maelstrom::vector origins;

            std::tie(degrees, origins) = traversal->getGraph()->degree(
                data,
                label_vec,
                dir
            );

            return std::make_pair(
                std::move(degrees),
                std::move(origins)
            );
        });
    }

}