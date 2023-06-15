#pragma once

class GraphTraversal;
class Vertex;

#include "step/TraversalStep.h"

#include <string>
#include <boost/any.hpp>

#define FROM_STEP 0x90

namespace gremlinxx {
		
	class FromStep : public TraversalStep {
		private:
			boost::any arg;
		public:
			FromStep(std::string side_effect_label);

			FromStep(Vertex* to_vertex);

			FromStep(GraphTraversal* from_vertex_traversal);

			using TraversalStep::getInfo;
			virtual std::string getInfo();

			inline boost::any get() { return arg; }
	};

}