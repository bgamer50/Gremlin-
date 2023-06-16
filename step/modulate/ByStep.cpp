#include "step/modulate/ByStep.h"

namespace gremlinxx {
		
	ByStep::ByStep(boost::any arg)
	: TraversalStep(MODULATOR, BY_STEP) {
		this->arg = arg;
	}

	std::string ByStep::getInfo() {
		return "ByStep(?)";
	}

}