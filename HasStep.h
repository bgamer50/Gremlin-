#ifndef HAS_STEP_H
#define HAS_STEP_H
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <boost/any.hpp>
#include "TraversalStep.h"
#include "P.h"
#include "Vertex.h"

#define HAS_STEP 0x83

class HasStep : public TraversalStep {
	private:
		// The key of the property where data to compare
		// against is stored.
		std::string property_key_or_label;

		// A function that compares extracted objects.
		// Generated by the P class (or an extension class)
		std::function<bool(boost::any)> predicate;

	public:
		HasStep(std::string key, std::function<bool(boost::any)> pred)
		: TraversalStep(FILTER, HAS_STEP) {
			predicate = pred;
			property_key_or_label = key;
		}

		virtual std::string	getInfo() {
			std::string info = "HasStep(";
			info = info + property_key_or_label + " " + "<predicate>" + ")";
			return info;
		}

		/**
            This is used for the expansion of has(prop) and has(prop, val)
            It tests whether the Vertex in question has the property/value
            in question and returns true if this is in fact the case.
		**/
		bool apply(Vertex* v) {		    
			VertexProperty<boost::any>* vp = v->property(property_key_or_label);

		    if(predicate == nullptr) return vp == nullptr;
		    else return vp != nullptr && predicate(vp->value());
		}
};

#endif
