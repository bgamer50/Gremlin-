#ifndef GRAPH_STEP_H
#define GRAPH_STEP_H
#include <string>
#include <vector>
#include "TraversalStep.h"

#define GRAPH_STEP 0x81

enum GraphStepType {VERTEX, EDGE};

class GraphStep : public TraversalStep {
	private:
		GraphStepType gs_type;
		std::vector<void*> element_ids;
	public:
		GraphStep(GraphStepType gsType_arg, std::vector<void*> eids);
		virtual std::string	getInfo();
		GraphStepType getType();
};

#endif