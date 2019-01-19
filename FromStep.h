#ifndef FROM_STEP_H
#define FROM_STEP_H

#include "TraversalStep.h"
#include "GraphTraversal.h"
class Vertex;

#define FROM_STEP 0x90

class FromStep : public TraversalStep {
	private:
		GraphTraversal* from_traversal;
	public:
		FromStep(std::string side_effect_label);

		FromStep(Vertex* to_vertex);

		FromStep(GraphTraversal* from_vertex_traversal);

		GraphTraversal* getTraversal();

		virtual std::string getInfo();
};

#endif