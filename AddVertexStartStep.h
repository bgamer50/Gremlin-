#ifndef ADD_VERTEX_START_STEP_H
#define ADD_VERTEX_START_STEP_H

#include "TraversalStep.h"
#include <string>

#define ADD_VERTEX_START_STEP 0x70

class AddVertexStartStep: public TraversalStep {
	private:
		std::string label;
		bool has_label;
	public:
		AddVertexStartStep(std::string label_arg);
		AddVertexStartStep();
		virtual std::string getInfo();
};

#endif