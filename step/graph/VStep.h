#pragma once

#include <string>
#include <vector>
#include <any>
#include "step/TraversalStep.h"
#include "traversal/Traverser.h"

#define V_STEP 0x81

namespace gremlinxx {

	class VStep : public TraversalStep {
		protected:
			std::vector<std::any> element_ids;
		public:
			VStep(std::vector<std::any> eids);

			using TraversalStep::getInfo;
			virtual std::string	getInfo();

			inline std::vector<std::any>& get_element_ids() { return this->element_ids; }

			virtual void apply(GraphTraversal* trv, gremlinxx::traversal::TraverserSet& traversers);
	};

}