#pragma once

#include "step/TraversalStep.h"
#include "traversal/GraphTraversal.h"

#include <string>
#include <any>

#define FROM_STEP 0x90

namespace gremlinxx {
	class Vertex;
		
	class FromStep : public TraversalStep {
		private:
			std::any arg;
			std::optional<GraphTraversal> traversal;
		public:
			FromStep(std::string side_effect_label);

			FromStep(Vertex to_vertex);

			FromStep(GraphTraversal from_vertex_traversal);

			using TraversalStep::getInfo;
			virtual std::string getInfo();

			inline std::any get_arg() {
				if(!arg.has_value()) throw std::runtime_error("step does not contain arg");
				return arg; 
			}

			inline GraphTraversal& get_traversal() {
				if(!traversal) throw std::runtime_error("step does not contain traversal");
				return traversal.value();
			}
	};

}