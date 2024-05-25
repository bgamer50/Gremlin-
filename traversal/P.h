#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <any>
#include <stdlib.h>
#include <functional>

#include "maelstrom/storage/comparison.h"
#include "util/gremlin_utils.h"

namespace gremlinxx {

	/**
		Equivalent of P in Java-Gremlin.
	**/
	class P {
		public:
			maelstrom::comparator comparison;
			std::any operand;

			P(maelstrom::comparator comparison, std::any operand) {
				this->comparison = comparison;

				if(operand.type() == typeid(const char*)) {
					operand = std::string(
						std::any_cast<const char*>(operand)
					);
				}
				this->operand = operand;
			}

			inline std::string getInfo() {
				std::stringstream sx;
				sx << "P<" << "'" << maelstrom::comparator_names[this->comparison] << "' " << string_any(operand) << ">";
				return sx.str();
			}

			inline static P eq(std::any t) {
				return P(maelstrom::EQUALS, t);
			}

			inline static P neq(std::any t) {
				return P(maelstrom::NOT_EQUALS, t);
			}

			inline static P gt(std::any t) {
				return P(maelstrom::GREATER_THAN, t);
			}

			inline static P gte(std::any t) {
				return P(maelstrom::GREATER_THAN_OR_EQUAL, t);
			}

			inline static P lt(std::any t) {
				return P(maelstrom::LESS_THAN, t);
			}

			inline static P lte(std::any t) {
				return P(maelstrom::LESS_THAN_OR_EQUAL, t);
			}

			inline static P between(std::any t, std::any u) {
				return P(maelstrom::BETWEEN, std::make_pair(t,u));
			}

			inline static P inside(std::any t, std::any u) {
				return P(maelstrom::INSIDE, std::make_pair(t,u));
			}

			inline static P outside(std::any t, std::any u) {
				return P(maelstrom::OUTSIDE, std::make_pair(t,u));
			}

			inline static P within(std::any b...) {
				throw std::runtime_error("Within is currently unsupported in gremlin++");
			}

			inline static P without(std::any b...) {
				throw std::runtime_error("Without is currently unsupported in gremlinx++");
			}

	};

}
