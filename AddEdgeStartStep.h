#ifndef ADD_EDGE_START_STEP_H
#define ADD_EDGE_START_STEP_H

#include "TraversalStep.h"
#include <string>

#define ADD_EDGE_START_STEP 0x72

class AddEdgeStartStep: public TraversalStep {
	private:
		bool has_traversals;
		std::string label;
		GraphTraversal* out_vertex_traversal; // filled in at runtime
		GraphTraversal* in_vertex_traversal; // filled in at runtime
	public:
		AddEdgeStartStep(std::string label_arg);
		virtual std::string getInfo();
		GraphTraversal* get_out_traversal();
		GraphTraversal* get_in_traversal();
		void set_out_traversal(GraphTraversal* new_traversal);
		void set_in_traversal(GraphTraversal* new_traversal);
};

#endif