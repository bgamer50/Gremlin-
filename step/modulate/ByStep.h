#pragma once

#include <string>
#include <boost/any.hpp>

#define BY_STEP 0x92

#include "traversal/GraphTraversal.h"
#include "step/TraversalStep.h"

namespace gremlinxx {
		
	class ByStep : public TraversalStep {
		private:
			boost::any arg;
		public:
			ByStep(boost::any arg);
			
			inline boost::any get() { return arg; }

			using TraversalStep::getInfo;
			virtual std::string getInfo();
	};

}