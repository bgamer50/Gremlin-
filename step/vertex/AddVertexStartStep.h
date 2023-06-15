#pragma once

class GraphTraversal;
class Traverser;

#include "step/TraversalStep.h"
#include "traversal/Traverser.h"

#include <string>
#include <vector>

#define ADD_VERTEX_START_STEP 0x70

namespace gremlinxx {

	class AddVertexStartStep: public TraversalStep {
		private:
			std::string label;
			bool has_label;
		public:
			AddVertexStartStep(std::string label_arg);

			AddVertexStartStep();
			
			using TraversalStep::getInfo;
			virtual std::string getInfo();

			virtual void apply(GraphTraversal* trv, gremlinxx::traversal::TraverserSet& traversers);
	};

}