#ifndef ADD_VERTEX_STEP_H
#define ADD_VERTEX_STEP_H

#include "TraversalStep.h"
#include <string>

#define ADD_VERTEX_STEP 0x71

class AddVertexStep: public TraversalStep {
	private:
		std::string label;
		bool has_label;
	public:
		AddVertexStep(std::string label_arg);
		AddVertexStep();
		virtual std::string getInfo();
};

#endif