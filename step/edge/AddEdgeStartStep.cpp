#include "step/edge/AddEdgeStartStep.h"

#include "traversal/GraphTraversal.h"
#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include "structure/Graph.h"
#include "structure/Vertex.h"
#include "structure/Edge.h"

AddEdgeStartStep::AddEdgeStartStep(std::string label_arg)
: TraversalStep(MAP, ADD_EDGE_START_STEP) {
	this->label = label_arg;
	this->out_vertex_traversal = NULL;
	this->in_vertex_traversal = NULL;
}

std::string AddEdgeStartStep::getInfo() {
    std::string info = "AddEdgeStartStep(";
    info += label + ")";
    return info;
}

void AddEdgeStartStep::modulate_from(boost::any arg) { 
    if(arg.type() == typeid(Vertex*)) {
        this->out_vertex_traversal = new GraphTraversal();
        this->out_vertex_traversal->setInitialTraversers({Traverser(arg)});
    }
    else if(arg.type() == typeid(GraphTraversal*)) this->out_vertex_traversal = boost::any_cast<GraphTraversal*>(arg); 
    else throw std::runtime_error("Invalid object passed in from() to AddEdgeStep");			
}

void AddEdgeStartStep::modulate_to(boost::any arg) {
    if(arg.type() == typeid(Vertex*)) {
        this->in_vertex_traversal = new GraphTraversal();
        this->in_vertex_traversal->setInitialTraversers({Traverser(arg)});
    }
    else if(arg.type() == typeid(GraphTraversal*)) this->in_vertex_traversal = boost::any_cast<GraphTraversal*>(arg);
    else throw std::runtime_error("Invalid object passed in to() to AddEdgeStep");		
}

void AddEdgeStartStep::apply(GraphTraversal* trv, TraverserSet& traversers) {
	// Need to check if there is enough info to add the Edge, then add it
	// if we can.
	// from() and to() are both always required here.
	GraphTraversalSource* my_traversal_source = trv->getTraversalSource();
	if(my_traversal_source == NULL) throw std::runtime_error("Cannot call this step from an anonymous traversal!\n");

	GraphTraversal from_traversal(my_traversal_source, this->out_vertex_traversal);
	GraphTraversal to_traversal(my_traversal_source, this->in_vertex_traversal);

	Vertex* from_vertex = boost::any_cast<Vertex*>(from_traversal.next());
	Vertex* to_vertex = boost::any_cast<Vertex*>(to_traversal.next());

	Edge* new_edge = trv->getGraph()->add_edge(from_vertex, to_vertex, label);
	traversers.push_back(Traverser(new_edge));
}
