#pragma once

#include <string>
#include <iostream>
#include <boost/any.hpp>
#include <stdlib.h>
#include <functional>

namespace gremlinxx {

	/**
		Equivalent of P in Java-Gremlin.
	**/
	class P {
		public:
			enum Comparison { EQ, NEQ, GT, GTE, LT, LTE, BETWEEN};
			Comparison comparison;
			boost::any operand;

			P(P::Comparison comparison, boost::any operand) {
				this->comparison = comparison;
				this->operand = operand;
			}

			inline std::string getInfo() {
				return std::string("P<?>");
			}

			inline static P eq(boost::any t) {
				return P(EQ, t);
			}

			inline static P neq(boost::any t) {
				return P(NEQ, t);
			}

			inline static P gt(boost::any t) {
				return P(GT, t);
			}

			inline static P gte(boost::any t) {
				return P(GTE, t);
			}

			inline static P lt(boost::any t) {
				return P(LT, t);
			}

			inline static P lte(boost::any t) {
				return P(LTE, t);
			}

			inline static P between(boost::any t, boost::any u) {
				return P(BETWEEN, std::make_pair(t,u));
			}
	};

}
