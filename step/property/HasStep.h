#pragma once

class Vertex;

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <any>
#include "step/TraversalStep.h"
#include "traversal/P.h"
#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"
#include "traversal/GraphTraversalSource.h"
#include "structure/Vertex.h"
#include "structure/Edge.h"
#include "structure/VertexProperty.h"

#define HAS_STEP 0x83

namespace gremlinxx {

	class HasStep : public TraversalStep {
		private:
			// The key of the property where data to compare
			// against is stored.
			std::string property_key_or_label;

			// Predicate
			P predicate = P(maelstrom::EQUALS, std::any());

		public:
			HasStep(std::string property_key_or_label, P predicate);

			using TraversalStep::getInfo;
			virtual std::string	getInfo();

			inline std::string get_key() {
				return this->property_key_or_label;
			}

			inline std::any get_value() {
				return this->predicate.operand;
			}

			inline P get_predicate() {
				return this->predicate;
			}

			virtual void apply(GraphTraversal* trv, gremlinxx::traversal::TraverserSet& traversers);
	};

}