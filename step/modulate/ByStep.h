#pragma once

#include <string>
#include <any>

#define BY_STEP 0x92

#include "traversal/GraphTraversal.h"
#include "step/TraversalStep.h"

namespace gremlinxx {
		
	class ByStep : public TraversalStep {
		private:
			std::any arg;
		public:
			ByStep(std::any arg);
			
			inline std::any get() { return arg; }

			using TraversalStep::getInfo;
			virtual std::string getInfo();
	};

}