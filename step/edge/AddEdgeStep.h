#ifndef ADD_EDGE_STEP_H
#define ADD_EDGE_STEP_H

#include "GraphTraversal.h"
#include "TraversalStep.h"
#include <string>
#include <vector>

#define ADD_EDGE_STEP 0x73

class AddEdgeStep: public TraversalStep {
	private:
		std::string label;
		GraphTraversal* out_vertex_traversal; // filled in at runtime
		GraphTraversal* in_vertex_traversal; // filled in at runtime
	public:
		AddEdgeStep(std::string label_arg)
		: TraversalStep(MAP, ADD_EDGE_STEP) {
			label = label_arg;
			out_vertex_traversal = NULL;
			in_vertex_traversal = NULL;
		}

		virtual std::string getInfo() {
			std::string info = "AddEdgeStep(";
			info += label + ")";
			return info;
		}

		GraphTraversal* get_out_traversal() { return this->out_vertex_traversal; }
		GraphTraversal* get_in_traversal() { return this->in_vertex_traversal; }
		void set_out_traversal(GraphTraversal* new_traversal) { this->out_vertex_traversal = new_traversal; }
		void set_in_traversal(GraphTraversal* new_traversal) { this->in_vertex_traversal = new_traversal; }
		std::string get_label() { return this->label; }
};

#endif