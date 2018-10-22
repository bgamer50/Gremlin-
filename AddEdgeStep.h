#ifndef ADD_EDGE_STEP_H
#define ADD_EDGE_STEP_H

#include "TraversalStep.h"
#include "GraphTraversal.h"
#include <string>

#define ADD_EDGE_STEP 0x73

class AddEdgeStep: public TraversalStep {
	private:
		std::string label;
		GraphTraversal* out_vertex_traversal; // filled in at runtime
		GraphTraversal* in_vertex_traversal; // filled in at runtime
	public:
		AddEdgeStep(std::string label_arg);
		virtual std::string getInfo();
		void addModulator(TraversalStep* modulatorStep);
		GraphTraversal* get_out_traversal();
		GraphTraversal* get_in_traversal();
		void set_out_traversal(GraphTraversal* new_traversal);
		void set_in_traversal(GraphTraversal* new_traversal);
		std::string get_label();
};

#endif