#pragma once

class GraphTraversal;
class Vertex;

#include "step/TraversalStep.h"
#include <string>
#include <boost/any.hpp>

#define TO_STEP 0x91

namespace gremlinxx {

	class ToStep : public TraversalStep {
		private:
			boost::any arg;
		public:
			ToStep(std::string side_effect_label);

			ToStep(Vertex* to_vertex);

			ToStep(GraphTraversal* to_vertex_traversal);

			inline boost::any get() { return arg; }

			using TraversalStep::getInfo;
			virtual std::string getInfo();
	};

}