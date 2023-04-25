#include "step/vertex/AddVertexStep.h"
#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"
#include "structure/Graph.h"

AddVertexStep::AddVertexStep(std::string label_arg)
: TraversalStep(MAP, ADD_VERTEX_STEP) {
    label = label_arg;
    has_label = true;
}

AddVertexStep::AddVertexStep()
: TraversalStep(MAP, ADD_VERTEX_STEP) {
    has_label = false;
}

std::string AddVertexStep::getInfo() {
    std::string info = "AddVertexStep(";
    info += has_label ? label : "";
    info += ")";
    return info;
}

void AddVertexStep::apply(GraphTraversal* traversal, TraverserSet& traversers) {
    // For each traverser, a new Vertex should be created and replace the original traverser
    std::for_each(traversers.begin(), traversers.end(), [&, this](Traverser& trv) {
        Vertex* v = this->has_label ? traversal->getGraph()->add_vertex(this->label) : traversal->getGraph()->add_vertex();
        trv.replace_data(v);
    });
}