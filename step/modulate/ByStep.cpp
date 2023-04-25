#include "step/modulate/ByStep.h"

ByStep::ByStep(boost::any arg)
: TraversalStep(MODULATOR, BY_STEP) {
	this->arg = arg;
}

std::string ByStep::getInfo() {
	return "ByStep(?)";
}