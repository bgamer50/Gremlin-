#pragma once

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
		GraphStep(GraphStepType gsType_arg, std::vector<boost::any> eids);

		using TraversalStep::getInfo;
		virtual std::string	getInfo();

		inline GraphStepType getType() { return this->gs_type; }

		inline std::vector<boost::any>& get_element_ids() { return this->element_ids; }

		virtual void apply(GraphTraversal* trv, TraverserSet& traversers);
};

