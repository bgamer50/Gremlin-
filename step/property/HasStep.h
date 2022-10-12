#ifndef HAS_STEP_H
#define HAS_STEP_H
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <boost/any.hpp>
#include "step/TraversalStep.h"
#include "traversal/P.h"
#include "structure/Vertex.h"

#define HAS_STEP 0x83

class HasStep : public TraversalStep {
	private:
		// The key of the property where data to compare
		// against is stored.
		std::string property_key_or_label;

		// Predicate
		P predicate = P(P::Comparison::EQ, boost::any());

		// Acquirer
		std::function<boost::any(GraphTraversalSource*, Vertex*, std::string&)> acquirer = [](GraphTraversalSource* src, Vertex* v, std::string& key){
			VertexProperty* vp = static_cast<VertexProperty*>(v->property(key));
			return vp == nullptr ? boost::any() : vp->value();
		};

	public:
		HasStep(std::string property_key_or_label, P predicate)
		: TraversalStep(FILTER, HAS_STEP) {
			this->predicate = predicate;
			this->property_key_or_label = property_key_or_label;
		}

		using TraversalStep::getInfo;
		virtual std::string	getInfo() {
			return std::string("HasStep(") + property_key_or_label + " " + predicate.getInfo() + ")";
		}

		std::string get_key() {
			return this->property_key_or_label;
		}

		boost::any get_value() {
			return this->predicate.operand;
		}

		void set_acquirer(std::function<boost::any(GraphTraversalSource* src, Vertex*, std::string&)> acquirer) {
			this->acquirer = acquirer;
		}

		/**
            This is used for the expansion of has(prop) and has(prop, val)
            It tests whether the Vertex in question has the property/value
            in question and returns true if this is in fact the case.
		**/
		bool test(Vertex* v, GraphTraversalSource* src) {
			boost::any property_val = this->acquirer(src, v, this->property_key_or_label);
			boost::any val = this->predicate.operand;
			switch(this->predicate.comparison) { // betting on a good branch predictor here
				case P::Comparison::EQ:
					if(val.empty()) return property_val.empty();
					return src->test_equals(property_val, val);
					break;
				case P::Comparison::NEQ:
					if(val.empty()) return !property_val.empty();
					return !src->test_equals(property_val, val);
					break;
				case P::Comparison::GTE:
					return src->test_compare(property_val, val) >= 0;
					break;
				case P::Comparison::GT:
					return src->test_compare(property_val, val) > 0;
					break;
				case P::Comparison::LTE:
					return src->test_compare(property_val, val) <= 0;
					break;
				case P::Comparison::LT:
					return src->test_compare(property_val, val) < 0;
					break;
				case P::Comparison::BETWEEN: {
					std::pair<boost::any, boost::any> p = boost::any_cast<std::pair<boost::any, boost::any>>(val);
					return src->test_compare(property_val, p.first) >= 0 && src->test_compare(property_val, p.second) < 0;
					break;
				}
				default:
					return false;
			}
		}

		virtual void apply(GraphTraversal* trv, TraverserSet& traversers) {
			GraphTraversalSource* src = trv->getTraversalSource();
			TraverserSet new_traversers;

			for(Traverser& trv : traversers) {
				Vertex* v = boost::any_cast<Vertex*>(trv.get());
				bool advance = this->test(v, src);
				if(advance) new_traversers.push_back(trv);
			}

			traversers.swap(new_traversers);
		}
};

#endif
