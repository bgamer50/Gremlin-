#ifndef FROM_STEP_H
#define FROM_STEP_H

#include "TraversalStep.h"
#include "GraphTraversal.h"
class Vertex;

#define FROM_STEP 0x90

class FromStep : public TraversalStep {
	private:
		GraphTraversal<void*, Vertex>* from_traversal;
	public:
		FromStep(std::string side_effect_label);

		FromStep(Vertex* to_vertex);

		FromStep(GraphTraversal<void*, Vertex>* from_vertex_traversal);

		GraphTraversal<void*, Vertex>* getTraversal();

		virtual std::string getInfo();
};

#endif