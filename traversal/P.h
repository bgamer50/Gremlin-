#ifndef P_PREDICATE_H
#define P_PREDICATE_H

#include <string>
#include <iostream>
#include <boost/any.hpp>
#include <stdlib.h>
#include <functional>

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

		std::string getInfo() {
			return std::string("P<?>");
		}

		static P eq(boost::any t) {
			return P(EQ, t);
		}

		static P neq(boost::any t) {
			return P(NEQ, t);
		}

		static P gt(boost::any t) {
			return P(GT, t);
		}

		static P gte(boost::any t) {
			return P(GTE, t);
		}

		static P lt(boost::any t) {
			return P(LT, t);
		}

		static P lte(boost::any t) {
			return P(LTE, t);
		}

		static P between(boost::any t, boost::any u) {
			return P(BETWEEN, std::make_pair(t,u));
		}
};

#endif
