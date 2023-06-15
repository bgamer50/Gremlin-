#pragma once

#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include "step/TraversalStep.h"
#include "structure/Direction.h"

#define VERTEX_STEP 0x80

namespace gremlinxx {

	enum VertexStepType{
		VERTEX_TO_VERTEX = 0,
		VERTEX_TO_EDGE = 1,
		EDGE_TO_VERTEX = 2
	};

	class VertexStep : public TraversalStep {
		private:
			Direction direction;
			std::set<std::string> edge_labels;
			VertexStepType vsType;
		public:
			VertexStep(Direction dir, std::vector<std::string> edge_labels_arg, VertexStepType vs_type);

			VertexStep(Direction dir, VertexStepType vs_type);

			inline Direction get_direction() {
				return this->direction;
			}

			inline std::set<std::string> get_labels() {
				return this->edge_labels;
			}

			inline VertexStepType get_type() {
				return this->vsType;
			}

			using TraversalStep::getInfo;
			virtual std::string getInfo();

			virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);
	};

}