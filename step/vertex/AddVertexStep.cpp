#include "step/vertex/AddVertexStep.h"
#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"
#include "structure/Graph.h"

namespace gremlinxx {

    AddVertexStep::AddVertexStep(std::string label_arg)
    : TraversalStep(MAP, ADD_VERTEX_STEP) {
        this->label = label_arg;
        this->has_label = true;
    }

    AddVertexStep::AddVertexStep()
    : TraversalStep(MAP, ADD_VERTEX_STEP) {
        this->has_label = false;
    }

    std::string AddVertexStep::getInfo() {
        std::string info = "AddVertexStep(";
        info += has_label ? label : "";
        info += ")";
        return info;
    }

    void AddVertexStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        auto graph = traversal->getGraph();
        std::string label_str = this->label;

        // For each traverser, a new Vertex should be created and replace the original traverser
        traversers.advance([&graph, label_str](auto traverser_data, auto traverser_se, auto traverser_path_info){
            return std::make_pair(
                std::move(graph->add_vertices(traverser_data.size(), label_str)),
                maelstrom::vector()
            );
        });
    }

}