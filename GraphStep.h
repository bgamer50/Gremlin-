#ifndef GRAPH_STEP_H
#define GRAPH_STEP_H
#include <string>
#include <vector>
#include <boost/any.hpp>
#include "TraversalStep.h"

#define GRAPH_STEP 0x81

enum GraphStepType {VERTEX, EDGE};

class GraphStep : public TraversalStep {
	private:
		GraphStepType gs_type;
		std::vector<boost::any> element_ids;
	public:
		GraphStep(GraphStepType gsType_arg, std::vector<boost::any> eids);
		virtual std::string	getInfo();
		GraphStepType getType();
		std::vector<boost::any> get_element_ids();
};

#endif