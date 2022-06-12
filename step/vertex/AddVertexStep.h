#ifndef ADD_VERTEX_STEP_H
#define ADD_VERTEX_STEP_H

#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"
#include <string>
#include <vector>

#define ADD_VERTEX_STEP 0x71

class AddVertexStep: public TraversalStep {
	private:
		std::string label;
		bool has_label;
	public:
		AddVertexStep(std::string label_arg)
		: TraversalStep(MAP, ADD_VERTEX_STEP) {
			label = label_arg;
			has_label = true;
		}

		AddVertexStep()
		: TraversalStep(MAP, ADD_VERTEX_STEP) {
			has_label = false;
		}

		virtual std::string getInfo() {
			std::string info = "AddVertexStep(";
			info += has_label ? label : "";
			info += ")";
			return info;
		}

		virtual void apply(GraphTraversal* traversal, TraverserSet& traversers) {
			// For each traverser, a new Vertex should be created and replace the original traverser
			std::for_each(traversers.begin(), traversers.end(), [&, this](Traverser& trv) {
				Vertex* v = this->has_label ? traversal->getGraph()->add_vertex(this->label) : traversal->getGraph()->add_vertex();
				trv.replace_data(v);
			});
		}
};

#endif