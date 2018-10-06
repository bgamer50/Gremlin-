#ifndef ADD_EDGE_START_STEP_H
#define ADD_EDGE_START_STEP_H

#include "TraversalStep.h"
#include <string>

#define ADD_EDGE_START_STEP 0x72

class AddEdgeStartStep: public TraversalStep {
	private:
		std::string label;
	public:
		AddEdgeStartStep(std::string label_arg);
		virtual std::string getInfo();
};

#endif