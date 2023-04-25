#pragma once

class Vertex;

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <boost/any.hpp>
#include "step/TraversalStep.h"
#include "traversal/P.h"
#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"
#include "traversal/GraphTraversalSource.h"
#include "structure/Vertex.h"
#include "structure/Edge.h"
#include "structure/VertexProperty.h"

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
		HasStep(std::string property_key_or_label, P predicate);

		using TraversalStep::getInfo;
		virtual std::string	getInfo();

		inline std::string get_key() {
			return this->property_key_or_label;
		}

		inline boost::any get_value() {
			return this->predicate.operand;
		}

		inline void set_acquirer(std::function<boost::any(GraphTraversalSource* src, Vertex*, std::string&)> acquirer) {
			this->acquirer = acquirer;
		}

		/**
            This is used for the expansion of has(prop) and has(prop, val)
            It tests whether the Vertex in question has the property/value
            in question and returns true if this is in fact the case.
		**/
		bool test(Vertex* v, GraphTraversalSource* src);

		virtual void apply(GraphTraversal* trv, TraverserSet& traversers);
};
