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

		// The value to be compared against.
		boost::any value;

		// A function that compares extracted objects.
		// Generated by the P class (or an extension class)
		std::function<bool(boost::any)> predicate;

	public:
		HasStep(std::string key, std::function<bool(boost::any)> pred)
		: TraversalStep(FILTER, HAS_STEP) {
			predicate = pred;
			property_key_or_label = key;
		}

		HasStep(std::string key, boost::any value, std::function<bool(boost::any)> pred)
		: TraversalStep(FILTER, HAS_STEP) {
			predicate = pred;
			property_key_or_label = key;
			this->value = value;
		}

		virtual std::string	getInfo() {
			std::string info = "HasStep(";
			info = info + property_key_or_label + " " + "<predicate>" + ")";
			return info;
		}

		boost::any get_value() {
			return this->value;
		}

		std::string get_key() {
			return this->property_key_or_label;
		}

		/**
            This is used for the expansion of has(prop) and has(prop, val)
            It tests whether the Vertex in question has the property/value
            in question and returns true if this is in fact the case.
		**/
		bool apply(Vertex* v) {
			//std::cout << "id: " << boost::any_cast<uint64_t>(v->id());
			//std::cout << "search for " << property_key_or_label << "\n";		    
			VertexProperty<boost::any>* vp = v->property(property_key_or_label);
			//std::cout << "null? " << (vp == nullptr) << "\n";

			//std::cout << boost::any_cast<std::string>(vp->value()) << "\n";
		    if(predicate == nullptr) return vp == nullptr;
			else { 
				//std::cout << "need to test predicate\n";
				//std::cout << "key: " << vp->key() << "\n";
				std::string value = boost::any_cast<std::string>(vp->value());
				//std::cout << "value: " << value << "\n";
				return vp != nullptr && predicate(vp->value());
			}
		}
};

#endif
