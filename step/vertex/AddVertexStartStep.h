#ifndef ADD_VERTEX_START_STEP_H
#define ADD_VERTEX_START_STEP_H

#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"
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

		virtual void apply(GraphTraversal* trv, TraverserSet& traversers) {
			Vertex* v = this->has_label ? trv->getGraph()->add_vertex(this->label) : trv->getGraph()->add_vertex();
			traversers.push_back(Traverser(v));
		}
};

#endif