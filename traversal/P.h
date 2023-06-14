#pragma once

#include <string>
#include <iostream>
#include <boost/any.hpp>
#include <stdlib.h>
#include <functional>

#include "maelstrom/storage/comparison.h"

namespace gremlinxx {

	/**
		Equivalent of P in Java-Gremlin.
	**/
	class P {
		public:
			maelstrom::comparator comparison;
			boost::any operand;

			P(maelstrom::comparator comparison, boost::any operand) {
				this->comparison = comparison;
				this->operand = operand;
			}

			inline std::string getInfo() {
				return std::string("P<?>");
			}

			inline static P eq(boost::any t) {
				return P(maelstrom::EQUALS, t);
			}

			inline static P neq(boost::any t) {
				return P(maelstrom::NOT_EQUALS, t);
			}

			inline static P gt(boost::any t) {
				return P(maelstrom::GREATER_THAN, t);
			}

			inline static P gte(boost::any t) {
				return P(maelstrom::GREATER_THAN_OR_EQUAL, t);
			}

			inline static P lt(boost::any t) {
				return P(maelstrom::LESS_THAN, t);
			}

			inline static P lte(boost::any t) {
				return P(maelstrom::LESS_THAN_OR_EQUAL, t);
			}

			inline static P between(boost::any t, boost::any u) {
				return P(maelstrom::BETWEEN, std::make_pair(t,u));
			}

			inline static P inside(boost::any t, boost::any u) {
				return P(maelstrom::INSIDE, std::make_pair(t,u));
			}

			inline static P outside(boost::any t, boost::any u) {
				return P(maelstrom::OUTSIDE, std::make_pair(t,u));
			}

			inline static P within(boost::any b...) {
				throw std::runtime_error("Within is currently unsupported in gremlin++");
			}

			inline static P without(boost::any b...) {
				throw std::runtime_error("Without is currently unsupported in gremlinx++");
			}

	};

}
