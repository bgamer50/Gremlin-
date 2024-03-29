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
        Vertex v = this->has_label ? trv->getGraph()->add_vertex(this->label) : trv->getGraph()->add_vertex();
        auto vertex_dtype = trv->getTraversalSource()->get_dtype(v);
        std::vector<std::any> anys = {vertex_dtype.serialize(v)}; // Vertex isn't castable to a primitive so calling serialize manually is necessary
        
        traversers.reinitialize(
            std::move(maelstrom::make_vector_from_anys(traversers.getCurrentMemType(), trv->getTraversalSource()->get_dtype(v), anys)),
            std::move(std::unordered_map<std::string, maelstrom::vector>()),
            std::move(gremlinxx::traversal::PathInfo())
        );
    }

}