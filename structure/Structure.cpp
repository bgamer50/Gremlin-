#include "structure/Element.h"
#include "structure/Vertex.h"
#include "structure/Edge.h"
#include "structure/Direction.h"
#include "structure/Order.h"

#include "structure/Graph.h"

#include "maelstrom/algorithms/count_unique.h"

namespace gremlinxx {
    std::pair<maelstrom::vector, maelstrom::vector> Graph::degree(maelstrom::vector& current_vertices, std::vector<std::string>& labels, gremlinxx::Direction dir) {
        maelstrom::vector output_origin;
        std::tie(std::ignore, output_origin) = this->V(current_vertices, labels, dir);
        
        maelstrom::vector degrees;
        std::tie(output_origin, degrees) = maelstrom::count_unique(
            output_origin,
            current_vertices.size(),
            false
        );

        return std::make_pair(
            std::move(degrees),
            std::move(output_origin)
        );
    }
}