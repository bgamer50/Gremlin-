#ifndef P_PREDICATE_H
#define P_PREDICATE_H

#include <string>
#include <stdexcept>

enum PType {EQ, LT, GT, BT, LTE, GTE};

/**
    Equivalent of P in Java-Gremlin.
**/
template<typename T>
class P {
	public:
		T first_arg;
		T second_arg;
		PType comparator;

		P(PType type, T t0, T t1) {
			comparator = type;
			first_arg = t0;
			second_arg = t1;
		}

		std::string getInfo() {
			std::string info;
			switch(comparator) {
				case EQ:
					info = "eq ";
					info += std::to_string(first_arg);
					break;
				case LT:
					info = "lt ";
					info += std::to_string(first_arg);
					break;
				case GT:
					info = "gt ";
					info += std::to_string(first_arg);
					break;
				case LTE:
					info = "lte ";
					info += std::to_string(first_arg);
					break;
				case GTE:
					info = "gte ";
					info += std::to_string(first_arg);
					break;
				case BT:
					info = "bt ";
					info = info + std::to_string(first_arg) + ", " + std::to_string(second_arg);
					break;
				default:
					info = "??";
					break;
			}

			return info;
	}

	virtual bool apply(T t) {
		auto cmp = *(uint64_t*)t - *(uint64_t*)first_arg;

		switch(comparator) {
			case EQ:
				return cmp == 0;
			case LT:
				return cmp < 0;
			case GT:
				return cmp > 0;
			case LTE:
				return cmp <= 0;
			case GTE:
				return cmp >= 0;
			case BT:
				return cmp >= 0 && *(uint64_t*)t < *(uint64_t*)second_arg;
			default:
				throw std::runtime_error("Illegal comparator");
		}
	}
};

/**
    String version of the P template class.
**/
template <>
class P<std::string*> {
	public:
		std::string* first_arg;
		std::string* second_arg;
		PType comparator;

		P(PType type, std::string* t0, std::string* t1) {
			comparator = type;
			first_arg = t0;
			second_arg = t1;
		}

		std::string getInfo() {
			std::string info;
			switch(comparator) {
				case EQ:
					info = "eq ";
					info += *first_arg;
					break;
				case LT:
					info = "lt ";
					info += *first_arg;
					break;
				case GT:
					info = "gt ";
					info += *first_arg;
					break;
				case BT:
					info = "bt ";
					info = info + *first_arg + ", " + *second_arg;
					break;
				default:
					info = "??";
					break;
			}

			return info;
		}

		virtual bool apply(std::string* s) {
			auto cmp = (*s).compare(*first_arg);
			switch(comparator) {
				case EQ:
					return cmp == 0;
				case LT:
					return cmp < 0;
				case GT:
					return cmp > 0;
				case LTE:
					return cmp <= 0;
				case GTE:
					return cmp >= 0;
				case BT:
					return cmp >= 0 && (*s).compare(*second_arg) < 0;
				default:
					throw std::runtime_error("Illegal comparator");
			}
		}
};

#endif
