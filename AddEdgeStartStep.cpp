#include "AddEdgeStartStep.h"
#include "TraversalStep.h"
#include <string>
#include <vector>

AddEdgeStartStep::AddEdgeStartStep(std::string label_arg)
: TraversalStep(map, ADD_EDGE_START_STEP) {
	label = label_arg;
	has_traversals = false;
}

// Return something like AddEdgeStarStep(label)
std::string AddEdgeStartStep::getInfo() {
	std::string info = "AddVertexStartStep(";
	info += label + ")";
	return info;
}

GraphTraversal* AddEdgeStartStep::get_out_traversal() { return this->out_vertex_traversal; }
GraphTraversal* AddEdgeStartStep::get_in_traversal() { return this->in_vertex_traversal; }
void AddEdgeStartStep::set_out_traversal(GraphTraversal* new_traversal) { this->out_vertex_traversal = new_traversal; }
void AddEdgeStartStep::set_in_traversal(GraphTraversal* new_traversal) { this->in_vertex_traversal = new_traversal; }