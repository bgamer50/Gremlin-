#pragma once

#include <string>
#include <vector>
#include <boost/any.hpp>
#include "step/TraversalStep.h"
#include "traversal/Traverser.h"

#define V_STEP 0x81

namespace gremlinxx {

	class VStep : public TraversalStep {
		protected:
			std::vector<boost::any> element_ids;
		public:
			VStep(std::vector<boost::any> eids);

			using TraversalStep::getInfo;
			virtual std::string	getInfo();

			inline std::vector<boost::any>& get_element_ids() { return this->element_ids; }

			virtual void apply(GraphTraversal* trv, gremlinxx::traversal::TraverserSet& traversers);
	};

}