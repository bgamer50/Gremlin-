#ifndef TO_STEP_H
#define TO_STEP_H

#include "GraphTraversal.h"

#define TO_STEP 0x91

class ToStep : public TraversalStep {
	private:
		GraphTraversal<void*, Vertex>* to_traversal;
	public:
		ToStep(std::string side_effect_label);

		ToStep(Vertex* to_vertex);

		ToStep(GraphTraversal<void*, Vertex>* to_vertex_traversal);

		GraphTraversal<void*, Vertex>* getTraversal();

		virtual std::string getInfo();
};

#endif