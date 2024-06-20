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

	enum filter_policy_t {
		BY_ENTRY_COUNT = 0,
		BY_ENTRY_COUNT_REVERSE = 1,
		BY_SPECIFIED_ORDER = 2
	};

	class HasStep : public TraversalStep {
		private:
			std::vector<std::pair<std::string, P>> predicates;

		public:
			static filter_policy_t FILTER_POLICY;

			HasStep(std::string property_key_or_label, P predicate);

			using TraversalStep::getInfo;
			virtual std::string	getInfo();

			inline std::string get_key() {
				if(this->predicates.size() == 1) {
					return this->predicates.front().first;
				}
				
				throw std::runtime_error("This HasStep contains more than one predicate");
			}

			inline std::any get_value() {
				if(this->predicates.size() == 1) {
					return this->predicates.front().second.operand;
				}
				
				throw std::runtime_error("This HasStep contains more than one predicate");
			}

			inline P get_predicate() {
				if(this->predicates.size() == 1) {
					return this->predicates.front().second;
				}
				
				throw std::runtime_error("This HasStep contains more than one predicate");
			}

			void join(HasStep* other);

			virtual void apply(GraphTraversal* trv, gremlinxx::traversal::TraverserSet& traversers);
	};

}