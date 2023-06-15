#include "step/vertex/AddVertexStartStep.h"
#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"
#include "structure/Graph.h"

namespace gremlinxx {
        
    AddVertexStartStep::AddVertexStartStep(std::string label_arg)
    : TraversalStep(MAP, ADD_VERTEX_START_STEP) {
        this->label = label_arg;
        this->has_label = true;
    }

    AddVertexStartStep::AddVertexStartStep()
    : TraversalStep(MAP, ADD_VERTEX_START_STEP) {
        has_label = false;
    }

    std::string AddVertexStartStep::getInfo() {
        std::string info = "AddVertexStartStep(";
        info += has_label ? label : "";
        info += ")";
        return info;
    }

    void AddVertexStartStep::apply(GraphTraversal* trv, gremlinxx::traversal::TraverserSet& traversers) {
        Vertex* v = this->has_label ? trv->getGraph()->add_vertex(this->label) : trv->getGraph()->add_vertex();

        std::vector<boost::any> anys = {boost::any(v)};
        
        traversers.reinitialize(
            std::move(maelstrom::make_vector_from_anys(traversers.getCurrentMemType(), anys)),
            std::move(std::unordered_map<std::string, maelstrom::vector>()),
            std::move(gremlinxx::traversal::PathInfo())
        );
    }

}