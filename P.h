#ifndef P_PREDICATE_H
#define P_PREDICATE_H

#include <string>

enum PType {EQ, LT, GT, BT};

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
};

template <>
class P<std::string> {
	public:
		std::string first_arg;
		std::string second_arg;
		PType comparator;

		P(PType type, std::string t0, std::string t1) {
			comparator = type;
			first_arg = t0;
			second_arg = t1;
		}

		std::string getInfo() {
			std::string info;
			switch(comparator) {
				case EQ:
					info = "eq ";
					info += first_arg;
					break;
				case LT:
					info = "lt ";
					info += first_arg;
					break;
				case GT:
					info = "gt ";
					info += first_arg;
					break;
				case BT:
					info = "bt ";
					info = info + first_arg + ", " + second_arg;
					break;
				default:
					info = "??";
					break;
			}

			return info;
		}
};

template<typename T>
inline P<T>* eq(T t);
#endif