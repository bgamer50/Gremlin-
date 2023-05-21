#pragma once

#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include "step/TraversalStep.h"
#include "structure/Direction.h"

class Traverser;
class GraphTraversal;

#define VERTEX_STEP 0x80

enum GraphStepType{VERTEX, EDGE};

class VertexStep : public TraversalStep {
	private:
		Direction direction;
		std::set<std::string> edge_labels;
		GraphStepType gsType;
	public:
		VertexStep(Direction dir, std::vector<std::string> edge_labels_arg, GraphStepType gsType_arg);

		VertexStep(Direction dir, GraphStepType gsType_arg);

		inline Direction get_direction() {
			return this->direction;
		}

		inline std::set<std::string> get_labels() {
			return this->edge_labels;
		}

		inline GraphStepType get_type() {
			return this->gsType;
		}

		using TraversalStep::getInfo;
		virtual std::string getInfo();

		virtual void apply(GraphTraversal* traversal, TraverserSet& traversers);
};
