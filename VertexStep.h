#ifndef VERTEX_STEP_H
#define VERTEX_STEP_H
#include <string>
#include <vector>
#include "TraversalStep.h"
#include "Direction.h"
#include "GraphStep.h"

#define VERTEX_STEP 0x80

class VertexStep : public TraversalStep {
	private:
		Direction direction;
		std::vector<std::string>* edge_labels;
		GraphStepType gsType;
	public:
		VertexStep(Direction dir, std::vector<std::string> edge_labels_arg, GraphStepType gsType_arg);
		VertexStep(Direction dir, GraphStepType gsType_arg);
		virtual std::string getInfo();
};

#endif