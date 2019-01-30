#ifndef ADD_VERTEX_START_STEP_H
#define ADD_VERTEX_START_STEP_H

#include "TraversalStep.h"
#include <string>
#include <vector>

#define ADD_VERTEX_START_STEP 0x70

class AddVertexStartStep: public TraversalStep {
	private:
		std::string label;
		bool has_label;
	public:
		AddVertexStartStep(std::string label_arg)
		: TraversalStep(MAP, ADD_VERTEX_START_STEP) {
			label = label_arg;
			has_label = true;
		}

		AddVertexStartStep()
		: TraversalStep(MAP, ADD_VERTEX_START_STEP) {
			has_label = false;
		}
		
		virtual std::string getInfo() {
			std::string info = "AddVertexStartStep(";
			info += has_label ? label : "";
			info += ")";
			return info;
		}
};

#endif