#include "step/graph/GraphStep.h"

GraphStep::GraphStep(GraphStepType gsType_arg, std::vector<boost::any> eids)
: TraversalStep(MAP, GRAPH_STEP) {
    this->gs_type = gsType_arg;
    for(boost::any id_ctr : eids) this->element_ids.push_back(id_ctr);
}

std::string	GraphStep::getInfo() {
    std::string info = "GraphStep(";
    info += this->gs_type == VERTEX ? "VERTEX" : "EDGE";
    info = info + ", " + (element_ids.size() > 0 ? "{...}" : "{}");
    return info + ")";
}

void GraphStep::apply(GraphTraversal* trv, TraverserSet& traversers) {
    throw std::runtime_error("Unsupported operation!");
}