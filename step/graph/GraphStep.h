#ifndef GRAPH_STEP_H
#define GRAPH_STEP_H
#include <string>
#include <vector>
#include <boost/any.hpp>
#include "step/TraversalStep.h"
#include "traversal/Traverser.h"

#define GRAPH_STEP 0x81

enum GraphStepType {VERTEX, EDGE};

class GraphStep : public TraversalStep {
	protected:
		GraphStepType gs_type;
		std::vector<boost::any> element_ids;
	public:
		GraphStep(GraphStepType gsType_arg, std::vector<boost::any> eids)
		: TraversalStep(MAP, GRAPH_STEP) {
			this->gs_type = gsType_arg;
			for(boost::any id_ctr : eids) this->element_ids.push_back(id_ctr);
		}

		virtual std::string	getInfo() {
			std::string info = "GraphStep(";
			info += this->gs_type == VERTEX ? "VERTEX" : "EDGE";
			info = info + ", " + (element_ids.size() > 0 ? "{...}" : "{}");
			return info + ")";
		}

		GraphStepType getType() { return this->gs_type; }

		std::vector<boost::any>& get_element_ids() { return this->element_ids; }

		virtual void apply(GraphTraversal* trv, TraverserSet& traversers) {
			throw std::runtime_error("Unsupported operation!");
		}
};

#endif