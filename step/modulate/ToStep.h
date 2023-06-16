#pragma once

#include "structure/Vertex.h"
#include "step/TraversalStep.h"
#include "traversal/GraphTraversal.h"
#include <string>
#include <optional>
#include <boost/any.hpp>

#define TO_STEP 0x91

namespace gremlinxx {

	class ToStep : public TraversalStep {
		private:
			boost::any arg;
			std::optional<GraphTraversal> traversal = {};
		public:
			ToStep(std::string side_effect_label);

			ToStep(Vertex to_vertex);

			ToStep(GraphTraversal to_vertex_traversal);

			inline boost::any get_arg() { 
				if(arg.empty()) throw std::runtime_error("Argument is not present!");
				return arg; 
			}

			inline GraphTraversal& get_traversal() { 
				if(!traversal) throw std::runtime_error("traversal is not present!");
				return traversal.value();
			}

			using TraversalStep::getInfo;
			virtual std::string getInfo();
	};

}