#ifndef ADD_EDGE_STEP_H
#define ADD_EDGE_STEP_H

#include "TraversalStep.h"
#include <string>

#define ADD_EDGE_STEP 0x73

class AddEdgeStep: public TraversalStep {
	private:
		std::string label;
		GraphTraversal* out_vertex_traversal;
		GraphTraversal* in_vertex_traversal;
	public:
		AddEdgeStep(std::string label_arg);
		virtual std::string getInfo();
		void addModulator(TraversalStep* modulatorStep);
};

#endif