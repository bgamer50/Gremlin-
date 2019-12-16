#ifndef ADD_EDGE_START_STEP_H
#define ADD_EDGE_START_STEP_H

#define ADD_EDGE_START_STEP 0x72

#include <string>
#include <vector>

class GraphTraversalSource;
class GraphTraversal;
class Traverser;
class TraversalStep;
typedef std::vector<Traverser> TraverserSet; // TODO remove this forward dec?

class AddEdgeStartStep: public TraversalStep {
	private:
		std::string label;
		GraphTraversal* out_vertex_traversal; // filled in at runtime
		GraphTraversal* in_vertex_traversal; // filled in at runtime
	public:
		AddEdgeStartStep(std::string label_arg);
		
		virtual std::string getInfo() {
			std::string info = "AddEdgeStartStep(";
			info += label + ")";
			return info;
		}


		GraphTraversal* get_out_traversal();
		GraphTraversal* get_in_traversal();
		void set_out_traversal(GraphTraversal* new_traversal);
		void set_in_traversal(GraphTraversal* new_traversal);
		std::string get_label() { return this->label; }

		virtual void apply(GraphTraversal* trv, TraverserSet& traversers);
};

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

GraphTraversal* AddEdgeStartStep::get_out_traversal() { return this->out_vertex_traversal; }
GraphTraversal* AddEdgeStartStep::get_in_traversal() { return this->in_vertex_traversal; }
void AddEdgeStartStep::set_out_traversal(GraphTraversal* new_traversal) { this->out_vertex_traversal = new_traversal; }
void AddEdgeStartStep::set_in_traversal(GraphTraversal* new_traversal) { this->in_vertex_traversal = new_traversal; }

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

#endif