#ifndef ADD_EDGE_STEP_H
#define ADD_EDGE_STEP_H

#include "GraphTraversal.h"
#include "TraversalStep.h"
#include <string>

#define ADD_EDGE_STEP 0x73

class AddEdgeStep: public TraversalStep {
	private:
		std::string label;
		GraphTraversal<void*, Vertex>* out_vertex_traversal; // filled in at runtime
		GraphTraversal<void*, Vertex>* in_vertex_traversal; // filled in at runtime
	public:
		AddEdgeStep(std::string label_arg);
		virtual std::string getInfo();
		void addMODULATOR(TraversalStep* MODULATORStep);
		GraphTraversal<void*, Vertex>* get_out_traversal();
		GraphTraversal<void*, Vertex>* get_in_traversal();
		void set_out_traversal(GraphTraversal<void*, Vertex>* new_traversal);
		void set_in_traversal(GraphTraversal<void*, Vertex>* new_traversal);
		std::string get_label();
};

#endif