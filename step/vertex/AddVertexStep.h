#pragma once

#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include <string>
#include <vector>

#define ADD_VERTEX_STEP 0x71

namespace gremlinxx {

	class AddVertexStep: public TraversalStep {
		private:
			std::string label;
			bool has_label;
		public:
			AddVertexStep(std::string label_arg);

			AddVertexStep();

			using TraversalStep::getInfo;
			virtual std::string getInfo();

			virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);
	};

}