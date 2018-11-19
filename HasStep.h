#ifndef HAS_STEP_H
#define HAS_STEP_H
#include <string>
#include <vector>
#include <stdexcept>
#include "TraversalStep.h"
#include "P.h"
#include "Vertex.h"

#define HAS_STEP 0x83

template<typename T>
class HasStep : public TraversalStep {
	private:
		std::string property_key_or_label;
		P<T>* predicate;
	public:
		HasStep(std::string key, P<T>* pred)
		: TraversalStep(FILTER, HAS_STEP) {
			predicate = pred;
			property_key_or_label = key;
		}

		virtual std::string	getInfo() {
			std::string info = "HasStep(";
			info = info + property_key_or_label + " " + predicate->getInfo() + ")";
			return info;
		}

		bool apply(Vertex* v) {

		}
};

#endif