#ifndef TO_STEP_H
#define TO_STEP_H

#include "GraphTraversal.h"

#define TO_STEP 0x91

class ToStep : public TraversalStep {
	private:
		GraphTraversal* to_traversal;
	public:
		ToStep(std::string side_effect_label);

		ToStep(Vertex* to_vertex);

		ToStep(GraphTraversal* to_vertex_traversal);

		GraphTraversal* getTraversal();

		virtual std::string getInfo();
};

#endif