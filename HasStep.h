#ifndef HAS_STEP_H
#define HAS_STEP_H
#include <string>
#include <vector>
#include "TraversalStep.h"
#include "P.h"

#define HAS_STEP 0x83

template<typename T>
class HasStep : public TraversalStep {
	private:
		std::string property_key;
		P<T>* predicate;
	public:
		HasStep(std::string key, P<T>* pred)
		: TraversalStep(filter, HAS_STEP) {
			predicate = pred;
			property_key = key;
		}

		virtual std::string	getInfo() {
			std::string info = "HasStep(";
			info = info + property_key + " " + predicate->getInfo() + ")";
			return info;
		}
};

#endif